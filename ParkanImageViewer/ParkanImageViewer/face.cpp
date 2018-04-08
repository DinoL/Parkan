#include "face.h"

InputBinaryStream& operator>>(InputBinaryStream& s, Face& f)
{
    for(Vertex& v : f.vx)
    {
        s >> v;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Face& f)
{
    for(const Vertex& v : f.vx)
    {
        s << v;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const Face& f)
{
    s << "Face(";
    for(const Vertex& v : f.vx)
    {
        s << v << ' ';
    }
    s << ") ";
    return s;
}

std::istream& operator>>(std::istream& s, Face& f)
{
    for(Vertex& v : f.vx)
    {
        s >> v;
    }
    return s;
}
