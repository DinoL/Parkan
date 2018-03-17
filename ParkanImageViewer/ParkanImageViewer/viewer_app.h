#ifndef VIEWER_APP_H
#define VIEWER_APP_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

#include "color_ramp_widget.h"
#include "image.h"
#include "image_iterator.h"

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
    void on_select_palette_combo_box_activated(const QString& i_palette_name);

    void on_actionExit_triggered();

    void on_actionOpen_Image_triggered();

    void on_actionOpen_interior_triggered();

    void on_actionExport_all_used_textures_triggered();

    void on_actionSave_image_triggered();

    void on_actionExport_all_interiors_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionNormal_Size_triggered();

    void on_actionFit_to_Window_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

private:

    void setup_scroll_area();

    void open_image(const QString& i_path);

    void update_image();

    void update_actions();

    bool has_image() const;

    bool has_palette() const;

    bool is_fit_to_window_mode() const;

    void scale_image(float i_factor);

    void adjust_scroll_bar(QScrollBar* i_scroll_bar, float i_factor);

private:
    Ui::ViewerApp* ui;
    std::unique_ptr<ColorRampWidget> m_crw;
    std::unique_ptr<Image> m_img;

    ImageIterator m_it;

    QLabel* m_image_label;
    QScrollArea* m_scroll_area;

    float m_scale_factor = 0.f;
    float m_scale_step = 0.25f;
    float m_min_zoom = 0.333f;
    float m_max_zoom = 3.f;
};

#endif // VIEWER_APP_H
