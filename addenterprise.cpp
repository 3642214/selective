#include "addenterprise.h"
#include "ui_addenterprise.h"

AddEnterprise::AddEnterprise(db* myDB,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEnterprise),
    myDB(myDB)
{
    ui->setupUi(this);
    //    this->myDB->initDB();
    //    detail mDetail = {1,"222",33,"44","55","66","77"};
    //    this->myDB->setDetail(mDetail);

    this->addRow(this->myDB->getAllEnterprise());
    defalutFlag = ui->tableWidget->item(0,0)->flags();
    unWriteFlag = defalutFlag&~(Qt::ItemIsEditable);
    setAllUnWrite();
    hideBtn();
}

void AddEnterprise::addRow(QList<detail> d){
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

AddEnterprise::~AddEnterprise()
{
    delete ui;
}

void AddEnterprise::on_exit_clicked()
{
    this->close();
}


void AddEnterprise::on_add_clicked()
{
    int row = ui->tableWidget->rowCount();
    for(int i = 0 ; i < row ; i++)
    {
        if(ui->tableWidget->item(i,0)->text() == "")
        {
            QMessageBox::critical(0, tr("警告"), tr("上次新增的一行未提交,请先提交!!!"));
            return;
        }
    }
    ui->tableWidget->setRowCount(row + 1);
    initItem(row);
    setRowCanWrite(row);
    ui->tableWidget->setCurrentCell(row,1);
    ui->tableWidget->editItem(ui->tableWidget->item(row,1));
    showBtn();
}

void AddEnterprise::initItem(int row)
{
    int colSize = ui->tableWidget->columnCount();
    qDebug()<<"column size is "<<colSize;
    for(int i = 0;i<colSize;i++)
    {
        ui->tableWidget->setItem(row,i,new QTableWidgetItem(QString("")));
    }
}

void AddEnterprise::setRowCanWrite(int row)
{
    modiftRow = row;
    int culSize = ui->tableWidget->columnCount();
    for(int i=1;i<culSize-1;i++){
        ui->tableWidget->item(modiftRow,i)->setFlags(defalutFlag);
    }
    ui->tableWidget->item(modiftRow,culSize-1)->setFlags(unWriteFlag);
}

void AddEnterprise::setRowUnWrite()
{
    ui->widget->setFocus();
    int culSize = ui->tableWidget->columnCount();
    for(int i=0;i<culSize;i++){
        ui->tableWidget->item(modiftRow,i)->setFlags(unWriteFlag);
    }
    modiftRow=-1;
}

void AddEnterprise::setAllUnWrite()
{
    int culSize = ui->tableWidget->columnCount();
    int rowSize = ui->tableWidget->rowCount();
    for(int j=0;j<rowSize;j++){
        for(int i=0;i<culSize;i++){
            ui->tableWidget->item(j,i)->setFlags(unWriteFlag);
        }
    }
}


void AddEnterprise::setCulReadOnlay()
{
    int rowSize = ui->tableWidget->rowCount();
    qDebug()<<"row size is "<<rowSize;
    for(int i=0;i<rowSize;i++)
    {
        ui->tableWidget->item(i, 0)->setFlags(unWriteFlag);
        ui->tableWidget->item(i, 6)->setFlags(unWriteFlag);
    }
}

void AddEnterprise::on_del_clicked()
{
    if(ui->tableWidget->rowCount() > 0 and ui->tableWidget->currentRow() >= 0)
    {
        QMessageBox::StandardButton delWarn = QMessageBox::warning(NULL, "删除提示", "是否删除第"+QString::number(ui->tableWidget->currentRow() + 1,10)+"行数据,删除无法恢复!!!", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(delWarn == QMessageBox::Yes)
        {
            //            qDebug()<<ui->tableWidget->currentRow();
            int id = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toInt();
            myDB->delDetail(id);
            ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        }
    }
    //    outEditMode();
}


void AddEnterprise::on_commit_clicked()
{
    int row = modiftRow;
    //    qDebug()<<"row is "<<row;
    if(row < 0)
    {
        QMessageBox::critical(0, tr("警告"), tr("请选择需要提交的一行记录"));
        return;
    }
    setRowUnWrite();
    detail m_detal ={
        ui->tableWidget->item(row,0)->text().toInt(),
        ui->tableWidget->item(row,1)->text(),
        ui->tableWidget->item(row,2)->text().toInt(),
        ui->tableWidget->item(row,3)->text(),
        ui->tableWidget->item(row,4)->text(),
        ui->tableWidget->item(row,5)->text(),
        ui->tableWidget->item(row,6)->text()
    };
    qDebug()<<"m_detal.id "<<m_detal.id;
    if(m_detal.id == 0)
    {
        myDB->setDetail(m_detal);
        ui->tableWidget->item(row,0)->setText(QString::number(myDB->getLastId(), 10));
    }
    else {
        myDB->updateDetail(m_detal);
    }
    hideBtn();
}

void AddEnterprise::on_cancel_clicked()
{
    setRowUnWrite();
    ui->tableWidget->clearSelection();
    hideBtn();
}


void AddEnterprise::on_modify_clicked()
{
    setRowCanWrite(ui->tableWidget->currentRow());
    ui->tableWidget->editItem(ui->tableWidget->item(modiftRow,1));
    showBtn();
}

void AddEnterprise::hideBtn(){
    ui->commit->setEnabled(false);
    ui->cancel->setEnabled(false);
    ui->add->setEnabled(true);
    ui->del->setEnabled(true);
    ui->modify->setEnabled(true);
    ui->search->setEnabled(true);
}

void AddEnterprise::showBtn(){
    ui->commit->setEnabled(true);
    ui->cancel->setEnabled(true);
    ui->add->setEnabled(false);
    ui->del->setEnabled(false);
    ui->modify->setEnabled(false);
    ui->search->setEnabled(false);
}

void AddEnterprise::on_search_clicked()
{
    ui->tableWidget->setRowCount(0);
    addRow(myDB->searchEnterprise(ui->ext->text()));
}
