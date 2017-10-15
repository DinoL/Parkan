#ifndef PALETTE_H
#define PALETTE_H

#include "binary_file.h"
#include <QColor>
#include <QString>

class Palette : public BinaryFile
{
public:
    Palette(const QFileInfo& i_path);

    QColor get_color_by_id(int i_col_id) { return m_colors[i_col_id]; }

    int colors_cnt() const { return m_palette_colors_cnt; }

    QString get_name() const { return m_name; }

private:
    int m_palette_colors_cnt = 256;
    QString m_name;
    std::vector<QColor> m_colors;
};

#endif // PALETTE_H
