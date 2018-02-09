#ifndef INTERIOR_EXPORTER_H
#define INTERIOR_EXPORTER_H

#include "interior.h"
#include <QString>
#include <QFileInfoList>

class InteriorExporter
{
public:

    enum class ExportFormat
    {
        Text,
        Obj,
        TexturedObj
    };

    bool export_interior(const QString& i_from,
                         const QString& i_to) const;

    bool export_interior(const QString& i_from,
                         const QString& i_to,
                         ExportFormat i_format) const;

    bool export_all_used_textures(const QFileInfoList& i_all_interiors, const QString& i_to) const;

private:

    bool import_interior(const QString& i_from, InteriorFile& o_interior) const;
    bool export_as_text(const QString& i_from, const QString& i_to) const;
    bool export_as_obj(const QString& i_from, const QString& i_to) const;
    bool export_as_obj(const InteriorFile& i_interior, const QString& i_to) const;
    bool export_as_textured_obj(const QString& i_from, const QString& i_to) const;
    bool export_as_textured_obj(const InteriorFile& i_interior, const QString& i_to) const;

    ExportFormat auto_detect_format(const QString& i_file_name) const;


};

#endif // INTERIOR_EXPORTER_H
