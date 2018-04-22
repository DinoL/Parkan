#include "image_data.h"

#include "utils/exceptions.h"

ImageData::ImageData(const QFileInfo& i_path) :
    m_path(i_path)
{}

qint32 ImageData::width() const
{
    return m_width;
}

qint32 ImageData::height() const
{
    return m_height;
}

bool ImageData::is_valid() const
{
    return m_width > 0 && m_height > 0 && m_data.size() >= m_width * m_height;
}

Image ImageData::get_image() const
{
    if(!is_valid())
    {
        throw DecodeImageDataException("Cannot create image from data");
    }

    QImage image(m_width, m_height, QImage::QImage::Format_Indexed8);
    for(qint32 y = 0; y < m_height; ++y)
    {
        auto* row = image.scanLine(y);
        for(qint32 x = 0; x < m_width; ++x)
        {
            row[x] = m_data[x + m_width * y];
        }
    }
    return Image(image, m_path);
}
