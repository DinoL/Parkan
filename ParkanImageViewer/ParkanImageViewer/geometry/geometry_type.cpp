#include "geometry_type.h"

#include <QDir>
#include <QString>

GeometryType::GeometryType(const QFileInfo& i_path)
{
    const QString dir_name = i_path.dir().dirName();

    if(dir_name.startsWith("BIN"))
    {
        m_palette_name = "Interior";
        m_textures_folder = "TEXTURES.LIB.dir";
    }
    else if(dir_name.startsWith("OBJ3D"))
    {
        m_palette_name = "Interior";
        m_textures_folder = "TEXTUR3D.LIB.dir";
    }
    else if(dir_name.startsWith("SP3DOB"))
    {
        m_palette_name = "Space";
        m_textures_folder = "SP3DTEXT.LIB.dir";
    }
}

bool GeometryType::is_valid() const
{
    return !m_palette_name.isEmpty() && !m_textures_folder.isEmpty();
}
