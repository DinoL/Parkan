#include "dib_image_data.h"
#include "image_description_guard.h"

#include "utils/binary_stream.h"
#include "utils/exceptions.h"

#include <QFile>

#include <fstream>

DibImageData::DibImageData(const QFileInfo& i_path)
    : ImageData(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary | std::ios::ate);
    if(file.fail())
        throw LoadImageDataException("Cannot open texture file " + i_path.filePath());

    InputBinaryStream bis(file);
    {
        FooterGuard guard(32, file);

        qint32 width, height;
        QByteArray skip(8, '\0');
        bis >> skip >> width >> height;
        QByteArray skip2(6, '\0');
        QByteArray signature(2, '\0');
        bis >> skip2 >> signature;
        if(signature != QByteArray("BC"))
            return;

        m_width = width;
        m_height = height;
    }

    m_data.resize(m_width * m_height);
    bis >> m_data;
}
