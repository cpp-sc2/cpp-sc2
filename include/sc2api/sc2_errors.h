#pragma once

#include <exception>
#include <string>

namespace sc2 {

struct ClientConnectionError: std::runtime_error {
    ClientConnectionError(const std::string& net_address_, int port_):
        std::runtime_error("Failed connect to client " + net_address_ + ":" + std::to_string(port_)) {
    }
};

}  // namespace sc2
