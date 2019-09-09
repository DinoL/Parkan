#include "simple_image_data.h"
#include "image_description_guard.h"

#include "utils/binary_stream.h"
#include "utils/exceptions.h"

#include <fstream>

SimpleImageData::SimpleImageData(const QFileInfo& i_path)
    : ImageData(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw LoadImageDataException("Cannot open texture file " + i_path.filePath());

    InputBinaryStream bis(file);
    {
        HeaderGuard guard(32, file);

        QByteArray signature(4, '\0');
        bis >> signature;
        if(signature != QByteArray("Texm"))
            return;

        bis >> m_width >> m_height;
    }

    m_data.resize(m_width * m_height);
    bis >> m_data;
}
