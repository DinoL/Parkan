#include "vector_2d.h"

InputBinaryStream& operator>>(InputBinaryStream& s, Vector2d& v)
{
    s >> v.u >> v.v;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Vector2d& v)
{
    s << v.u << v.v;
    return s;
}

std::wostream& operator<<(std::wostream& s, const Vector2d& v)
{
    s << v.u << ' ' << v.v;
    return s;
}

std::wistream& operator>>(std::wistream& s, Vector2d& v)
{
    s >> v.u >> v.v;
    return s;
}
