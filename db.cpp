#include "db.h"
#include <QFileDialog>
#include <QString>

db::db(QString fileName)
{
    //    ddb = QSqlDatabase::addDatabase(QSqlDatabase::driver())
    ddb = QSqlDatabase::addDatabase("QSQLITE");
    //    ddb.setDatabaseName("./selective.db");
    ddb.setDatabaseName(fileName);
    if(!ddb.open())
    {
        //        QMessageBox::critical(0, QObject::tr("错误"),QObject::tr("无法打开数据库文件。。。！！！"));
        QMessageBox::critical(0, QObject::tr("错误"),ddb.lastError().text());
        exit(0);
    }
}

void db::initDB()
{
    QSqlQuery sql_q;
    if(!sql_q.exec("CREATE TABLE detail (id INTEGER  PRIMARY KEY AUTOINCREMENT DEFAULT NULL,name TEXT DEFAULT NULL,wasteWater INTEGER DEFAULT NULL,address TEXT DEFAULT NULL,contract TEXT DEFAULT NULL,phone TEXT DEFAULT NULL,lastTime TEXT DEFAULT NULL)"))
    {
        logError;
    }
    else
    {
        logOK;
    }
}

QList<detail> db::getAllEnterprise()
{
    QList<detail> enterprises;
    QSqlQuery sql_q;
    QString getEtalon_sql = "SELECT * FROM detail";
    sql_q.prepare(getEtalon_sql);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        detail myDetail = SETDETAIL;
        qdebugDetail;
        enterprises<<myDetail;
    }
    return enterprises;
}

bool db::setDetail(detail myDetail)
{
    qDebug()<<"set detail :";
    qdebugDetail;
    QSqlQuery sql_q;
    QString setDetail_sql = "insert into detail (id,name,wasteWater,address,contract,phone,lastTime) VALUES (:id,:name,:wasteWater,:address,:contract,:phone,:lastTime)";
    sql_q.prepare(setDetail_sql);
    sql_q.bindValue(":name",myDetail.name);
    sql_q.bindValue(":wasteWater",myDetail.wasteWater);
    sql_q.bindValue(":address",myDetail.address);
    sql_q.bindValue(":contract",myDetail.contract);
    sql_q.bindValue(":phone",myDetail.phone);
    sql_q.bindValue(":lastTime",myDetail.lastTime);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        detail myDetail = SETDETAIL;
        qdebugDetail;
    }
    return true;
}

bool db::updateDetail(detail myDetail)
{
    qDebug()<<"update detail :";
    qdebugDetail;
    QSqlQuery sql_q;
    QString setDetail_sql = "update detail set name = :name,wasteWater = :wasteWater,address = :address,contract = :contract ,phone = :phone,lastTime = :lastTime where id = :id";
    sql_q.prepare(setDetail_sql);
    sql_q.bindValue(":name",myDetail.name);
    sql_q.bindValue(":wasteWater",myDetail.wasteWater);
    sql_q.bindValue(":address",myDetail.address);
    sql_q.bindValue(":contract",myDetail.contract);
    sql_q.bindValue(":phone",myDetail.phone);
    sql_q.bindValue(":lastTime",myDetail.lastTime);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    return true;

}

bool db::delDetail(int ID)
{
    QSqlQuery sql_q;
    QString delDetail_sql = "delete from detail where id = :id";
    sql_q.prepare(delDetail_sql);
    sql_q.bindValue(":id",ID);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    return true;
}

int db::getLastId()
{
    int result = 0;
    QSqlQuery sql_q;
    QString delDetail_sql = "select last_insert_rowid() from detail";
    sql_q.prepare(delDetail_sql);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    if (sql_q.next()) {
        result = sql_q.value(0).toInt();
        qDebug()<<"result is "<<result;
    }
    return result;
}

QList<detail> db::searchEnterprise(QString name)
{
    QList<detail> enterprises;
    QSqlQuery sql_q;
    QString getEtalon_sql = "select * from detail where name like \"%"+name+"%\"";
    qDebug()<<getEtalon_sql;
    sql_q.prepare(getEtalon_sql);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        detail myDetail = SETDETAIL;
        qdebugDetail;
        enterprises<<myDetail;
    }
    return enterprises;
}

//搜索符合条件的企业
QList<detail> db::searchEnterprise(int water ,bool allEnterPrise)
{
    QList<detail> enterprises;
    QSqlQuery sql_q;
    QString enterprisesString,waterString;
    if(!allEnterPrise){
        enterprisesString = "and lastTime is null";
    }
    switch (water) {
    case 0:
        waterString = "wasteWater => 500 and wasteWater <= 1000 ";
        break;
    case 1:
        waterString = "wasteWater => 1001 and wasteWater <= 5000 ";
        break;
    case 2:
        waterString = "wasteWater => 5000 ";
        break;
    default:
        break;
    }
    QString getEtalon_sql = "select * from detail where "+waterString + enterprisesString;
    qDebug()<<getEtalon_sql;
    sql_q.prepare(getEtalon_sql);
    if(!sql_q.exec())
    {
        logError;
    }
    else
    {
        logOK;
    }
    while (sql_q.next()) {
        detail myDetail = SETDETAIL;
        qdebugDetail;
        enterprises<<myDetail;
    }
    return enterprises;
}
