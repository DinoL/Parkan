#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "vertex.h"
#include "face.h"

#include <vector>

class Object3d
{
public:
    Object3d()
    {}

    void read(std::istream& i_s);

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
};

#endif // OBJECT_3D_H
