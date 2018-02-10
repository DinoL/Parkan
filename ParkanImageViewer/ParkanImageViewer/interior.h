#ifndef INTERIOR_H
#define INTERIOR_H

#include "io_utils.h"
#include "data_array.h"

#include <QString>
#include <QDir>
#include <QFileInfo>

#include <vector>
#include <set>
#include <string>
#include <iostream>

struct Vertex
{
    float x;
    float y;
    float z;
};

InputBinaryStream& operator>>(InputBinaryStream& s, Vertex& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Vertex& v);
std::ostream& operator<<(std::ostream& s, const Vertex& v);

struct CoordinatesShort
{
    short i;
    short j;
    short k;
};

InputBinaryStream& operator>>(InputBinaryStream& s, CoordinatesShort& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const CoordinatesShort& v);
std::ostream& operator<<(std::ostream& s, const CoordinatesShort& v);

struct Point
{
    short id;
    float u;
    float v;
};

InputBinaryStream& operator>>(InputBinaryStream& s, Point& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const Point& v);
std::ostream& operator<<(std::ostream& s, const Point& v);

struct ShortPair
{
    short x;
    short y;
};

InputBinaryStream& operator>>(InputBinaryStream& s, ShortPair& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortPair& v);
std::ostream& operator<<(std::ostream& s, const ShortPair& v);

struct ShortString
{
    char str[16];

    QString to_string() const;
};

InputBinaryStream& operator>>(InputBinaryStream& s, ShortString& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const ShortString& v);
std::ostream& operator<<(std::ostream& s, const ShortString& v);

struct SmallIndices
{
    short m;
    char c;
    char d;
};

InputBinaryStream& operator>>(InputBinaryStream& s, SmallIndices& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const SmallIndices& v);
std::ostream& operator<<(std::ostream& s, const SmallIndices& v);

struct VerticalPolygon
{
    Point ps[4];
    ShortString texture;
    SmallIndices ind;
    CoordinatesShort c;
    Vertex vs[4];
};

InputBinaryStream& operator>>(InputBinaryStream& s, VerticalPolygon& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const VerticalPolygon& v);
std::ostream& operator<<(std::ostream& s, const VerticalPolygon& v);

struct HorizontalPolygon
{
    Point ps[4];
    ShortString texture;
    SmallIndices ind;
    ShortPair sp;
    float fs[4];
    Vertex vs[4];
};

InputBinaryStream& operator>>(InputBinaryStream& s, HorizontalPolygon& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const HorizontalPolygon& v);
std::ostream& operator<<(std::ostream& s, const HorizontalPolygon& v);

struct VertexInfo
{
    Vertex v;
    ShortPair sp;
};

InputBinaryStream& operator>>(InputBinaryStream& s, VertexInfo& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const VertexInfo& v);
std::ostream& operator<<(std::ostream& s, const VertexInfo& v);


struct InteriorSignature
{
    ShortPair sp;
    ShortString signature;
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorSignature& v);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorSignature& v);
std::ostream& operator<<(std::ostream& s, const InteriorSignature& v);

struct InteriorFile
{
    DataArray<Vertex> vertices;                       // size 12
    DataArray<VerticalPolygon> vertical_polygons;     // size 114
    DataArray<HorizontalPolygon> horizontal_polygons; // size 128
    DataArray<VertexInfo> vertex_infos;               // size 16
    DataArray<InteriorSignature> signature;           // size 20

    static QString get_textures_palette_name();

    static QDir get_textures_folder();

    static QFileInfo get_texture_fullpath(const QString& i_texture_name);

    std::set<QString> all_texture_names() const;
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file);
std::ostream& operator<<(std::ostream& s, const InteriorFile& file);

#endif // INTERIOR_H
