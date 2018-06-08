#ifndef GEOMETRY_FILE_H
#define GEOMETRY_FILE_H

#include "serializable_geometry.h"
#include "geometry_type.h"

#include "image/palette.h"

#include <QFileInfo>
#include <QDir>

#include <memory>

class GeometryFile
{
public:
    GeometryFile(const QFileInfo& i_path);

    bool export_to(const QFileInfo& i_path) const;

    bool is_valid() const;

protected:
    static std::unique_ptr<SerializableGeometry> get_geometry_by_ext(const QString& i_ext);

    QDir get_textures_folder() const;
    Palette get_palette() const;

private:
    QFileInfo m_path;
    std::unique_ptr<SerializableGeometry> m_geometry;
    GeometryType m_type;
};

#endif // GEOMETRY_FILE_H
