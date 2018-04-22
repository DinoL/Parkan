#ifndef GEOMETRY_IMPORTER_H
#define GEOMETRY_IMPORTER_H

#include "serializable_geometry.h"

#include <QString>

class GeometryImporter
{
public:
    bool import_geometry(const QString& i_from, SerializableGeometry& o_geometry) const;
};

#endif // GEOMETRY_IMPORTER_H
