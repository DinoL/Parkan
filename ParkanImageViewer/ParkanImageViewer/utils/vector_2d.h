#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include "binary_stream.h"

#include <iostream>

struct Vector2d
{
    float u;
    float v;
};

InputBinaryStream& operator>>(InputBinaryStream& s, Vector2d& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Vector2d& v);
std::ostream& operator<<(std::ostream& s, const Vector2d& v);
std::istream& operator>>(std::istream& s, Vector2d& v);

#endif // VECTOR_2D_H
