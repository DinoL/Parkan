#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include "interior.h"
#include "object_3d.h"

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
    ObjModel(const InteriorFile& i_interior);
    ObjModel(const Object3d& i_object);

    void save(const std::string& i_to, const std::string& i_mtl_file) const;

private:
    void save_material_file(const std::string& to) const;

private:
    std::vector<Vertex> vxs;
    AllUVs uvs;
    std::vector<ObjFace> fs;
};

#endif // OBJ_MODEL_H
