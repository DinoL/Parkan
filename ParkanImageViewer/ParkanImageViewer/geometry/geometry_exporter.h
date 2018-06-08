#ifndef GEOMETRY_EXPORTER_H
#define GEOMETRY_EXPORTER_H

#include <QString>
#include <QFileInfoList>
#include <QDir>

class GeometryExporter
{
public:
    bool export_geometry(const QString& i_from, const QString& i_to) const;
    bool export_all_geometry_files(const QFileInfoList& i_all_geometry_files, const QDir& i_out_directory) const;
};

QFileInfoList get_geometry_files(const QString& i_dir);

#endif // GEOMETRY_EXPORTER_H
