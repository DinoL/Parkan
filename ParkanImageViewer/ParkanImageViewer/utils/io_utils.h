#ifndef IO_UTILS_H
#define IO_UTILS_H

#include "binary_stream.h"

#include <QString>

#include <iostream>
#include <string>
#include <vector>

std::wostream& operator<<(std::wostream& s, const QString& i_str);
std::wistream& operator>>(std::wistream& s, QString& o_str);

template<typename T>
InputBinaryStream& operator>>(InputBinaryStream& s, std::vector<T>& o_arr)
{
    quint16 size;
    s >> size;
    o_arr.resize(size);
    for(T& el : o_arr)
    {
        s >> el;
    }
    return s;
}

template<typename T>
OutputBinaryStream& operator<<(OutputBinaryStream& s, const std::vector<T>& i_arr)
{
    quint16 size = static_cast<quint16>(i_arr.size());
    s << size;

    for(const T& el : i_arr)
    {
        s << el;
    }
    return s;
}

template<typename T>
std::wostream& operator<<(std::wostream& s, const std::vector<T>& o_arr)
{
    size_t size = o_arr.size();
    s << "Size: " << size << std::endl;

    for(const T& el : o_arr)
    {
        s << el << std::endl;
    }
    return s;
}


#endif // IO_UTILS_H
