#include "object_3d.h"

#include <iomanip>

void Object3d::read(std::istream& io_s)
{
    int vertices_cnt;
    io_s >> vertices_cnt >> m_scale;
    m_vertices.resize(vertices_cnt);
    for(Vertex& v : m_vertices)
    {
        io_s >> v;
    }
    int faces_cnt;
    io_s >> faces_cnt;
    m_faces.resize(faces_cnt);
    for(Face& f : m_faces)
    {
        io_s >> f;
    }
}

void Object3d::write(std::ostream& io_s) const
{
    io_s << m_vertices.size() << ' ' << m_scale << std::endl;
    io_s << std::fixed << std::setprecision(6);
    for(const Vertex& v : m_vertices)
    {
        io_s << v << std::endl;
    }
    io_s << m_faces.size() << std::endl;
    for(const Face& f : m_faces)
    {
        io_s << f;
    }
}

std::vector<Vertex> Object3d::get_vertices() const
{
    return m_vertices;
}

std::vector<Face> Object3d::get_faces() const
{
    return m_faces;
}

QString Object3d::get_textures_palette_name() const
{
    return "Space";
}

std::set<QString> Object3d::all_texture_names() const
{
    std::set<QString> texture_names;
    for(const Face& f : get_faces())
    {
        texture_names.insert(QString(f.texture.c_str()));
    }
    return texture_names;
}

bool Object3d::is_empty() const
{
    return m_vertices.empty() || m_faces.empty();
}

