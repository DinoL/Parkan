#include "palette.h"

#include <QFile>

Palette::Palette(const QFileInfo& i_path) :
    m_name(i_path.fileName()),
    m_colors(256)
{
    QFile file(i_path.filePath());
    if(!file.open(QIODevice::ReadOnly))
        throw "Cannot create palette from file " + i_path.filePath();

    const qint64 channels_cnt = 4;
    for (auto& cur_color : m_colors)
    {
        const QByteArray m_seq = file.read(channels_cnt);
        const quint8 b = m_seq[0];
        const quint8 g = m_seq[1];
        const quint8 r = m_seq[2];
        cur_color = QColor(r, g, b);
    }
}

size_t Palette::get_colors_cnt() const
{
    return m_colors.size();
}

QColor Palette::get_color_by_id(int i_col_id) const
{
    return m_colors[i_col_id];
}
