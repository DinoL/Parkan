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

std::ostream& operator<<(std::ostream& s, const Vector2d& v)
{
    s << v.u << ' ' << v.v;
    return s;
}

std::istream& operator>>(std::istream& s, Vector2d& v)
{
    s >> v.u >> v.v;
    return s;
}
