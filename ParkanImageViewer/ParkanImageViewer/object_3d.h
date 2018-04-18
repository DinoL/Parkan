#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "vertex.h"
#include "face.h"
#include "geometry_3d.h"

#include <QDir>
#include <QString>
#include <QFileInfo>

#include <vector>
#include <set>
#include <iostream>

class Object3d : public Geometry3d
{
public:
    Object3d();
    Object3d(std::istream& io_s);

    std::vector<Vertex> get_vertices() const;
    std::vector<Face> get_faces() const;

    virtual QString get_textures_palette_name() const override;
    virtual QDir get_textures_folder() const override;
    virtual std::set<QString> all_texture_names() const override;

    friend std::ostream& operator<<(std::ostream& io_s, const Object3d& i_obj);
    friend std::istream& operator>>(std::istream& io_s, Object3d& o_obj);

private:
    void read(std::istream& io_s);
    void write(std::ostream& io_s) const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    float m_scale = 1.f;
};

#endif // OBJECT_3D_H
