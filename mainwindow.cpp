#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addenterprise.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open db file"), ".", tr("db Files (*.db)"));
    myDB = new db(fileName);
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
