#include "geometry_file.h"

#include "obj_model.h"
#include "interior_file.h"
#include "object_3d.h"
#include "image/texture_exporter.h"

#include <QString>
#include <QDir>

#include <fstream>

std::unique_ptr<SerializableGeometry> GeometryFile::get_geometry_by_ext(const QString& i_ext)
{
    if(i_ext == "BIN")
    {
        return std::make_unique<InteriorFile>();
    }
    if(i_ext == "3D")
    {
        return std::make_unique<Object3d>();
    }
    return nullptr;
}

QDir GeometryFile::get_textures_folder() const
{
    QDir dir(m_path.dir());
    if(!dir.cd("..\\" + m_type.m_textures_folder))
        throw std::exception("Textures folder doesn't exist");

    return dir;
}

GeometryFile::GeometryFile(const QFileInfo& i_path)
    : m_path(i_path),
      m_type(i_path)
{
    const QString ext = QFileInfo(i_path).suffix().toUpper();
    m_geometry = get_geometry_by_ext(ext);
    if(m_geometry)
    {
        std::ifstream file(i_path.absoluteFilePath().toStdWString(), std::ios::binary);
        if(!file.good())
            return;

        file >> *m_geometry;
    }
}

Palette GeometryFile::get_palette() const
{
    return Palette::get_palette_by_name(m_type.m_palette_name);
}

bool GeometryFile::export_to(const QFileInfo& i_path) const
{
    if(!is_valid())
        return false;

    const QString out_file_name = i_path.baseName();
    const QDir out_dir = i_path.dir();

    const auto all_textures = m_geometry->all_texture_names();

    std::cout << "Found " << all_textures.size() << " textures" << std::endl;

    TextureExporter textures_exporter;
    textures_exporter.set_textures_dir(get_textures_folder());
    textures_exporter.export_textures(all_textures, get_palette(), out_dir);

    const ObjModel model(*m_geometry);
    model.save(i_path);

    return true;
}

bool GeometryFile::is_valid() const
{
    return m_geometry != nullptr && !m_geometry->is_empty() && m_type.is_valid();
}
