#include "interior_exporter.h"
#include <fstream>


bool InteriorExporter::export_interior(const QString &i_from, const QString &i_to, InteriorExporter::ExportFormat i_format) const
{
    switch(i_format)
    {
    case ExportFormat::Text:
        return export_as_text(i_from, i_to);
    default:
        return false;
    }
}

bool InteriorExporter::import_interior(const QString &i_from, InteriorFile& o_interior) const
{
    if(i_from.isEmpty())
        return false;

    std::ifstream file(i_from.toStdString(), std::ios::binary);
    InputBinaryStream bis(file);
    bis >> o_interior;
    return true;
}

bool InteriorExporter::export_as_text(const QString &i_from, const QString &i_to) const
{
    if(i_to.isEmpty())
        return false;

    InteriorFile interior;
    if(!import_interior(i_from, interior))
        return false;

    std::ofstream out_file(i_to.toStdString());
    out_file << interior;
    return true;
}
