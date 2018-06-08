#include "viewer_app.h"
#include "ui_viewer_app.h"

#include "color_ramp_widget.h"

#include "image/texture_factory.h"
#include "geometry/geometry_exporter.h"
#include "utils/files_filter.h"
#include "utils/exceptions.h"

#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

ViewerApp::ViewerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerApp),
    m_crw(nullptr),
    m_img(nullptr),
    m_scroll_area(nullptr),
    m_image_label(nullptr)
{
    ui->setupUi(this);

    setup_scroll_area();

    setWindowTitle("Parkan Image Viewer");

    QStringList all_palettes = Palette::get_all_palettes();
    ui->select_palette_combo_box->addItems(all_palettes);

    if(!all_palettes.isEmpty())
        set_palette(all_palettes.front());

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(next_frame()));
    set_animation_speed(ui->frames_per_second_control->value());
    m_timer->start();

    update_actions();
}

void ViewerApp::setup_scroll_area()
{
    if(!ui)
        return;

    m_scroll_area = new QScrollArea(ui->centralWidget);
    m_scroll_area->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_image_label = new QLabel(m_scroll_area);
    m_image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_image_label->setScaledContents(true);

    m_scroll_area->setWidget(m_image_label);

    ui->verticalLayout->insertWidget(2, m_scroll_area, 1);
}

void ViewerApp::try_open_image(const QFileInfoList& i_paths)
{
    if(i_paths.empty())
        return;

    if(!open_image(i_paths))
    {
        clear_image();
        const QString filename = i_paths.front().fileName();
        const QString msg("Could not open image %1");
        show_warning_message("Loading failed", msg.arg(filename));
    }
}

ViewerApp::~ViewerApp()
{
    delete ui;
    delete m_timer;
}

void ViewerApp::on_select_palette_combo_box_activated(const QString& i_palette_name)
{
    set_palette(i_palette_name);
    if (has_image())
    {
        m_img->set_palette(m_crw->m_palette);
    }
    update_image();
    update_actions();
}

void ViewerApp::on_actionExit_triggered()
{
    close();
}

void ViewerApp::on_actionOpen_Image_triggered()
{
    const QString file_path = QFileDialog::getOpenFileName();
    if (file_path.isEmpty())
        return;

    if(!has_palette())
    {
        show_warning_message("No palette", "Please select palette first");
        return;
    }

    m_it = ImageIterator(file_path);
    if(m_it)
    {
        try_open_image(*m_it);
    }
}

void ViewerApp::on_actionOpen_3d_geometry_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (file_name.isEmpty())
        return;

    const QString out_file_name = QFileDialog::getSaveFileName(this, tr("Save 3d geometry file"),
                                                               QFileInfo(file_name).baseName(),
                                                               "*.obj");
    if(out_file_name.isEmpty())
        return;

    GeometryExporter().export_geometry(file_name, out_file_name);
}

void ViewerApp::on_actionSave_image_triggered()
{
    if(!has_image())
    {
        show_warning_message("No image", "Please open image first");
        return;
    }
    const QString out_file_name = QFileDialog::getSaveFileName();
    if(out_file_name.isEmpty())
        return;

    const bool was_saved = m_img->current_image().save(out_file_name);
    if(!was_saved)
    {
        show_warning_message("Not saved", QString("Failed to save image into %1").arg(out_file_name));
        return;
    }
}

void ViewerApp::on_actionExport_all_3d_files_triggered()
{
    const QString dir_name = QFileDialog::getExistingDirectory();
    if (dir_name.isEmpty())
        return;

    const QString out_directory = QFileDialog::getExistingDirectory();
    if(out_directory.isEmpty())
        return;

    const QFileInfoList all_geometry_files = get_geometry_files(dir_name);
    GeometryExporter().export_all_geometry_files(all_geometry_files, QDir(out_directory));
}

void ViewerApp::on_actionZoom_In_triggered()
{
    scale_image(1.f + m_scale_step);
}

void ViewerApp::on_actionZoom_Out_triggered()
{
    scale_image(1.f / (1.f + m_scale_step));
}

void ViewerApp::on_actionNormal_Size_triggered()
{
    m_image_label->adjustSize();
    m_scale_factor = 1.f;

    update_actions();
}

void ViewerApp::on_actionFit_to_Window_triggered()
{
    bool fit_to_window = ui->actionFit_to_Window->isChecked();
    m_scroll_area->setWidgetResizable(fit_to_window);
    if (!fit_to_window)
        on_actionNormal_Size_triggered();

    update_actions();
}

bool ViewerApp::open_image(const QFileInfoList& i_paths)
{
    if(!has_palette())
        return false;

    m_img.reset(new AnimatedImage(i_paths));

    if(!has_image())
        return false;

    m_img->set_palette(m_crw->m_palette);

    update_image();
    update_actions();

    return true;
}

bool ViewerApp::show_image(const Image& i_image)
{
    if(!ui || !m_image_label)
        return false;

    const QPixmap pixmap = QPixmap::fromImage(i_image.image());
    m_image_label->setPixmap(pixmap);
    m_image_label->adjustSize();
    m_image_label->resize(m_scale_factor * pixmap.size());

    ui->image_name->setText(i_image.path().fileName());

    return true;
}

void ViewerApp::update_image()
{
    if(!has_image())
        return;

    show_image(m_img->current_image());
}

bool ViewerApp::has_image() const
{
    return m_img && m_img->is_valid() && has_palette();
}

bool ViewerApp::has_palette() const
{
    return m_crw != nullptr;
}

bool ViewerApp::show_palette() const
{
    return ui->actionShow_Palette->isChecked();
}

void ViewerApp::set_palette(const QString& i_palette_name)
{
    const Palette palette = Palette::get_palette_by_name(i_palette_name);
    m_crw.reset(new ColorRampWidget(palette, show_palette()));
}

bool ViewerApp::is_fit_to_window_mode() const
{
    return ui->actionFit_to_Window->isChecked();
}

void ViewerApp::update_actions()
{    
    ui->actionOpen_Image->setEnabled(has_palette());
    ui->actionOpen_animation->setEnabled(has_palette());

    const bool can_zoom = has_image() && !is_fit_to_window_mode();

    ui->actionZoom_In->setEnabled(can_zoom && m_scale_factor < m_max_zoom);
    ui->actionZoom_Out->setEnabled(can_zoom && m_scale_factor > m_min_zoom);
    ui->actionNormal_Size->setEnabled(can_zoom);
    ui->actionSave_image->setEnabled(has_image());
    ui->actionNext->setEnabled(has_image());
    ui->actionPrevious->setEnabled(has_image());
    ui->actionFit_to_Window->setEnabled(has_image());
}

void ViewerApp::scale_image(float i_factor)
{
    m_scale_factor *= i_factor;
    m_image_label->resize(m_scale_factor * m_image_label->pixmap()->size());

    adjust_scroll_bar(m_scroll_area->horizontalScrollBar(), i_factor);
    adjust_scroll_bar(m_scroll_area->verticalScrollBar(), i_factor);

    ui->actionZoom_In->setEnabled(m_scale_factor < m_max_zoom);
    ui->actionZoom_Out->setEnabled(m_scale_factor > m_min_zoom);
}

void ViewerApp::adjust_scroll_bar(QScrollBar* i_scroll_bar, float i_factor)
{
    if(!i_scroll_bar)
        return;

    i_scroll_bar->setValue(int(i_factor * i_scroll_bar->value()
                               + ((i_factor - 1) * i_scroll_bar->pageStep() / 2)));
}

void ViewerApp::show_warning_message(const QString& i_title, const QString& i_message) const
{
    auto* mb = new QMessageBox(QMessageBox::Warning, i_title, i_message);
    mb->show();
}

void ViewerApp::clear_image()
{
    if(!ui || !m_image_label)
        return;

    m_image_label->clear();
    ui->image_name->setText("");
}

void ViewerApp::set_animation_speed(int i_frames_per_second)
{
    m_timer->setInterval(1000.f / i_frames_per_second);
}

void ViewerApp::on_actionNext_triggered()
{
    if(m_it)
        try_open_image(*(++m_it));
}

void ViewerApp::on_actionPrevious_triggered()
{
    if(m_it)
        try_open_image(*(--m_it));
}

void ViewerApp::next_frame()
{
    if(!has_image() || m_img->is_single_frame())
        return;

    Image img = m_img->next_image();
    img.set_palette(m_crw->m_palette);

    show_image(img);

    update_actions();
}

void ViewerApp::on_actionShow_Palette_triggered(bool checked)
{
    if(!has_palette())
        return;

    m_crw->setVisible(checked);
}

void ViewerApp::on_frames_per_second_control_valueChanged(int i_frames_per_second)
{
    set_animation_speed(i_frames_per_second);
}

void ViewerApp::on_next_frame_button_clicked()
{
    if(has_image())
        show_image(m_img->next_image());
}

void ViewerApp::on_previous_frame_button_clicked()
{
    if(has_image())
        show_image(m_img->previous_image());
}

void ViewerApp::on_play_pause_button_toggled(bool i_set_on_pause)
{
    i_set_on_pause ? m_timer->stop() : m_timer->start();
}
