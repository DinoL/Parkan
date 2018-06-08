#ifndef SERIALIZABLE_GEOMETRY_H
#define SERIALIZABLE_GEOMETRY_H

#include "geometry_3d.h"
#include "utils/serializable.h"

class SerializableGeometry : public IGeometry3d, public ISerializable
{
};

#endif // SERIALIZABLE_GEOMETRY_H
