#include "color_ramp_widget.h"

ColorRampWidget::ColorRampWidget(const Palette& i_palette, QWidget *parent)
    : QWidget(parent)
    , m_palette(i_palette)
{
    setGeometry(300, 300, 350, 350);
    show();
}

void ColorRampWidget::draw_rectangles(QPainter &qp)
{
    const int cnt = m_palette.colors_cnt();
    const int wd = 20;
    const int ht = 20;
    const int col_per_row = 16;
    const int hor_padding = 5;
    const int vert_padding = 5;
    for (int col_id = 0; col_id < cnt; ++col_id)
    {
        const int row = col_id / col_per_row;
        const int column = col_id % col_per_row;
        const QColor cur_col = m_palette.get_color_by_id(col_id);
        qp.setBrush(cur_col);
        qp.drawRect(hor_padding + column * wd, vert_padding + row * ht, wd, ht);
    }
}
