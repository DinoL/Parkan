#include "obj_model.h"

#include "io_utils.h"

ObjModel::ObjModel(const SerializableGeometry& i_geometry)
{
    vxs = i_geometry.get_vertices();

    for(const Face& poly : i_geometry.get_faces())
    {
        ObjFace cur_poly;
        cur_poly.texture = QString(poly.texture.c_str());
        for(int i = 0; i < poly.pts.size(); ++i)
        {
            ObjVertex cur_vx;

            const FacePoint& cur = poly.pts[i];
            cur_vx.vid = cur.id + 1;
            cur_vx.uvid = uvs.add_one(cur.uv) + 1;

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

size_t AllUVs::add_one(const Vector2d& uv)
{
    uvs.push_back(uv);
    return uvs.size() - 1;
}
