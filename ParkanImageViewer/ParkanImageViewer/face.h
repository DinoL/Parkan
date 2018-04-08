#ifndef FACE_H
#define FACE_H

#include "binary_stream.h"
#include "vertex.h"
#include "vector_2d.h"

#include <iostream>
#include <string>
#include <vector>

struct FacePoint
{
    int id;
    Vector2d uv;
    int k;
};

struct Face
{
    std::vector<FacePoint> pts;
    std::string texture;

};

InputBinaryStream& operator>>(InputBinaryStream& s, Face& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Face& v);
std::ostream& operator<<(std::ostream& s, const Face& v);
std::istream& operator>>(std::istream& s, Face& v);

#endif // FACE_H
