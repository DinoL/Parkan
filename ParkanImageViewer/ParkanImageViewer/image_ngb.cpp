#include "image_ngb.h"
#include "binary_stream.h"

#include <QFile>

#include <fstream>

ImageNgb::ImageNgb(const QFileInfo& i_path)
    : Image(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary | std::ios::ate);
    if(file.fail())
        throw "Cannot open texture file " + i_path.filePath();

    InputBinaryStream bis(file);

    qint16 words[8];
    for(int i = 0; i < 8; ++i)
    {
        bis >> words[i];
    }

    m_width = words[2] - words[0] + 1;
    m_height = words[3] - words[1] + 1;

    m_data.resize(m_width * m_height);

    m_img =  QImage((uchar*)m_data.data(), m_width, m_height, QImage::QImage::Format_Indexed8);
}
