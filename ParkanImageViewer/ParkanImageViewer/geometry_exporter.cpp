#include "geometry_exporter.h"

#include "geometry_importer.h"
#include "io_utils.h"
#include "texture_exporter.h"
#include "palette.h"
#include "obj_model.h"
#include "interior_file.h"
#include "object_3d.h"

#include <QFileInfo>
#include <QDir>
#include <QString>

#include <set>
#include <fstream>
#include <memory>

QFileInfo replace_dir_and_extension(const QFileInfo& i_filepath,
                                    const QDir& i_new_dir, const QString& i_new_ext)
{
    return QFileInfo(i_new_dir, i_filepath.baseName() + i_new_ext);
}

bool GeometryExporter::export_all_geometry_files(const QFileInfoList& i_all_geometry_files,
                                                 const QDir& i_out_directory) const
{
    bool success = true;
    for(const auto& geometry_file : i_all_geometry_files)
    {
        const QFileInfo output_file = replace_dir_and_extension(geometry_file, i_out_directory, ".obj");
        success &= export_geometry(geometry_file.absoluteFilePath(),
                                   output_file.absoluteFilePath());
    }
    return success;
}

std::unique_ptr<SerializableGeometry> get_geometry_by_ext(const QString& i_ext)
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

bool GeometryExporter::export_geometry(const QString& i_from, const QString& i_to) const
{
    std::cout << "Exporting as textured obj to " << i_to.toStdString() << std::endl;
    if(i_to.isEmpty())
        return false;

    QString ext = QFileInfo(i_from).suffix().toUpper();
    std::unique_ptr<SerializableGeometry> geometry = get_geometry_by_ext(ext);
    if(!geometry)
        return false;

    GeometryImporter().import_geometry(i_from, *geometry);
    return export_geometry(*geometry, i_to);
}

bool GeometryExporter::export_geometry(const SerializableGeometry& i_geometry, const QString& i_to) const
{
    if(i_to.isEmpty())
        return false;

    QFileInfo file_info(i_to);
    QString obj_file_name = file_info.baseName();
    QDir obj_file_dir = file_info.dir();

    const auto all_textures = i_geometry.all_texture_names();

    const Palette palette = Palette::get_palette_by_name(i_geometry.get_textures_palette_name());
    TextureExporter().export_textures(all_textures, palette, obj_file_dir);

    ObjModel model(i_geometry);
    const auto mtl_file = obj_file_dir.absoluteFilePath(obj_file_name + ".mtl").toStdString();

    model.save(i_to.toStdString(), mtl_file);

    std::cout << "Successfully exported to " << i_to.toStdString() << " MTL " << mtl_file << std::endl;
    return true;
}

QFileInfoList get_geometry_files(const QString& i_dir)
{
    return get_files_from_dir_by_mask(i_dir, QStringList() << "*.BIN" << "*.3D");
}
