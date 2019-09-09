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
std::wostream& operator<<(std::wostream& s, const Vertex& v);
std::wistream& operator>>(std::wistream& s, Vertex& v);

#endif // VERTEX_H
