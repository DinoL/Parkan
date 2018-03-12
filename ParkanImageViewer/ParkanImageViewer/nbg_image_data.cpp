#include "ngb_image_data.h"
#include "binary_stream.h"

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

    std::vector<quint16> words(4);
    for(auto& word : words)
    {
        bis >> word;
    }

    QByteArray signature(7, '\0');
    bis >> m_default_color >> signature;

    m_width = words[2] - words[0] + 1;
    m_height = words[3] - words[1] + 1;

    m_data.resize(m_width * m_height);

    bis >> m_data;
}
