#include "interior.h"

#include <QByteArray>

InputBinaryStream& operator>>(InputBinaryStream& s, CoordinatesShort& v)
{
    s >> v.i >> v.j >> v.k;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const CoordinatesShort& v)
{
    s << v.i << v.j << v.k;
    return s;
}

std::ostream& operator<<(std::ostream& s, const CoordinatesShort& v)
{
    s << "Indices(" << v.i << ' ' << v.j << ' ' << v.k << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, Point& v)
{
    s >> v.id >> v.u >> v.v;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const Point& v)
{
    s << v.id << v.u << v.v;
    return s;
}

std::ostream& operator<<(std::ostream& s, const Point& v)
{
    s << "Point(" << v.id << ' ' << v.u << ' ' << v.v << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, ShortPair& v)
{
    s >> v.x >> v.y;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortPair& v)
{
    s << v.x << v.y;
    return s;
}

std::ostream& operator<<(std::ostream& s, const ShortPair& v)
{
    s << "IndicesPair(" << v.x << ' ' << v.y << ") ";
    return s;
}

QString ShortString::to_string() const
{
    int i = 0;
    while(i < 16 && !isprint(str[i]))
        ++i;

    int j = i;
    while(j < 16 && isprint(str[j]))
        ++j;

    return QString(QByteArray(str + i, j - i));
}


InputBinaryStream& operator>>(InputBinaryStream& s, ShortString& v)
{
    for(auto& el : v.str)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortString& v)
{
    for(const auto& el : v.str)
    {
        s << el;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const ShortString& v)
{
    s << "\"";
    s << v.to_string().toStdString();
    s << "\" ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, SmallIndices& v)
{
    s >> v.m >> v.c >> v.d;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const SmallIndices& v)
{
    s << v.m << v.c << v.d;
    return s;
}

std::ostream& operator<<(std::ostream& s, const SmallIndices& v)
{
    s << "SmallIndices(" << v.m << ' ' << int(v.c) << ' ' << int(v.d) << ") ";
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, VerticalPolygon& v)
{
    for(auto& el : v.ps)
    {
        s >> el;
    }
    s >> v.texture >> v.ind >> v.c;
    for(auto& el : v.vs)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const VerticalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el;
    }
    s << v.texture << v.ind << v.c;
    for(const auto& el : v.vs)
    {
        s << el;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const VerticalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el << std::endl;
    }
    s << v.texture << std::endl;
    s << v.ind << std::endl;
    s << v.c << std::endl;
    for(const auto& el : v.vs)
    {
        s << el << std::endl;
    }
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, HorizontalPolygon& v)
{
    for(auto& el : v.ps)
    {
        s >> el;
    }
    s >> v.texture >> v.ind >> v.sp;
    for(auto& el : v.fs)
    {
        s >> el;
    }
    for(auto& el : v.vs)
    {
        s >> el;
    }
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const HorizontalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el;
    }
    s << v.texture << v.ind << v.sp;
    for(const auto& el : v.fs)
    {
        s << el;
    }
    for(const auto& el : v.vs)
    {
        s << el;
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const HorizontalPolygon& v)
{
    for(const auto& el : v.ps)
    {
        s << el << std::endl;
    }

    s << v.texture << std::endl;
    s << v.ind << std::endl;
    s << v.sp << std::endl;

    for(const auto& el : v.fs)
    {
        s << el << ' ';
    }
    s << std::endl;
    for(const auto& el : v.vs)
    {
        s << el << std::endl;
    }
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, VertexInfo& v)
{
    s >> v.v >> v.sp;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const VertexInfo& v)
{
    s << v.v << v.sp;
    return s;
}

std::ostream& operator<<(std::ostream& s, const VertexInfo& v)
{
    s << v.v << v.sp;
    return s;
}

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorSignature& v)
{
    s >> v.sp >> v.signature;
    return s;
}

OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorSignature& v)
{
    s << v.sp << v.signature;
    return s;
}

std::ostream& operator<<(std::ostream& s, const InteriorSignature& v)
{
    s << v.sp << v.signature;
    return s;
}

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

QString InteriorFile::get_textures_palette_name()
{
    return "PAL.PAL";
}

QDir InteriorFile::get_textures_folder()
{
    return QDir(R"(C:\Users\Leonid\Downloads\PARKAN THE IMPERIAL CHRONICLES\TEXTURES.LIB.dir)");
}

QFileInfo InteriorFile::get_texture_fullpath(const QString& i_texture_name)
{
    return QFileInfo(InteriorFile::get_textures_folder(), i_texture_name);
}

std::set<QString> InteriorFile::all_texture_names() const
{
    std::set<QString> texture_names;
    for(const auto& p : vertical_polygons.vec)
    {
        texture_names.insert(InteriorFile::get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    for(const auto& p : horizontal_polygons.vec)
    {
        texture_names.insert(InteriorFile::get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    return texture_names;
}
