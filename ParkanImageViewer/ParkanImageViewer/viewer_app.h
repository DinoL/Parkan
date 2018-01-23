#ifndef VIEWER_APP_H
#define VIEWER_APP_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include "color_ramp_widget.h"
#include "texture.h"
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
    void on_select_palette_combo_box_activated(const QString &arg1);

    void on_actionExit_triggered();

    void on_actionOpen_Image_triggered();

    void on_actionOpen_interior_triggered();

private:
    QString get_palettes_folder() const;

private:
    Ui::ViewerApp *ui;
    std::unique_ptr<ColorRampWidget> m_crw;
    std::unique_ptr<Texture> m_img;
};

#endif // VIEWER_APP_H
