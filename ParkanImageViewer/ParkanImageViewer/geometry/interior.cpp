#include "interior.h"

#include <QByteArray>

InputBinaryStream& operator>>(InputBinaryStream& s, CoordinatesShort& v)
{
    s >> v.i >> v.j >> v.k;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const CoordinatesShort& v)
{
    s << v.i << v.j << v.k;
    return s;
}

std::ostream& operator<<(std::ostream& s, const CoordinatesShort& v)
{
    s << "Indices(" << v.i << ' ' << v.j << ' ' << v.k << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, Point& v)
{
    s >> v.id >> v.u >> v.v;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Point& v)
{
    s << v.id << v.u << v.v;
    return s;
}

std::ostream& operator<<(std::ostream& s, const Point& v)
{
    s << "Point(" << v.id << ' ' << v.u << ' ' << v.v << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, ShortPair& v)
{
    s >> v.x >> v.y;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortPair& v)
{
    s << v.x << v.y;
    return s;
}

std::ostream& operator<<(std::ostream& s, const ShortPair& v)
{
    s << "IndicesPair(" << v.x << ' ' << v.y << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, SmallIndices& v)
{
    s >> v.m >> v.c >> v.d;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const SmallIndices& v)
{
    s << v.m << v.c << v.d;
    return s;
}

std::ostream& operator<<(std::ostream& s, const SmallIndices& v)
{
    s << "SmallIndices(" << v.m << ' ' << int(v.c) << ' ' << int(v.d) << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, VerticalPolygon& v)
{
    for(auto& el : v.ps)
    {
        s >> el;
    }
    s >> v.texture >> v.ind >> v.c;
    for(auto& el : v.vs)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const VerticalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el;
    }
    s << v.texture << v.ind << v.c;
    for(const auto& el : v.vs)
    {
        s << el;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const VerticalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el << std::endl;
    }
    s << v.texture << std::endl;
    s << v.ind << std::endl;
    s << v.c << std::endl;
    for(const auto& el : v.vs)
    {
        s << el << std::endl;
    }
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, HorizontalPolygon& v)
{
    for(auto& el : v.ps)
    {
        s >> el;
    }
    s >> v.texture >> v.ind >> v.sp;
    for(auto& el : v.fs)
    {
        s >> el;
    }
    for(auto& el : v.vs)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const HorizontalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el;
    }
    s << v.texture << v.ind << v.sp;
    for(const auto& el : v.fs)
    {
        s << el;
    }
    for(const auto& el : v.vs)
    {
        s << el;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const HorizontalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el << std::endl;
    }

    s << v.texture << std::endl;
    s << v.ind << std::endl;
    s << v.sp << std::endl;

    for(const auto& el : v.fs)
    {
        s << el << ' ';
    }
    s << std::endl;
    for(const auto& el : v.vs)
    {
        s << el << std::endl;
    }
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, VertexInfo& v)
{
    s >> v.v >> v.sp;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const VertexInfo& v)
{
    s << v.v << v.sp;
    return s;
}

std::ostream& operator<<(std::ostream& s, const VertexInfo& v)
{
    s << v.v << v.sp;
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorSignature& v)
{
    s >> v.sp >> v.signature;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorSignature& v)
{
    s << v.sp << v.signature;
    return s;
}

std::ostream& operator<<(std::ostream& s, const InteriorSignature& v)
{
    s << v.sp << v.signature;
    return s;
}

