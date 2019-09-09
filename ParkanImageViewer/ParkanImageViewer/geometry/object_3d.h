#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "utils/vertex.h"
#include "face.h"
#include "serializable_geometry.h"

#include <QDir>
#include <QString>
#include <QFileInfo>

#include <vector>
#include <set>

class Object3d : public SerializableGeometry
{
public:
    virtual std::vector<Vertex> get_vertices() const override;
    virtual std::vector<Face> get_faces() const override;

    virtual QString get_textures_palette_name() const override;
    virtual std::set<QString> all_texture_names() const override;

    virtual bool is_empty() const override;

private:
    virtual void read(std::wistream& io_s) override;
    virtual void write(std::wostream& io_s) const override;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    float m_scale = 1.f;
};

#endif // OBJECT_3D_H
