#ifndef VIEWER_APP_H
#define VIEWER_APP_H

#include <QMainWindow>
#include "color_ramp_widget.h"
#include <memory>

namespace Ui {
class ViewerApp;
}

class ViewerApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewerApp(QWidget *parent = 0);
    ~ViewerApp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewerApp *ui;
    std::unique_ptr<ColorRampWidget> m_crw;

};

#endif // VIEWER_APP_H
