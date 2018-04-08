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

std::ostream& operator<<(std::ostream& s, const Vertex& v)
{
    s << "Vertex(" << v.x << ' ' << v.y << ' ' << v.z << ") ";
    return s;
}

std::istream&operator>>(std::istream& s, Vertex& v)
{
    s >> v.x >> v.y >> v.z;
    return s;
}
