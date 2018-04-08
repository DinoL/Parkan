#ifndef FACE_H
#define FACE_H

#include "binary_stream.h"
#include "vertex.h"

#include <iostream>

struct Face
{
    Vertex vx[3];

};

InputBinaryStream& operator>>(InputBinaryStream& s, Face& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Face& v);
std::ostream& operator<<(std::ostream& s, const Face& v);
std::istream& operator>>(std::istream& s, Face& v);

#endif // FACE_H
