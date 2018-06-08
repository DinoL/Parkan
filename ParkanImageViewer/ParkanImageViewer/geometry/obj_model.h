#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include "serializable_geometry.h"

#include <QString>
#include <QFileInfo>

#include <map>
#include <vector>
#include <string>
#include <fstream>

struct AllUVs
{
    std::vector<Vector2d> uvs;

    size_t add_one(const Vector2d& uv);
};

struct ObjVertex
{
    size_t vid;
    size_t uvid;
};

struct ObjFace
{
    QString texture;
    std::vector<ObjVertex> face_vxs;
};

class ObjModel
{
public:
    ObjModel(const SerializableGeometry& i_geometry);

    void save(const QFileInfo& i_to) const;

private:
    void save_material_file(const QFileInfo& i_to) const;

private:
    std::vector<Vertex> m_vertices;
    AllUVs m_uvs;
    std::vector<ObjFace> m_faces;
};

#endif // OBJ_MODEL_H
