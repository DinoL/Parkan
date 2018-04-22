#include "ngb_simple_image_data.h"
#include "image_description_guard.h"

#include "utils/binary_stream.h"
#include "utils/exceptions.h"

#include <fstream>

NgbSimpleImageData::NgbSimpleImageData(const QFileInfo& i_path)
    : NgbImageData(i_path)
{
    std::ifstream file(i_path.filePath().toStdString(), std::ios::binary);
    if(file.fail())
        throw LoadImageDataException("Cannot open texture file " + i_path.filePath());

    const std::vector<uchar> signature{0xAB, 0xCD, 0xF0, 0x01};
    if(has_signature(file, signature))
        fill_data(file);
}

void NgbSimpleImageData::fill_data(std::istream& io_file)
{
    InputBinaryStream bis(io_file);
    m_data.resize(m_width * m_height);

    bis >> m_data;
}
