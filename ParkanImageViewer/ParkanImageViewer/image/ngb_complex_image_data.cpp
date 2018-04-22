#include "ngb_complex_image_data.h"
#include "image_description_guard.h"

#include "utils/binary_stream.h"
#include "utils/exceptions.h"

#include <fstream>

NgbComplexImageData::NgbComplexImageData(const QFileInfo& i_path)
    : NgbImageData(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw LoadImageDataException("Cannot open texture file " + i_path.filePath());

    const std::vector<uchar> signature{0xAB, 0xCD, 0xEF, 0x01};
    if(has_signature(file, signature))
        fill_data(file);
}

void NgbComplexImageData::fill_data(std::istream& io_file)
{
    InputBinaryStream bis(io_file);
    std::vector<qint32> row_starts(m_height);
    for(auto& rs : row_starts)
    {
        bis >> rs;
    }

    m_data.clear();

    for(qint32 row = 0; row < m_height; ++row)
    {
        QByteArray cur_row(m_width, m_default_color);

        qint32 cur_x = 0;
        while(cur_x <= m_width)
        {
            quint16 shift, cur_width;
            bis >> shift;

            if (shift == 0xFFFF)
                break;

            bis >> cur_width;

            QByteArray buffer(cur_width, '\0');
            bis >> buffer;
            qint32 pos = cur_x + shift;
            cur_row.replace(pos, cur_width, buffer);
            cur_x += (cur_width + shift);
        }

        m_data.append(cur_row);
    }
}
