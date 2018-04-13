#include "geometry_3d.h"

QFileInfo Geometry3d::get_texture_fullpath(const QString& i_texture_name) const
{
    return QFileInfo(get_textures_folder(), i_texture_name);
}
