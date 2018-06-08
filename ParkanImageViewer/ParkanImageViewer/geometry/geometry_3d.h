#ifndef GEOMETRY_3D_H
#define GEOMETRY_3D_H

#include "utils/vertex.h"
#include "face.h"

#include <QString>
#include <QDir>
#include <QFileInfo>

#include <set>

class IGeometry3d
{
public:
    virtual std::vector<Vertex> get_vertices() const = 0;
    virtual std::vector<Face> get_faces() const = 0;

    virtual QString get_textures_palette_name() const = 0;
    virtual std::set<QString> all_texture_names() const = 0;

    virtual bool is_empty() const = 0;
};

#endif // GEOMETRY_3D_H
