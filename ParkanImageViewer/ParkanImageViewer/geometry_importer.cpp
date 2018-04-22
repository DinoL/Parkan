#include "geometry_importer.h"

#include <fstream>

bool GeometryImporter::import_geometry(const QString& i_from, SerializableGeometry& o_geometry) const
{
    if(i_from.isEmpty())
        return false;

    std::ifstream file(i_from.toStdString(), std::ios::binary);
    if(!file.good())
        return false;

    file >> o_geometry;
    return true;
}
