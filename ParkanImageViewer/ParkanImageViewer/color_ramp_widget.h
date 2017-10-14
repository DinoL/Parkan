#ifndef COLORRAMPWIDGET_H
#define COLORRAMPWIDGET_H

#include <QWidget>
#include <QPainter>
#include "palette.h"

class ColorRampWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorRampWidget(const Palette& i_palette, QWidget *parent = 0);

    void paintEvent(QPaintEvent *)
    {
        QPainter qp(this);
        draw_rectangles(qp);
    }

    void draw_rectangles(QPainter& qp);

    Palette m_palette;

signals:

public slots:
};

#endif // COLORRAMPWIDGET_H
