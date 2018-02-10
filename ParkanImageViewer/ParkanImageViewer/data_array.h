#ifndef DATA_ARRAY_H
#define DATA_ARRAY_H

#include "binary_stream.h"

#include <vector>
#include <iostream>

template<typename T>
struct DataArray
{
    std::vector<T> vec;
};

template<typename T>
InputBinaryStream& operator>>(InputBinaryStream& s, DataArray<T>& arr)
{
    quint16 size;
    s >> size;
    arr.vec.resize(size);
    for(auto& el : arr.vec)
    {
        s >> el;
    }
    return s;
}

template<typename T>
OutputBinaryStream& operator<<(OutputBinaryStream& s, const DataArray<T>& arr)
{
    quint16 size = static_cast<quint16>(arr.vec.size());
    s << size;

    for(const auto& el : arr.vec)
    {
        s << el;
    }
    return s;
}

template<typename T>
std::ostream& operator<<(std::ostream& s, const DataArray<T>& arr)
{
    size_t size = arr.vec.size();
    s << "Size: " << size << std::endl;

    for(const auto& el : arr.vec)
    {
        s << el << std::endl;
    }
    return s;
}



#endif // DATA_ARRAY_H
