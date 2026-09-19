#include "sc2_proto_interface.h"

#include <cassert>
#include <iostream>

#include "sc2_control_interfaces.h"

// This assert reflects a guarantee that each request is matched by the correct response.
static_assert(
    int(SC2APIProtocol::Response::ResponseCase::kCreateGame) ==
            int(SC2APIProtocol::Request::RequestCase::kCreateGame) &&
        int(SC2APIProtocol::Response::ResponseCase::kJoinGame) ==
            int(SC2APIProtocol::Request::RequestCase::kJoinGame) &&
        int(SC2APIProtocol::Response::ResponseCase::kRestartGame) ==
            int(SC2APIProtocol::Request::RequestCase::kRestartGame) &&
        int(SC2APIProtocol::Response::ResponseCase::kStartReplay) ==
            int(SC2APIProtocol::Request::RequestCase::kStartReplay) &&
        int(SC2APIProtocol::Response::ResponseCase::kLeaveGame) ==
            int(SC2APIProtocol::Request::RequestCase::kLeaveGame) &&
        int(SC2APIProtocol::Response::ResponseCase::kGameInfo) ==
            int(SC2APIProtocol::Request::RequestCase::kGameInfo) &&
        int(SC2APIProtocol::Response::ResponseCase::kObservation) ==
            int(SC2APIProtocol::Request::RequestCase::kObservation) &&
        int(SC2APIProtocol::Response::ResponseCase::kAction) == int(SC2APIProtocol::Request::RequestCase::kAction) &&
        int(SC2APIProtocol::Response::ResponseCase::kStep) == int(SC2APIProtocol::Request::RequestCase::kStep) &&
        int(SC2APIProtocol::Response::ResponseCase::kData) == int(SC2APIProtocol::Request::RequestCase::kData) &&
        int(SC2APIProtocol::Response::ResponseCase::kQuery) == int(SC2APIProtocol::Request::RequestCase::kQuery) &&
        int(SC2APIProtocol::Response::ResponseCase::kSaveReplay) ==
            int(SC2APIProtocol::Request::RequestCase::kSaveReplay) &&
        int(SC2APIProtocol::Response::ResponseCase::kQuit) == int(SC2APIProtocol::Request::RequestCase::kQuit) &&
        int(SC2APIProtocol::Response::ResponseCase::kPing) == int(SC2APIProtocol::Request::RequestCase::kPing) &&
        int(SC2APIProtocol::Response::ResponseCase::kDebug) == int(SC2APIProtocol::Request::RequestCase::kDebug) &&
        int(SC2APIProtocol::Response::ResponseCase::kReplayInfo) ==
            int(SC2APIProtocol::Request::RequestCase::kReplayInfo) &&
        int(SC2APIProtocol::Response::ResponseCase::kAvailableMaps) ==
            int(SC2APIProtocol::Request::RequestCase::kAvailableMaps) &&
        int(SC2APIProtocol::Response::ResponseCase::RESPONSE_NOT_SET) ==
            int(SC2APIProtocol::Request::RequestCase::REQUEST_NOT_SET),
    "Requests and responses should be of the exact same size and in the exact order.");

namespace sc2 {

const char* RequestResponseIDToName(int type) {
    switch (type) {
        case 1:
            return "CreateGame";
        case 2:
            return "JoinGame";
        case 3:
            return "RestartGame";
        case 4:
            return "StartReplay";
        case 5:
            return "LeaveGame";
        case 6:
            return "QuickSave";
        case 7:
            return "QuickLoad";
        case 8:
            return "Quit";
        case 9:
            return "GameInfo";
        case 10:
            return "Observation";
        case 11:
            return "Action";
        case 12:
            return "Step";
        case 13:
            return "Data";
        case 14:
            return "Query";
        case 15:
            return "SaveReplay";
        case 16:
            return "ReplayInfo";
        case 17:
            return "AvailableMaps";
        case 18:
            return "SaveMap";
        case 19:
            return "Ping";
        case 20:
            return "Debug";
    }

    return "Unknown";
}

PendingMatch MatchPendingResponse(SC2APIProtocol::Response::ResponseCase pending_type, uint32_t pending_id,
                                  const SC2APIProtocol::Response& response) {
    if (response.has_id() && pending_id != 0 && response.id() < pending_id) {
        return PendingMatch::Stale;
    }

    const bool type_ok = pending_type == response.response_case();
    const bool id_matches = !response.has_id() || pending_id == 0 || response.id() == pending_id;

    if (response.error_size() > 0) {
        return id_matches ? PendingMatch::Accept : PendingMatch::Wait;
    }

    if (response.has_id() && pending_id != 0 && response.id() != pending_id) {
        return PendingMatch::Mismatch;
    }

    if (!type_ok) {
        if (response.has_id() && pending_id != 0 && response.id() == pending_id) {
            return PendingMatch::Mismatch;
        }
        return PendingMatch::Wait;
    }

    return PendingMatch::Accept;
}

ProtoInterface::ProtoInterface()
    : address_("127.0.0.1"),
      port_(5000),
      default_timeout_ms_(kDefaultProtoInterfaceTimeout),
      latest_status_(SC2APIProtocol::Status::unknown),
      response_pending_(SC2APIProtocol::Response::RESPONSE_NOT_SET),
      pending_id_(0),
      next_request_id_(1) {
}

void ProtoInterface::ClearPending() {
    response_pending_ = SC2APIProtocol::Response::RESPONSE_NOT_SET;
    pending_id_ = 0;
}

bool ProtoInterface::ConnectToGame(const std::string& address, int port, int timeout_ms) {
    latest_status_ = SC2APIProtocol::Status::unknown;
    address_ = address;
    port_ = port;
    default_timeout_ms_ = timeout_ms;
    if (!connection_.Connect(address, port, false)) {
        return false;
    }

    connection_.SetConnectionClosedCallback([&]() { control_->Error(ClientError::ConnectionClosed); });

    return PingGame();
}

GameRequestPtr ProtoInterface::MakeRequest() {
    return std::make_shared<SC2APIProtocol::Request>(SC2APIProtocol::Request());
}

bool ProtoInterface::SendRequest(GameRequestPtr& request, bool ignore_pending_requests) {
    uint32_t request_type = static_cast<uint32_t>(request->request_case());
    if (request_type >= count_uses_.size()) {
        uint32_t current = static_cast<uint32_t>(count_uses_.size());
        count_uses_.resize(request_type + 1);
        for (uint32_t i = current; i < request_type + 1; ++i) {
            count_uses_[i] = 0;
        }
    }
    ++count_uses_[request_type];

    // If there is no connection, try rebuilding the connection.
    if (!connection_.HasConnection()) {
        if (!connection_.Connect(address_, port_, false)) {
            return false;
        }
    }

    // If there is still no connection, give up.
    if (!connection_.HasConnection()) {
        return false;
    }

    // Technically there can be new requests while responses are pending, but this library is not written for that.
    // For now, make everything purely sequential.
    if (!ignore_pending_requests && HasResponsePending()) {
        control_->Error(ClientError::ResponseNotConsumed);
        return false;
    }

    if (!request->has_id()) {
        if (next_request_id_ == 0) {
            next_request_id_ = 1;
        }
        request->set_id(next_request_id_++);
        if (next_request_id_ == 0) {
            next_request_id_ = 1;
        }
    }

    connection_.Send(request.get());

    // Expect a certain response.
    response_pending_ = SC2APIProtocol::Response::ResponseCase(request->request_case());
    pending_id_ = request->id();
    return true;
}

GameResponsePtr ProtoInterface::WaitForResponseInternal() {
    latest_status_ = SC2APIProtocol::Status::unknown;

    for (;;) {
        SC2APIProtocol::Response* response = nullptr;
        if (!connection_.Receive(response, default_timeout_ms_)) {
            // Timeout: this request is still owed.
            return nullptr;
        }

        GameResponsePtr response_ptr(response);
        const PendingMatch match = MatchPendingResponse(response_pending_, pending_id_, *response_ptr);

        if (match == PendingMatch::Stale) {
            continue;
        }

        for (int i = 0; error_callback_ && i < response_ptr->error_size(); ++i) {
            error_callback_(response_ptr->error(i));
        }

        if (response_ptr->has_status()) {
            latest_status_ = response_ptr->status();
        }

        if (match == PendingMatch::Wait) {
            continue;
        }

        if (match == PendingMatch::Mismatch) {
            control_->Error(ClientError::ResponseMismatch);
            ClearPending();
            return response_ptr;
        }

        if (response_ptr->error_size() > 0) {
            std::cerr << "While waiting for Response" << RequestResponseIDToName(response_pending_)
                      << " received an error." << std::endl;
            for (int i = 0; i < response_ptr->error_size(); ++i) {
                std::cerr << "Error: " << response_ptr->error(i) << std::endl;
            }
        }

        ClearPending();
        return response_ptr;
    }
}

bool ProtoInterface::PingGame() {
    // Send the request.
    GameRequestPtr request = MakeRequest();
    request->mutable_ping();
    if (!SendRequest(request, true)) {
        return false;
    }

    // Wait for the return of the ping.
    // TODO: Implement a time out here.
    GameResponsePtr response = WaitForResponseInternal();
    if (!response.get() || !response->has_ping()) {
        return false;
    }

    const auto& response_ping = response->ping();
    base_build_ = response_ping.base_build();
    data_version_ = response_ping.data_version();
    return true;
}

void ProtoInterface::Quit() {
    // Tell the game to close
    GameRequestPtr request = MakeRequest();
    request->mutable_quit();
    SendRequest(request);

    // Immediately tear down connection. The callbacks may try to call into objects who are
    // in the process of being destroyed.
    connection_.Disconnect();
}

void ProtoInterface::SetErrorCallback(std::function<void(const std::string& error_str)> error_callback) {
    error_callback_ = error_callback;
}

bool ProtoInterface::PollResponse() {
    return connection_.PollResponse();
}

bool ProtoInterface::HasResponsePending() const {
    return response_pending_ != SC2APIProtocol::Response::ResponseCase::RESPONSE_NOT_SET;
}

}  // namespace sc2
