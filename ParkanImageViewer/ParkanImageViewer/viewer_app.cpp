#include "viewer_app.h"
#include "ui_viewer_app.h"

#include "color_ramp_widget.h"

ViewerApp::ViewerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerApp), m_crw(nullptr)
{
    ui->setupUi(this);
}

ViewerApp::~ViewerApp()
{
    delete ui;
}

void ViewerApp::on_pushButton_clicked()
{
    const QFileInfo file("P.COL");
    const Palette palette(file);
    m_crw.reset(new ColorRampWidget(palette));
}
