#ifndef GEOMETRY_TYPE_H
#define GEOMETRY_TYPE_H

#include <QFileInfo>

struct GeometryType
{
    GeometryType(const QFileInfo& i_path);

    QString m_palette_name;
    QString m_textures_folder;

    bool is_valid() const;
};

#endif // GEOMETRY_TYPE_H
