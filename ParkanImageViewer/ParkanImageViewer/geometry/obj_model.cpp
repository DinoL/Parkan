#include "obj_model.h"

#include "utils/io_utils.h"

ObjModel::ObjModel(const SerializableGeometry& i_geometry)
{
    m_vertices = i_geometry.get_vertices();

    for(const Face& poly : i_geometry.get_faces())
    {
        ObjFace cur_poly;
        cur_poly.texture = QString(poly.texture.c_str());
        for(int i = 0; i < poly.pts.size(); ++i)
        {
            ObjVertex cur_vx;

            const FacePoint& cur = poly.pts[i];
            cur_vx.vid = cur.id + 1;
            cur_vx.uvid = m_uvs.add_one(cur.uv) + 1;

            cur_poly.face_vxs.push_back(cur_vx);
        }
        m_faces.push_back(cur_poly);
    }
}

bool ObjModel::save_material_file(const QFileInfo& i_to) const
{
    std::set<QString> textures;
    for(const auto& face : m_faces)
    {
        textures.insert(face.texture);
    }

    std::ofstream out(i_to.absoluteFilePath().toStdWString());
    if(!out.good())
        return false;

    for(const auto& texture : textures)
    {
        out << "newmtl " << texture << std::endl;
        out << "map_Kd " << texture << ".png" << std::endl;
    }
    return true;
}

bool ObjModel::save(const QFileInfo& i_to) const
{
    const QFileInfo mtl_file(i_to.absoluteDir().absoluteFilePath(i_to.baseName() + ".mtl"));
    save_material_file(mtl_file);

    std::ofstream out(i_to.absoluteFilePath().toStdWString());
    if(!out.good())
        return false;

    out << "mtllib " << mtl_file.fileName().toStdString() << std::endl;
    for(const Vertex& vertex : m_vertices)
    {
        out << "v " << vertex << std::endl;
    }

    for(const Vector2d& uv : m_uvs.uvs)
    {
        out << "vt " << uv.u << ' ' << 1 - uv.v << std::endl;
    }

    for(const ObjFace& face : m_faces)
    {
        out << "usemtl " << face.texture << std::endl;
        out << "f";
        for(const auto& vv : face.face_vxs)
        {
            out << " " << vv.vid << "/" << vv.uvid;
        }
        out << std::endl;
    }
    std::wcout << "Successfully exported to " << i_to.absoluteFilePath().toStdWString() << std::endl;
    std::wcout << "Material file: " << mtl_file.absoluteFilePath().toStdWString() << std::endl;

    return true;
}

size_t AllUVs::add_one(const Vector2d& uv)
{
    uvs.push_back(uv);
    return uvs.size() - 1;
}
