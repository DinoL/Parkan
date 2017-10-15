#include "viewer_app.h"
#include "ui_viewer_app.h"

#include "color_ramp_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

ViewerApp::ViewerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerApp), m_crw(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Parkan Image Viewer");

    QStringList all_palettes = QDir(get_palettes_folder()).entryList();
    ui->select_palette_combo_box->addItems(all_palettes);
}

ViewerApp::~ViewerApp()
{
    delete ui;
}

void ViewerApp::on_select_palette_combo_box_activated(const QString& file_name)
{
    const QFileInfo file(get_palettes_folder() + file_name);
    const Palette palette(file);
    m_crw.reset(new ColorRampWidget(palette));
}

QString ViewerApp::get_palettes_folder() const
{
    return ":/palettes/";
}

void ViewerApp::on_actionExit_triggered()
{
    close();
}

void ViewerApp::on_actionOpen_Image_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (!file_name.isEmpty())
    {
        auto* mb = new QMessageBox(QMessageBox::NoIcon, "Open", file_name);
        mb->show();
    }
}
