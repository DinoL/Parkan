#ifndef PALETTE_H
#define PALETTE_H

#include <QColor>
#include <QString>
#include <QFileInfo>
#include <QVector>

class Palette
{
public:
    Palette(const QFileInfo& i_path);

    QColor get_color_by_id(int i_col_id) const;

    QVector<QRgb> get_color_table() const;

    size_t get_colors_cnt() const;

    QString get_name() const { return m_name; }

private:
    QString m_name;
    QVector<QRgb> m_colors;
};

#endif // PALETTE_H
