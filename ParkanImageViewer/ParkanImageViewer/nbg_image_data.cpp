#include "ngb_image_data.h"
#include "image_description_guard.h"
#include "binary_stream.h"

NgbImageData::NgbImageData(const QFileInfo& i_path) :
    ImageData(i_path)
{}

void NgbImageData::fill_data(std::istream&)
{}

bool NgbImageData::has_signature(std::istream& io_file, const std::vector<uchar>& i_signature)
{
    InputBinaryStream bis(io_file);
    HeaderGuard guard(16, io_file);

    std::vector<quint16> words(4);
    for(auto& word : words)
    {
        bis >> word;
    }
    uchar default_color;
    QByteArray skip(3, '\0');
    QByteArray signature(4, '\0');
    bis >> default_color >> skip >> signature;

    const std::vector<uchar> signature_vec(signature.begin(), signature.end());
    if(signature_vec != i_signature)
        return false;

    m_width = words[2] - words[0] + 1;
    m_height = words[3] - words[1] + 1;
    m_default_color = default_color;

    return true;
}
