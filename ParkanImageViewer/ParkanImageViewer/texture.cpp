#include "texture.h"
#include "binary_stream.h"
#include <fstream>

Texture::Texture(const QFileInfo& i_path)
    : Image(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw "Cannot open texture file " + i_path.filePath();

    InputBinaryStream bis(file);

    QByteArray signature(4, '\0');
    bis >> signature >> m_width >> m_height;

    QByteArray header(20, '\0');
    bis >> header;

    m_data.resize(m_width * m_height);
    bis >> m_data;

    m_img =  QImage((uchar*)m_data.data(), m_width, m_height, QImage::QImage::Format_Indexed8);
}
