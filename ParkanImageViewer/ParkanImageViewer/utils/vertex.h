#ifndef VERTEX_H
#define VERTEX_H

#include "binary_stream.h"

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
std::istream& operator>>(std::istream& s, Vertex& v);

#endif // VERTEX_H
