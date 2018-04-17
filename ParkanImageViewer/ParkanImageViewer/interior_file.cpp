#include "interior_file.h"

#include "io_utils.h"

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file)
{
    s >> file.m_vertices;
    s >> file.m_vertical_polygons;
    s >> file.m_horizontal_polygons;
    s >> file.m_vertex_infos;
    s >> file.m_signature;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file)
{
    s << file.m_vertices;
    s << file.m_vertical_polygons;
    s << file.m_horizontal_polygons;
    s << file.m_vertex_infos;
    s << file.m_signature;
    return s;
}

std::ostream& operator<<(std::ostream& s, const InteriorFile& file)
{
    s << "Vertices:\n"            << file.m_vertices            << std::endl;
    s << "Vertical polygons:\n"   << file.m_vertical_polygons   << std::endl;
    s << "Horizontal polygons:\n" << file.m_horizontal_polygons << std::endl;
    s << "Block 4:\n"             << file.m_vertex_infos        << std::endl;
    s << "Signature:\n"           << file.m_signature           << std::endl;
    return s;
}

QString InteriorFile::get_textures_palette_name() const
{
    return "PAL.PAL";
}

QDir InteriorFile::get_textures_folder() const
{
    return QDir(R"(C:\Users\Leonid\Downloads\PARKAN THE IMPERIAL CHRONICLES\TEXTURES.LIB.dir)");
}

std::set<QString> InteriorFile::all_texture_names() const
{
    std::set<QString> texture_names;
    for(const auto& p : m_vertical_polygons)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    for(const auto& p : m_horizontal_polygons)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    return texture_names;
}
