#include "texture.h"
#include "binary_stream.h"
#include <fstream>

Texture::Texture(const QFileInfo& i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw "Cannot open texture file file " + i_path.filePath();

    InputBinaryStream bis(file);

    QByteArray signature(4, '\0');
    bis >> signature >> m_width >> m_height;
}
