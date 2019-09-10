#include "geometry_exporter.h"
#include "geometry_file.h"

#include "utils/io_utils.h"
#include "utils/files_filter.h"
#include "image/texture_exporter.h"
#include "image/palette.h"

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

bool GeometryExporter::export_geometry(const QString& i_from, const QString& i_to) const
{
    std::wcout << "Exporting as textured obj to " << i_to.toStdWString() << std::endl;
    if(i_to.isEmpty())
        return false;

    const GeometryFile geometry{QFileInfo(i_from)};
    if(!geometry.is_valid())
        return false;

    return geometry.export_to(QFileInfo(i_to));
}

QFileInfoList get_geometry_files(const QString& i_dir)
{
    return get_files_from_dir_by_mask(i_dir, QStringList() << "*.BIN" << "*.3D");
}
