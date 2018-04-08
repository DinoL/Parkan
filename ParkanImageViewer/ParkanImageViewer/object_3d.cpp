#include "object_3d.h"

void Object3d::read(std::istream& i_s)
{
    int vertices_cnt;
    float scale;
    i_s >> vertices_cnt >> scale;
    m_vertices.resize(vertices_cnt);
    for(Vertex& v : m_vertices)
    {
        i_s >> v;
    }
    m_vertices;
}
