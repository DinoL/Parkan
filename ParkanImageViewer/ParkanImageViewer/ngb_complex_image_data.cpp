#include "ngb_complex_image_data.h"
#include "binary_stream.h"
#include "image_description_guard.h"

#include <QFile>

#include <fstream>
#include <vector>

NgbComplexImageData::NgbComplexImageData(const QFileInfo& i_path)
    : ImageData(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw "Cannot open texture file " + i_path.filePath();

    InputBinaryStream bis(file);

    {
        HeaderGuard guard(16, file);

        std::vector<quint16> words(4);
        for(auto& word : words)
        {
            bis >> word;
        }
        uchar default_color;
        QByteArray skip(3, '\0');
        QByteArray signature(4, '\0');
        bis >> default_color >> skip >> signature;

        std::vector<uchar> signature_vec(signature.begin(), signature.end());
        if(signature_vec != std::vector<uchar>{0xAB, 0xCD, 0xEF, 0x01})
            return;

        m_width = words[2] - words[0] + 1;
        m_height = words[3] - words[1] + 1;
        m_default_color = default_color;
    }

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
