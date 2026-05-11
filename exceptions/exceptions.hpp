#pragma once

#include <exception>
#include <expected>
#include <string>

class Error : public std::exception {
    private:
        std::string msg_;
    public:
        Error(const std::string& msg) : msg_(msg) {}
        const char* what() const noexcept override { 
            return msg_.c_str(); 
    }
};

class RangeError : public Error {
    public:
        RangeError(size_t index, size_t size) : Error("Index " + std::to_string(index) + "out of range [0, " + std::to_string(size - 1) +"]" ) {}
}; 

class InvalidArgumentError : public Error {
    public:
        InvalidArgumentError(const std::string& invalid_argument) : Error("Invalid argument: " + invalid_argument) {}
};

class FailedAllocationError : public Error {
    public:
        FailedAllocationError(const std::string& details) : Error("Allocation failed: " + details) {}
};

class EmptyBufferError : public Error {
    public:
        EmptyBufferError(const std::string& details) : Error("Buffer is empty") {}
};
