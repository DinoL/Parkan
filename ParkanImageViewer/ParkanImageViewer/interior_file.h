#ifndef INTERIOR_FILE_H
#define INTERIOR_FILE_H

#include "interior.h"

class InteriorFile
{
public:
    DataArray<Vertex> vertices;                       // size 12
    DataArray<VerticalPolygon> vertical_polygons;     // size 114
    DataArray<HorizontalPolygon> horizontal_polygons; // size 128
    DataArray<VertexInfo> vertex_infos;               // size 16
    DataArray<InteriorSignature> signature;           // size 20

    QString get_textures_palette_name() const;

    QDir get_textures_folder() const;

    QFileInfo get_texture_fullpath(const QString& i_texture_name) const;

    std::set<QString> all_texture_names() const;
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file);
std::ostream& operator<<(std::ostream& s, const InteriorFile& file);

#endif // INTERIOR_FILE_H
