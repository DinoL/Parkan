#include "simle_image_data.h"
#include "binary_stream.h"
#include <fstream>

SimpleImageData::SimpleImageData(const QFileInfo& i_path)
    : ImageData(i_path)
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
}
