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
std::wostream& operator<<(std::wostream& s, const Vector2d& v);
std::wistream& operator>>(std::wistream& s, Vector2d& v);

#endif // VECTOR_2D_H
