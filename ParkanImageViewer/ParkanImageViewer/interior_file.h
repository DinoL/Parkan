#ifndef INTERIOR_FILE_H
#define INTERIOR_FILE_H

#include "geometry_3d.h"
#include "interior.h"

class InteriorFile : public Geometry3d
{
public:
    DataArray<Vertex> vertices;                       // size 12
    DataArray<VerticalPolygon> vertical_polygons;     // size 114
    DataArray<HorizontalPolygon> horizontal_polygons; // size 128
    DataArray<VertexInfo> vertex_infos;               // size 16
    DataArray<InteriorSignature> signature;           // size 20

    virtual QString get_textures_palette_name() const override;

    virtual QDir get_textures_folder() const override;

    virtual  std::set<QString> all_texture_names() const override;
};

InputBinaryStream& operator>>(InputBinaryStream& s, InteriorFile& file);
OutputBinaryStream& operator<<(OutputBinaryStream& s, const InteriorFile& file);
std::ostream& operator<<(std::ostream& s, const InteriorFile& file);

#endif // INTERIOR_FILE_H
