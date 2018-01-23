#include "palette.h"

#include <QFile>
#include <QDir>
#include <QByteArray>

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
        cur_color = QColor(r, g, b).rgb();
    }
}

QVector<QRgb> Palette::get_color_table() const
{
    return m_colors;
}

size_t Palette::get_colors_cnt() const
{
    return m_colors.size();
}

Palette Palette::get_palette_by_name(const QString &i_palette_name)
{
    const QFileInfo file_info(Palette::get_palettes_folder() + i_palette_name);
    return Palette(file_info);
}

QString Palette::get_palettes_folder()
{
    return ":/palettes/";
}

QStringList Palette::get_all_palettes()
{
    return QDir(Palette::get_palettes_folder()).entryList();
}

QColor Palette::get_color_by_id(int i_col_id) const
{
    return QColor(m_colors[i_col_id]);
}
