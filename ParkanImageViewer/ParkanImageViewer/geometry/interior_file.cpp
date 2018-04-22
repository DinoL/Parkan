#include "interior_file.h"

#include "utils/io_utils.h"

void InteriorFile::read(std::istream& io_s)
{
    InputBinaryStream bis(io_s);
    bis >> m_vertices;
    bis >> m_vertical_polygons;
    bis >> m_horizontal_polygons;
    bis >> m_vertex_infos;
    bis >> m_signature;
}

void InteriorFile::write(std::ostream& io_s) const
{
    OutputBinaryStream bos(io_s);
    bos << m_vertices;
    bos << m_vertical_polygons;
    bos << m_horizontal_polygons;
    bos << m_vertex_infos;
    bos << m_signature;
}

std::vector<Vertex> InteriorFile::get_vertices() const
{
    return m_vertices;
}

FacePoint to_face_point(const Point& i_pt)
{
    return FacePoint{i_pt.id, Vector2d{i_pt.u, i_pt.v}, 1};
}

std::vector<Face> InteriorFile::get_faces() const
{
    std::vector<Face> faces;
    for(const auto& poly : m_vertical_polygons)
    {
        Face cur_face;
        cur_face.texture = poly.texture.to_string().toStdString();

        std::vector<FacePoint> points;
        for(const Point& pt : poly.ps)
        {
            points.push_back(to_face_point(pt));
        }
        cur_face.pts = points;
        faces.push_back(cur_face);
    }
    for(const auto& poly : m_horizontal_polygons)
    {
        Face cur_face;
        cur_face.texture = poly.texture.to_string().toStdString();

        std::vector<FacePoint> points;
        for(const Point& pt : poly.ps)
        {
            points.push_back(to_face_point(pt));
        }
        cur_face.pts = points;
        faces.push_back(cur_face);
    }
    return faces;
}

QString InteriorFile::get_textures_palette_name() const
{
    return "PAL.PAL";
}

QDir InteriorFile::get_textures_folder() const
{
    return QDir(R"(C:\Users\Leonid\Downloads\PARKAN THE IMPERIAL CHRONICLES\TEXTURES.LIB.dir)");
}

std::set<QString> InteriorFile::all_texture_names() const
{
    std::set<QString> texture_names;
    for(const auto& p : m_vertical_polygons)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    for(const auto& p : m_horizontal_polygons)
    {
        texture_names.insert(get_texture_fullpath(p.texture.to_string()).absoluteFilePath());
    }
    return texture_names;
}

