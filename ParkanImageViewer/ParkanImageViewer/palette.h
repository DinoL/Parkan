#ifndef PALETTE_H
#define PALETTE_H

#include <QColor>
#include <QString>
#include <QFileInfo>

#include <vector>

class Palette
{
public:
    Palette(const QFileInfo& i_path);

    QColor get_color_by_id(int i_col_id) const;

    size_t get_colors_cnt() const;

    QString get_name() const { return m_name; }

private:
    QString m_name;
    std::vector<QColor> m_colors;
};

#endif // PALETTE_H
