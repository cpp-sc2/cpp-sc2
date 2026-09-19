#include "sc2api/sc2_proto_interface.h"

namespace sc2 {

bool TestProtoMatch(int, char**) {
    using SC2APIProtocol::Response;

    {
        Response stale;
        stale.set_id(1);
        stale.mutable_step();
        if (MatchPendingResponse(Response::kObservation, 5, stale) != PendingMatch::Stale) {
            return false;
        }
    }

    {
        Response mismatch;
        mismatch.set_id(5);
        mismatch.mutable_step();
        if (MatchPendingResponse(Response::kObservation, 5, mismatch) != PendingMatch::Mismatch) {
            return false;
        }
    }

    {
        Response wait;
        wait.mutable_step();
        if (MatchPendingResponse(Response::kObservation, 5, wait) != PendingMatch::Wait) {
            return false;
        }
    }

    {
        Response err;
        err.set_id(5);
        err.add_error("warning");
        err.mutable_observation();
        if (MatchPendingResponse(Response::kObservation, 5, err) != PendingMatch::Accept) {
            return false;
        }
    }

    {
        Response err_no_id;
        err_no_id.add_error("warning");
        if (MatchPendingResponse(Response::kObservation, 5, err_no_id) != PendingMatch::Accept) {
            return false;
        }
    }

    {
        Response ok;
        ok.set_id(5);
        ok.mutable_observation();
        if (MatchPendingResponse(Response::kObservation, 5, ok) != PendingMatch::Accept) {
            return false;
        }
    }

    return true;
}

}  // namespace sc2
