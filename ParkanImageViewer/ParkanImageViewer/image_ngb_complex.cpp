#include "image_ngb_complex.h"
#include "binary_stream.h"

#include <QFile>

#include <fstream>
#include <vector>

ImageNgbComplex::ImageNgbComplex(const QFileInfo& i_path)
    : Image(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw "Cannot open texture file " + i_path.filePath();

    InputBinaryStream bis(file);

    std::vector<quint16> words(4);
    for(auto& word : words)
    {
        bis >> word;
    }

    QByteArray signature(7, '\0');
    bis >> m_default_color >> signature;

    m_width = words[2] - words[0] + 1;
    m_height = words[3] - words[1] + 1;

    std::vector<qint32> row_starts(m_height);
    for(auto& rs : row_starts)
    {
        bis >> rs;
    }

    m_data.clear();

    for(int row = 0; row < m_height; ++row)
    {

        QByteArray cur_row(m_width, m_default_color);

        int cur_x = 0;
        int cnt = 0;
        while(cur_x < m_width)
        {
            quint16 shift, cur_width;
            bis >> shift >> cur_width;

            QByteArray buffer(cur_width, '\0');
            bis >> buffer;
            if(cur_x + shift + cur_width < m_width)
            {
                cur_row.replace(cur_x + shift, cur_width, buffer);
            }

            cur_x += (cur_width + shift);
        }
        quint16 end_row;
        bis >> end_row;

        m_data.append(cur_row);


    }


    auto size = m_data.size();
    std::cout << size;
    m_img = QImage((uchar*)m_data.data(), m_width, m_height, QImage::QImage::Format_Indexed8);
}
