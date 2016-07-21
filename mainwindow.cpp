#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addenterprise.h"
#include <QDebug>
#include <QFileDialog>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    QString fileName = QFileDialog::getOpenFileName(this,
    //        tr("Open db file"), ".", tr("db Files (*.db)"));
    myDB = new db("./selective.db");
    qsrand(time(NULL));
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
    int enterPriseCount = 0;
    QList<detail> list = myDB->searchEnterprise(water,enterPrise);
    QList<detail> newList;
    switch (per) {
    case 0:
        enterPriseCount = list.size()*0.05;
        break;
    case 1:
        enterPriseCount = list.size()*0.1;
        break;
    case 2:
        enterPriseCount = list.size()*0.3;
        break;
    default:
        break;
    }
     QMessageBox::critical(0, tr(""), tr("符合的企业数 ")+QString::number(list.size()) +tr("个.抽签企业数 ")+QString::number(enterPriseCount)+tr("个"));
    qDebug()<<"符合企业数"<<list.size()<<" 抽签数 "<<enterPriseCount+1;
    for(int i = 0;i<enterPriseCount;i++){
        int n = qrand() % list.size();
        newList<<list.at(n);
        list.removeAt(n);
    }

    addRow(newList);
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
