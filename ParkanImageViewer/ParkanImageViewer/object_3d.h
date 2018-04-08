#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "vertex.h"
#include "face.h"

#include <QDir>
#include <QString>
#include <QFileInfo>

#include <vector>
#include <set>

class Object3d
{
public:
    Object3d()
    {}

    void read(std::istream& i_s);

    std::vector<Vertex> get_vertices() const;
    std::vector<Face> get_faces() const;

    static QString get_textures_palette_name();
    static QDir get_textures_folder();
    static QFileInfo get_texture_fullpath(const QString& i_texture_name);
    std::set<QString> all_texture_names() const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
};

#endif // OBJECT_3D_H
