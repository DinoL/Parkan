#ifndef INTERIOR_H
#define INTERIOR_H

#include "binary_stream.h"
#include <vector>
#include <iostream>

struct Vertex
{
    float x;
    float y;
    float z;
};

InputBinaryStream& operator>>(InputBinaryStream& s, Vertex& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Vertex& v);
std::ostream& operator<<(std::ostream& s, const Vertex& v);

struct CoordinatesShort
{
    short i;
    short j;
    short k;
};

InputBinaryStream& operator>>(InputBinaryStream& s, CoordinatesShort& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const CoordinatesShort& v);
std::ostream& operator<<(std::ostream& s, const CoordinatesShort& v);

struct Point
{
    short id;
    float u;
    float v;
};

InputBinaryStream& operator>>(InputBinaryStream& s, Point& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Point& v);
std::ostream& operator<<(std::ostream& s, const Point& v);

struct ShortPair
{
    short x;
    short y;
};

InputBinaryStream& operator>>(InputBinaryStream& s, ShortPair& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortPair& v);
std::ostream& operator<<(std::ostream& s, const ShortPair& v);

struct ShortString
{
    char str[16];
};

InputBinaryStream& operator>>(InputBinaryStream& s, ShortString& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortString& v);
std::ostream& operator<<(std::ostream& s, const ShortString& v);

struct SmallIndices
{
    short m;
    char c;
    char d;
};

InputBinaryStream& operator>>(InputBinaryStream& s, SmallIndices& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const SmallIndices& v);
std::ostream& operator<<(std::ostream& s, const SmallIndices& v);

struct VerticalPolygon
{
    Point ps[4];
    ShortString texture;
    SmallIndices ind;
    CoordinatesShort c;
    Vertex vs[4];
};

InputBinaryStream& operator>>(InputBinaryStream& s, VerticalPolygon& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const VerticalPolygon& v);
std::ostream& operator<<(std::ostream& s, const VerticalPolygon& v);

struct HorizontalPolygon
{
    Point ps[4];
    ShortString texture;
    SmallIndices ind;
    ShortPair sp;
    float fs[4];
    Vertex vs[4];
};

InputBinaryStream& operator>>(InputBinaryStream& s, HorizontalPolygon& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const HorizontalPolygon& v);
std::ostream& operator<<(std::ostream& s, const HorizontalPolygon& v);

struct VertexInfo
{
    Vertex v;
    ShortPair sp;
};

InputBinaryStream& operator>>(InputBinaryStream& s, VertexInfo& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const VertexInfo& v);
std::ostream& operator<<(std::ostream& s, const VertexInfo& v);


struct InteriorSignature
{
    ShortPair sp;
    ShortString signature;
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorSignature& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorSignature& v);
std::ostream& operator<<(std::ostream& s, const InteriorSignature& v);


template<typename T>
struct DataArray
{
    std::vector<T> vec;
};

template<typename T>
InputBinaryStream& operator>>(InputBinaryStream& s, DataArray<T>& arr)
{
    std::cout << "Reading ObjectsArray " << std::endl;
    quint16 size;
    s >> size;
    std::cout << "Size is " << size << std::endl;
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
    quint16 size = arr.vec.size();
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
    quint16 size = arr.vec.size();
    s << "Size: " << size << std::endl;

    for(const auto& el : arr.vec)
    {
        s << el << std::endl;
    }
    return s;
}

struct InteriorFile
{
    DataArray<Vertex> vertices;                       // size 12
    DataArray<VerticalPolygon> vertical_polygons;     // size 114
    DataArray<HorizontalPolygon> horizontal_polygons; // size 128
    DataArray<VertexInfo> vertex_infos;               // size 16
    DataArray<InteriorSignature> signature;           // size 20
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file);
std::ostream& operator<<(std::ostream& s, const InteriorFile& file);

#endif // INTERIOR_H
