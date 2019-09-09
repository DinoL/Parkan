#ifndef FACE_H
#define FACE_H

#include "utils/binary_stream.h"
#include "utils/vertex.h"
#include "utils/vector_2d.h"

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
    std::wstring texture;

};

InputBinaryStream& operator>>(InputBinaryStream& s, Face& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Face& v);
std::wostream& operator<<(std::wostream& s, const Face& v);
std::wistream& operator>>(std::wistream& s, Face& v);

#endif // FACE_H
