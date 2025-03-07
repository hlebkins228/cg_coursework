#ifndef ERRORS_H_

#define ERRORS_H_

#include <exception>
#include <string>


class BaseError: public std::exception
{
protected:
    std::string error_info;

public:
    BaseError(std::string info = "Error") : error_info(info) {};
    virtual ~BaseError() {};

    virtual const char* what() const noexcept override
    {
        return error_info.c_str();
    }

    std::string whatStr() const noexcept
    {
        return error_info;
    }
};

class WindowCreateError: public BaseError
{
public:
    WindowCreateError(std::string info = "Failed to create GLFW window!") : BaseError(info) {};
};

class InvalidArgs: public BaseError
{
public:
    InvalidArgs(std::string info = "Invalid function argument!") : BaseError(info) {};
};

class InvalidCord: public BaseError
{
public:
    InvalidCord(std::string info = "Invalid cord!") : BaseError(info) {}
};

class MemoryAllocError: public BaseError
{
public:
    MemoryAllocError(std::string info = "Memory allocation error!") : BaseError(info) {}
};

class ModelNotReady: public BaseError
{
public:
    ModelNotReady(std::string info = "Model not ready to render!") : BaseError(info) {}
};

class FileOpenError: public BaseError
{
public:
    FileOpenError(std::string info = "File open error!") : BaseError(info) {}
};

class NoShaderSource: public BaseError
{
public:
    NoShaderSource(std::string info = "No shader source!") : BaseError(info) {}
};

class ModelReadError: public BaseError
{
public:
    ModelReadError(std::string info = "model read error!") : BaseError(info) {}
};

#endif
