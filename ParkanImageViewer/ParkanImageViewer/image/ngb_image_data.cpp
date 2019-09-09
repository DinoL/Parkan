#include "ngb_image_data.h"
#include "image_description_guard.h"

#include "utils/binary_stream.h"

NgbImageData::NgbImageData(const QFileInfo& i_path) :
    ImageData(i_path)
{}

void NgbImageData::fill_data(std::wistream&)
{}

bool NgbImageData::has_signature(std::wistream& io_file, const std::vector<uchar>& i_signature)
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

    m_width = 640;
    m_height = 480;

    const QPoint top_left(words[0], words[1]);
    const QPoint bottom_right(words[2], words[3]);
    m_boundary = QRect(top_left, bottom_right);

    m_default_color = default_color;

    return true;
}

QByteArray NgbImageData::overlay_with_background() const
{
    QByteArray merged_data(m_width * m_height, m_default_color);

    int overlay_width = m_boundary.width();
    int overlay_height = m_boundary.height();

    const QPoint overlay_top_left = m_boundary.topLeft();
    const int offset_y = overlay_top_left.y();
    const int offset_x = overlay_top_left.x();
    for(int y = 0; y < overlay_height; ++y)
    {
        const int shifted_y = offset_y + y;
        for(int x = 0; x < overlay_width; ++x)
        {
            const int shifted_x = offset_x + x;
            const int shifted_index = point_to_index(shifted_x, shifted_y, m_width);
            const int overlay_index = point_to_index(x, y, overlay_width);
            merged_data[shifted_index] = m_data[overlay_index];
        }
    }
    return merged_data;
}
