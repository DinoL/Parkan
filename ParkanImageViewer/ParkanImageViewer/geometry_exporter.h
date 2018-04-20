#ifndef GEOMETRY_EXPORTER_H
#define GEOMETRY_EXPORTER_H

#include "serializable_geometry.h"
#include "files_filter.h"

#include <QString>
#include <QFileInfoList>

class GeometryExporter
{
public:
    bool export_geometry(const QString& i_from, const QString& i_to) const;
    bool export_all_geometry_files(const QFileInfoList& i_all_geometry_files, const QDir& i_out_directory) const;

private:

    bool import_geometry(const QString& i_from, SerializableGeometry& o_geometry) const;
    bool export_geometry(const SerializableGeometry& i_geometry, const QString& i_to) const;
};

QFileInfoList get_geometry_files(const QString& i_dir);

#endif // GEOMETRY_EXPORTER_H
