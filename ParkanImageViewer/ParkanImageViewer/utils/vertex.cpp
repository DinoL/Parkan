#include "vertex.h"

InputBinaryStream& operator>>(InputBinaryStream& s, Vertex& v)
{
    s >> v.x >> v.y >> v.z;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Vertex& v)
{
    s << v.x << v.y << v.z;
    return s;
}

std::wostream& operator<<(std::wostream& s, const Vertex& v)
{
    s << v.x << ' ' << v.y << ' ' << v.z;
    return s;
}

std::wistream& operator>>(std::wistream& s, Vertex& v)
{
    s >> v.x >> v.y >> v.z;
    return s;
}
