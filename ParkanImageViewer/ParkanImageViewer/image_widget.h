#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>

class ImageWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(const QImage& i_img, const QString& title, QWidget *parent = 0);

    void paintEvent(QPaintEvent *)
    {
        QPainter qp(this);
        draw_image(qp);
    }

    void draw_image(QPainter& qp);

    QImage m_img;

signals:

public slots:
};


#endif // IMAGE_WIDGET_H
