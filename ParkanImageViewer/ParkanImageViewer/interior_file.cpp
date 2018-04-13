#include "interior_file.h"

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file)
{
    s >> file.vertices;
    s >> file.vertical_polygons;
    s >> file.horizontal_polygons;
    s >> file.vertex_infos;
    s >> file.signature;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file)
{
    s << file.vertices;
    s << file.vertical_polygons;
    s << file.horizontal_polygons;
    s << file.vertex_infos;
    s << file.signature;
    return s;
}

std::ostream& operator<<(std::ostream& s, const InteriorFile& file)
{
    s << "Vertices:\n"            << file.vertices            << std::endl;
    s << "Vertical polygons:\n"   << file.vertical_polygons   << std::endl;
    s << "Horizontal polygons:\n" << file.horizontal_polygons << std::endl;
    s << "Block 4:\n"             << file.vertex_infos        << std::endl;
    s << "Signature:\n"           << file.signature           << std::endl;
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
    for(const auto& p : vertical_polygons.vec)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    for(const auto& p : horizontal_polygons.vec)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    return texture_names;
}
