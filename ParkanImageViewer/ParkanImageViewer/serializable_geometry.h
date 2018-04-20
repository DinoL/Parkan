#ifndef SERIALIZABLE_GEOMETRY_H
#define SERIALIZABLE_GEOMETRY_H

#include "geometry_3d.h"
#include "serializable.h"

class SerializableGeometry : public Geometry3d, public ISerializable
{
};

#endif // SERIALIZABLE_GEOMETRY_H
