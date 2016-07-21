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
    ui->tableWidget->setColumnWidth(0,40);
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
    ui->tableWidget->resizeColumnsToContents();
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

void MainWindow::on_saveAsButton_clicked(){
    if(ui->tableWidget->rowCount() <1){
        QMessageBox::critical(0, tr("错误"), tr("请先搜索!"));
    return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save excel"),".", tr("Microsoft Office 2003 (*.csv)"));//获取保存路径
    if (fileName.isEmpty()) {
        QMessageBox::critical(0, tr("错误"), tr("要保存的文件名为空！"));
        return;
    }
    QFile* m_file = new QFile(fileName);
    if(m_file->open(QIODevice::WriteOnly))
    {
         m_file->write("\xEF\xBB\xBF");
//        m_file->write(new byte[]{(byte)0xEF,(byte)0xBB,(byte)0xBF});
        m_file->write("id:,");
        m_file->write("企业:,");
        m_file->write("废水量:,");
        m_file->write("地址:,");
        m_file->write("联系人:,");
        m_file->write("电话:,");
        m_file->write("上次被抽时间:");
        m_file->write("\n");

        for(int i = 0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {
                m_file->write(ui->tableWidget->item(i,j)->text().toUtf8().data());
                if(j!=ui->tableWidget->columnCount() -1)
                {
                    m_file->write(",");
                }
            }
            if(i!=ui->tableWidget->rowCount() -1 )
            {
                m_file->write("\n");
            }
        }
        m_file->close();
    }
    QMessageBox::information(this, tr("OK"), tr("保存成功！"));
}
