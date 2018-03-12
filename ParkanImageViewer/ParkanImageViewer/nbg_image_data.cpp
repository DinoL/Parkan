#include "ngb_image_data.h"
#include "binary_stream.h"
#include "image_description_guard.h"

#include <QFile>

#include <fstream>
#include <vector>

NgbImageData::NgbImageData(const QFileInfo& i_path)
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
        if(signature_vec != std::vector<uchar>{0xAB, 0xCD, 0xF0, 0x01})
            return;

        m_width = words[2] - words[0] + 1;
        m_height = words[3] - words[1] + 1;
        m_default_color = default_color;
    }

    m_data.resize(m_width * m_height);

    bis >> m_data;
}
