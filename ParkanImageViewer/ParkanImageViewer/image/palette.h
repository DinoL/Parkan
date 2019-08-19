#ifndef PALETTE_H
#define PALETTE_H

#include <QRgb>
#include <QString>
#include <QColor>
#include <QStringList>
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

    static QStringList get_all_palettes();

    static Palette get_palette_by_name(const QString& i_file_name);

private:
    QString m_name;
    QVector<QRgb> m_colors;

private:
    static QString get_palettes_folder();
};

#endif // PALETTE_H
