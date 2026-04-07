#pragma once

#include <exception>
#include <expected>

class Error : public std::exception {
    public:
        const char* what() const noexcept { return "error"; }
};

class RangeError : public Error {
    private:
        const char* msg;
    public:
        RangeError(const char* s) : msg(s) {}
        const char *what() const noexcept {
            return msg;
  }
};

class ZeroError : public Error {
    public:
        const char *what() const noexcept { return "Zero error"; }
};  

class InvalidArgumentError : public Error {
    private:
        const char* msg;
    public:
        InvalidArgumentError(const char* s) : msg(s) {}
        const char *what() const noexcept {
            return msg;
}};