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
    int faces_cnt;
    i_s >> faces_cnt;
    m_faces.resize(faces_cnt);
    for(Face& f : m_faces)
    {
        i_s >> f;
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
    return "PAL.PAL";
}

QDir Object3d::get_textures_folder() const
{
    return QDir(R"(C:\Users\Leonid\Downloads\PARKAN THE IMPERIAL CHRONICLES\TEXTUR3D.LIB.dir)");
}

std::set<QString> Object3d::all_texture_names() const
{
    std::set<QString> texture_names;
    for(const Face& f : get_faces())
    {
        texture_names.insert(get_texture_fullpath(QString(f.texture.c_str())).absoluteFilePath());
    }
    return texture_names;
}
