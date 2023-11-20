#include "sc2api/sc2_connection.h"

#include <iostream>
#include <cassert>
#include <chrono>

#include "s2clientprotocol/sc2api.pb.h"

#include "civetweb.h"

namespace {
bool StartCivetweb() {
    static bool is_initialized = false;

    if (is_initialized) {
        return true;
    }

    const char* options[] = {
        "request_timeout_ms",
        "5000",
        "websocket_timeout_ms",
        "1200000",
        "num_threads",
        "4",
        "tcp_nodelay",
        "1",
        0
    };

    struct mg_callbacks callbacks = {0};

    struct mg_init_data mg_start_init_data = {0};
    mg_start_init_data.callbacks = &callbacks;
    mg_start_init_data.configuration_options = options;

    struct mg_error_data mg_start_error_data = {0};
    char ebuff[256] = {0};
    mg_start_error_data.text = ebuff;
    mg_start_error_data.text_buffer_size = sizeof(ebuff);

    const auto* ctx = mg_start2(&mg_start_init_data, &mg_start_error_data);
    if (!ctx) {
        std::cerr << "Failed to start civetweb server: " << ebuff << std::endl;
        return false;
    }

    is_initialized = true;
    return true;
}

}  // anonymous namespace

namespace sc2 {

bool GetClientData(const mg_connection* connection, sc2::Connection*& out) {
    if (!connection) {
        return false;
    }

    mg_context* ctx = mg_get_context(connection);

    if (!ctx) {
        return false;
    }

    out = (sc2::Connection*) mg_get_user_data(ctx);
    return true;
}

static int DataHandler(
    mg_connection* conn,
    int /*flags*/,
    char* data,
    size_t data_len,
    void*) {
    sc2::Connection* sc2_connection;
    if (!GetClientData(conn, sc2_connection)) {
        return 0;
    }

    SC2APIProtocol::Response* response = new SC2APIProtocol::Response();
    if (!response->ParseFromArray(data, (int)data_len)) {
        return 1;
    }

    sc2_connection->PushResponse(response);

    return 1;
}

static void ConnectionClosedHandler(const struct mg_connection* conn, void *) {
    sc2::Connection* sc2_connection;
    if (!GetClientData(conn, sc2_connection)) {
        return;
    }

    if (sc2_connection->connection_closed_callback_) {
        sc2_connection->connection_closed_callback_();
    }
}

Connection::Connection() :
    connection_(nullptr),
    verbose_(false),
    queue_(),
    mutex_(),
    condition_(),
    has_response_(false) {}

bool Connection::Connect(const std::string& address, int port, bool verbose) {
    if (!StartCivetweb()) {
        return false;
    }
    verbose_ = verbose;

    char ebuff[256] = {0};

    connection_ = mg_connect_websocket_client(
        address.c_str(),
        port,
        0,
        ebuff,
        256,
        "/sc2api",
        nullptr,
        DataHandler,
        ConnectionClosedHandler,
        (void*) this);

    if (!connection_) {
        std::cerr << "Failed to establish websocket connection: " << ebuff << std::endl;
        return false;
    }

    if (verbose_) {
        std::cout << "Connected..." << std::endl;
    }

    return true;
}

Connection::~Connection() {
    Disconnect();
}

void Connection::Send(const SC2APIProtocol::Request* request) {
    if (!request) {
        return;
    }
    // Connection must be established before sending.
    assert(connection_);
    if (!connection_) {
        return;
    }
    size_t size = request->ByteSizeLong();
    void* buffer = malloc(size);
    request->SerializeToArray(buffer, (int)size);
    mg_websocket_write(
        connection_,
        MG_WEBSOCKET_OPCODE_BINARY,
        (const char*) buffer,
        size);

    free(buffer);

    if (verbose_) {
        std::cout << "Sending: " << request->DebugString();
    }
}

bool Connection::Receive(
    SC2APIProtocol::Response*& response,
    unsigned int timeout_ms) {
    std::unique_lock<std::mutex> lock(mutex_);
    // Block until a message is recieved.
    if (verbose_) {
        std::cout << "Waiting for response..." << std::endl;
    }
    auto now = std::chrono::system_clock::now();
    if (condition_.wait_until(
        lock,
        now + std::chrono::milliseconds(timeout_ms),
        [&] { return queue_.size() != 0; })) {
        lock.unlock();
        PopResponse(response);
        return true;
    }

    lock.unlock();
    response = nullptr;
    Disconnect();
    queue_.clear();

    // Execute the timeout callback if it exists.
    if (timeout_callback_) {
        timeout_callback_();
    }

    return false;
}

void Connection::PushResponse(SC2APIProtocol::Response*& response) {
    std::lock_guard<std::mutex> guard(mutex_);
    queue_.push_back(response);
    condition_.notify_one();
    has_response_ = true;
}

void Connection::PopResponse(SC2APIProtocol::Response*& response) {
    if (queue_.empty()) return;
    std::lock_guard<std::mutex> guard(mutex_);
    response = queue_.front();
    queue_.pop_front();
    if (queue_.empty()) {
        has_response_ = false;
    }
}

void Connection::SetTimeoutCallback(std::function<void()> callback) {
    timeout_callback_ = callback;
}

void Connection::SetConnectionClosedCallback(std::function<void()> callback) {
    connection_closed_callback_ = callback;
}

bool Connection::HasConnection() const {
    return connection_ != nullptr;
}

void Connection::Disconnect() {
    mg_close_connection(connection_);
    connection_ = nullptr;
}

bool Connection::PollResponse() {
    return has_response_;
}

}
