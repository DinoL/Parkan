#ifndef GEOMETRY_3D_H
#define GEOMETRY_3D_H

#include "vertex.h"
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
    virtual QDir get_textures_folder() const = 0;
    virtual QFileInfo get_texture_fullpath(const QString&) const = 0;
    virtual std::set<QString> all_texture_names() const = 0;
};

class Geometry3d : public IGeometry3d
{
public:
    virtual QFileInfo get_texture_fullpath(const QString& i_texture_name) const final;
};

#endif // GEOMETRY_3D_H
