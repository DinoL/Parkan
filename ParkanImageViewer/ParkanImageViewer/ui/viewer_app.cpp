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

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_animation()));
    timer->start(200);

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

    ui->verticalLayout->addWidget(m_scroll_area);
}

ViewerApp::~ViewerApp()
{
    delete ui;
}

void ViewerApp::on_select_palette_combo_box_activated(const QString& i_palette_name)
{
    set_palette(i_palette_name);
    if (m_img && m_crw)
    {
        m_img->set_palette(m_crw->m_palette);
        m_image_label->setPixmap(QPixmap::fromImage(m_img->image()));

        update_image();
    }
    update_actions();
}

void ViewerApp::on_actionExit_triggered()
{
    close();
}

void ViewerApp::on_actionOpen_Image_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (file_name.isEmpty())
        return;

    if(!m_crw)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "No palette", "Please select palette first");
        mb->show();
        return;
    }

    m_it = ImageIterator(file_name);
    if(m_it)
        open_image(*m_it);
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

    std::cout << "Exporting from " << file_name.toStdString() << " to " << out_file_name.toStdString() << std::endl;
    GeometryExporter().export_geometry(file_name, out_file_name);
}

void ViewerApp::on_actionSave_image_triggered()
{
    if(!m_img)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "No image", "Please open image first");
        mb->show();
        return;
    }
    const QString out_file_name = QFileDialog::getSaveFileName();
    if(out_file_name.isEmpty())
        return;

    const bool was_saved = m_img->save(out_file_name);
    if(!was_saved)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "Not saved",
                                   QString("Failed to save image into %1").arg(out_file_name));
        mb->show();
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

void ViewerApp::open_image(const QFileInfo& i_path)
{
    open_image(i_path.absoluteFilePath());
}

void ViewerApp::open_image(const QString& i_path)
{
    if(!m_crw || i_path.isEmpty())
        return;

    try
    {
        m_img = TextureFactory::build_image(i_path);
    }
    catch(const ImageDataException& e)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "Error", e.what());
        mb->show();
    }

    if (!m_img)
        return;

    m_img->set_palette(m_crw->m_palette);

    const QPixmap pixmap = QPixmap::fromImage(m_img->image());
    m_image_label->setPixmap(pixmap);
    m_image_label->adjustSize();
    m_image_label->resize(m_scale_factor * pixmap.size());

    ui->image_name->setText(QFileInfo(i_path).fileName());

    update_image();
    update_actions();
}

void ViewerApp::update_image()
{
    if(!m_img)
        return;

    ui->actionFit_to_Window->setEnabled(true);
}

bool ViewerApp::has_image() const
{
    return m_img != nullptr;
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

    ui->actionZoom_In->setEnabled(can_zoom);
    ui->actionZoom_Out->setEnabled(can_zoom);
    ui->actionNormal_Size->setEnabled(can_zoom);
    ui->actionSave_image->setEnabled(has_image());
    ui->actionNext->setEnabled(has_image());
    ui->actionPrevious->setEnabled(has_image());
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

void ViewerApp::on_actionNext_triggered()
{
    if(m_it)
        open_image(*(++m_it));
}

void ViewerApp::on_actionPrevious_triggered()
{
    if(m_it)
        open_image(*(--m_it));
}

void ViewerApp::on_actionOpen_animation_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (file_name.isEmpty())
        return;

    if(!m_crw)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "No palette", "Please select palette first");
        mb->show();
        return;
    }

    m_animation.reset(new AnimatedImage{QFileInfo(file_name)});
}

void ViewerApp::update_animation()
{
    if(!m_animation || !m_animation->is_valid())
        return;

    m_img.reset(new Image(m_animation->next_image()));
    if (!m_img)
        return;

    m_img->set_palette(m_crw->m_palette);
    m_image_label->setPixmap(QPixmap::fromImage(m_img->image()));

    update_image();
    update_actions();
}

void ViewerApp::on_actionShow_Palette_triggered(bool checked)
{
    if(!m_crw)
        return;

    if(checked)
    {
        m_crw->show();
    }
    else
    {
        m_crw->hide();
    }
}
