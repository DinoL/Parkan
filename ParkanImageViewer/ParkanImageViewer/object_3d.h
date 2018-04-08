#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "vertex.h"

#include <vector>

class Object3d
{
public:
    Object3d()
    {}

private:
    std::vector<Vertex> vertices;
};

#endif // OBJECT_3D_H
