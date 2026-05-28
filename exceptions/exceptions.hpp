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

class OptionalError : public Error {
    public:
        OptionalError(const std::string& details) : Error(details) {}
};

class CardinalError : public Error {
    public:
        CardinalError(const std::string& details) : Error(details) {}
};

class OrdinalError : public Error {
    public:
        OrdinalError(const std::string& details) : Error(details) {}
};

class StreamOpenError : public Error {
public:
    explicit StreamOpenError(const std::string& filename) 
        : Error("failed to open file " + filename) {}
};

class EndOfStreamError : public Error {
public:
    EndOfStreamError() : Error("end of stream reached") {}
};