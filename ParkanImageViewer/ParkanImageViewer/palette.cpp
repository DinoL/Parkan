#include "palette.h"

Palette::Palette(const QFileInfo& i_path)
    : BinaryFile(i_path)
    , m_name(i_path.baseName())
    , m_colors(m_palette_colors_cnt)
{
    m_colors.resize(m_palette_colors_cnt);
    const int channels_cnt = 4;
    for (int i = 0; i < m_palette_colors_cnt; ++i)
    {
        int pos = i * channels_cnt;
        int b = m_seq[pos];
        int g = m_seq[pos + 1];
        int r = m_seq[pos + 2];
        m_colors[i] = QColor(r, g, b);
    }
}
