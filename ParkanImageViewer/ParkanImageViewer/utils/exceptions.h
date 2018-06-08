#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "string_utils.h"

#include <QString>

#include <stdexcept>
#include <string>

class ImageDataException : public std::runtime_error
{
public:
    template<typename T>
    ImageDataException(const T& i_msg) : std::runtime_error(to_std_string(i_msg).c_str())
    {}
};

class LoadImageDataException : public ImageDataException
{
public:
    template<typename T>
    LoadImageDataException(const T& i_msg) : ImageDataException(i_msg)
    {}
};

class DecodeImageDataException : public ImageDataException
{
public:
    template<typename T>
    DecodeImageDataException(const T& i_msg) : ImageDataException(i_msg)
    {}
};

class GeometryException : public std::runtime_error
{
    template<typename T>
    GeometryException(const T& i_msg) : std::runtime_error(to_std_string(i_msg).c_str())
    {}
};

#endif // EXCEPTIONS_H
