#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include <map>
#include <vector>
#include <string>
#include "interior.h"
#include <fstream>
#include <QFileInfo>


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

    int add_one(const UV& uv);
};

struct ObjVertex
{
    int vid;
    int uvid;
};

struct ObjFace
{
    std::string texture;
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
