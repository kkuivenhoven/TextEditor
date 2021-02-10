#include "mainwindow.h"
#include "ui_mainwindow.h"


/* https://stackoverflow.com/questions/3860112/multiple-github-accounts-on-the-same-computer */
// http://zetcode.com/gui/qt5/menusandtoolbars/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    MyCustomWidget *customWidget = new MyCustomWidget();
}


MainWindow::~MainWindow() {
    delete ui;
}

