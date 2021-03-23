#pragma once

#include <string>
#include <exception>

class ClientResponseError : public std::exception {
public:
 std::string reason="";
 ClientResponseError(const char* reason) {
	this->reason = std::string(reason);
 }
 virtual const char* what() const throw() {
	return reason.c_str();
 }

};
