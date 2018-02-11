#include "image_dib.h"
#include "binary_stream.h"

#include <QFile>

#include <fstream>

ImageDib::ImageDib(const QFileInfo& i_path)
    : Image(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary | std::ios::ate);
    if(file.fail())
        throw "Cannot open texture file " + i_path.filePath();

    const size_t file_size = file.tellg();
    const size_t footer_size = 32;

    file.seekg(file_size - footer_size);

    InputBinaryStream bis(file);

    QByteArray signature(8, '\0');
    bis >> signature >> m_width >> m_height;

    file.seekg(0);

    m_data.resize(m_width * m_height);
    bis >> m_data;

    m_img =  QImage((uchar*)m_data.data(), m_width, m_height, QImage::QImage::Format_Indexed8);
}
