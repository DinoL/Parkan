#include "interior_file.h"

#include "io_utils.h"

void InteriorFile::read(std::istream& io_s)
{
    InputBinaryStream bis(io_s);
    bis >> m_vertices;
    bis >> m_vertical_polygons;
    bis >> m_horizontal_polygons;
    bis >> m_vertex_infos;
    bis >> m_signature;
}

void InteriorFile::write(std::ostream& io_s) const
{
    OutputBinaryStream bos(io_s);
    bos << m_vertices;
    bos << m_vertical_polygons;
    bos << m_horizontal_polygons;
    bos << m_vertex_infos;
    bos << m_signature;
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

