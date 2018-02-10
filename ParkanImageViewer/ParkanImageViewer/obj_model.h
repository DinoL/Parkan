#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include "interior.h"

#include <QString>
#include <QFileInfo>

#include <map>
#include <vector>
#include <string>
#include <fstream>

struct UV
{
    float u;
    float v;
};

struct PolygonVertex
{
    float x;
    float y;
    float z;
};

struct AllUVs
{
    std::vector<UV> uvs;

    size_t add_one(const UV& uv);
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

    void save(const std::string& i_to, const std::string& i_mtl_file) const;

private:
    void save_material_file(const std::string& to) const;

private:
    std::vector<PolygonVertex> vxs;
    AllUVs uvs;
    std::vector<ObjFace> fs;
};

#endif // OBJ_MODEL_H
