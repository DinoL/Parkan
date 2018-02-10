#include "obj_model.h"

ObjModel::ObjModel(const InteriorFile& i_interior)
{
    for(const auto& vx : i_interior.vertices.vec)
    {
        vxs.push_back(PolygonVertex{vx.x, vx.y, vx.z});
    }

    for(const auto& poly : i_interior.vertical_polygons.vec)
    {
        ObjFace cur_poly;
        cur_poly.texture = poly.texture.to_string();
        for(int i = 0; i < 4; ++i)
        {
            ObjVertex cur_vx;

            const auto& cur = poly.ps[i];
            cur_vx.vid = cur.id + 1;

            UV cur_uv{cur.u, cur.v};
            cur_vx.uvid = uvs.add_one(cur_uv) + 1;

            cur_poly.face_vxs.push_back(cur_vx);
        }
        fs.push_back(cur_poly);
    }
    for(const auto& poly : i_interior.horizontal_polygons.vec)
    {
        ObjFace cur_poly;
        cur_poly.texture = poly.texture.to_string();
        for(int i = 0; i < 4; ++i)
        {
            ObjVertex cur_vx;

            const auto& cur = poly.ps[i];
            cur_vx.vid = cur.id + 1;

            UV cur_uv{cur.u, cur.v};
            cur_vx.uvid = uvs.add_one(cur_uv) + 1;

            cur_poly.face_vxs.push_back(cur_vx);
        }
        fs.push_back(cur_poly);
    }
}

void ObjModel::save_material_file(const std::string& to) const
{
    std::set<QString> textures;
    for(const auto& f : fs)
    {
        textures.insert(f.texture);
    }

    std::ofstream out(to);
    for(const auto& t : textures)
    {
        out << "newmtl " << t << std::endl;
        out << "map_Kd " << t << ".png" << std::endl;
    }
}

void ObjModel::save(const std::string& i_to, const std::string& i_mtl_file) const
{
    save_material_file(i_mtl_file);

    QFileInfo mtl(QString(i_mtl_file.c_str()));

    std::ofstream out(i_to);
    out << "mtllib " << mtl.fileName().toStdString() << std::endl;
    for(const auto& v : vxs)
    {
        out << "v " << v.x << ' ' << v.y << ' ' << v.z << std::endl;
    }

    for(const auto& v : uvs.uvs)
    {
        out << "vt " << v.u << ' ' << 1-v.v << std::endl;
    }

    for(const auto& v : fs)
    {
        out << "usemtl " << v.texture << std::endl;
        out << "f";
        for(const auto& vv : v.face_vxs)
        {
            out << " " << vv.vid << "/" << vv.uvid;
        }
        out << std::endl;
    }
}

int AllUVs::add_one(const UV& uv)
{
    uvs.push_back(uv);
    return uvs.size() - 1;
}
