#ifndef VIEWER_APP_H
#define VIEWER_APP_H

#include "color_ramp_widget.h"
#include "image/image.h"
#include "image/image_iterator.h"
#include "image/animated_image.h"

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QScrollArea>
#include <QScrollBar>
#include <QFileInfoList>
#include <QTimer>

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

    void on_actionOpen_3d_geometry_triggered();

    void on_actionSave_image_triggered();

    void on_actionExport_all_3d_files_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionNormal_Size_triggered();

    void on_actionFit_to_Window_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

    void next_frame();

    void on_actionShow_Palette_triggered(bool checked);

private:

    void setup_scroll_area();

    void try_open_image(const QFileInfoList& i_paths);

    bool open_image(const QFileInfoList& i_paths);

    void update_image();

    void update_actions();

    bool has_image() const;

    bool has_palette() const;

    bool show_palette() const;

    void set_palette(const QString& i_palette_name);

    bool is_fit_to_window_mode() const;

    void scale_image(float i_factor);

    void adjust_scroll_bar(QScrollBar* i_scroll_bar, float i_factor);

    void show_warning_message(const QString& i_title, const QString& i_message) const;

    void clear_image();

private:
    Ui::ViewerApp* ui;
    std::unique_ptr<ColorRampWidget> m_crw;
    std::unique_ptr<AnimatedImage> m_img;

    ImageIterator m_it;

    QLabel* m_image_label;
    QScrollArea* m_scroll_area;

    float m_scale_factor = 1.f;
    float m_scale_step = 0.25f;
    float m_min_zoom = 0.333f;
    float m_max_zoom = 3.f;
};

#endif // VIEWER_APP_H
