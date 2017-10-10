#ifndef VIEWER_APP_H
#define VIEWER_APP_H

#include <QMainWindow>

namespace Ui {
class ViewerApp;
}

class ViewerApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewerApp(QWidget *parent = 0);
    ~ViewerApp();

private:
    Ui::ViewerApp *ui;
};

#endif // VIEWER_APP_H
