#include "image_widget.h"

ImageWidget::ImageWidget(const QImage& i_img, const QString& title, QWidget *parent)
    : QWidget(parent)
    , m_img(i_img)
{
    setGeometry(300, 300, 350, 350);
    setWindowTitle(title);
    show();
}

void ImageWidget::draw_image(QPainter &qp)
{
    qp.drawImage(0, 0, m_img);
}
