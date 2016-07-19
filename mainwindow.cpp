#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addenterprise.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDB = new db();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addEnterprise_clicked()
{
    AddEnterprise addEnterprise(myDB,this);
    addEnterprise.exec();
}
