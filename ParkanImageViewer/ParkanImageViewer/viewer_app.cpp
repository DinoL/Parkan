#include "viewer_app.h"
#include "ui_viewer_app.h"

ViewerApp::ViewerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerApp)
{
    ui->setupUi(this);
}

ViewerApp::~ViewerApp()
{
    delete ui;
}
