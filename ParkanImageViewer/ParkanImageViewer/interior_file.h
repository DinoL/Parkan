#ifndef INTERIOR_FILE_H
#define INTERIOR_FILE_H

#include "serializable_geometry.h"
#include "interior.h"

#include <vector>

class InteriorFile : public SerializableGeometry
{
public:
    std::vector<Vertex> m_vertices;                       // size 12
    std::vector<VerticalPolygon> m_vertical_polygons;     // size 114
    std::vector<HorizontalPolygon> m_horizontal_polygons; // size 128
    std::vector<VertexInfo> m_vertex_infos;               // size 16
    std::vector<InteriorSignature> m_signature;           // size 20

    virtual QString get_textures_palette_name() const override;
    virtual QDir get_textures_folder() const override;
    virtual  std::set<QString> all_texture_names() const override;

private:
    virtual void read(std::istream& io_s) override;
    virtual void write(std::ostream& io_s) const override;
};

#endif // INTERIOR_FILE_H
