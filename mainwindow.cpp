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

//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open db file"), ".", tr("db Files (*.db)"));
    myDB = new db("./selective.db");
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

void MainWindow::on_seletiveButton_clicked()
{
    int water = ui->waterCombo->currentIndex();
    int per = ui->perCombo->currentIndex();
    int enterPrise = ui->enterpriseCombo->currentIndex();

    addRow(myDB->searchEnterprise(water,enterPrise));
}

void MainWindow::addRow(QList<detail> d){
    int detailsSize = d.size();
    if(detailsSize>=0)
    {
        ui->tableWidget->setRowCount(detailsSize);
        int i = 0;
        for(;i<detailsSize;i++){
            detail m_detail = d.at(i);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(m_detail.id)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(m_detail.name)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(m_detail.wasteWater)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString(m_detail.address)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString(m_detail.contract)));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString(m_detail.phone)));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString(m_detail.lastTime)));
        }
    }
}
