#ifndef INTERIOR_EXPORTER_H
#define INTERIOR_EXPORTER_H

#include "interior.h"
#include <QString>

class InteriorExporter
{
public:

    enum class ExportFormat
    {
        Text
    };

    bool export_interior(const QString& i_from, const QString& i_to, ExportFormat i_format) const;

private:

    bool import_interior(const QString& i_from, InteriorFile& o_interior) const;
    bool export_as_text(const QString& i_from, const QString& i_to) const;
};

#endif // INTERIOR_EXPORTER_H
