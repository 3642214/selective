#ifndef DB_H
#define DB_H

#include <QList>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

#define qdebugDetail     qDebug()<<"get details :"; \
                         qDebug()<<myDetail.id<<myDetail.name<<myDetail.wasteWater<<myDetail.address<<myDetail.contract<<myDetail.phone<<myDetail.lastTime

#define SETDETAIL {    \
                    sql_q.value(0).toInt(), \
                    sql_q.value(1).toString(), \
                    sql_q.value(2).toInt(),  \
                    sql_q.value(3).toString(),  \
                    sql_q.value(4).toString(),  \
                    sql_q.value(5).toString(), \
                    sql_q.value(6).toString(), \
                    }

#define logError QString errorCode =  sql_q.lastError().text();\
    qDebug()<<__FUNCTION__<<" error :"<<errorCode;\
    QMessageBox::critical(0, QObject::tr("错误"),"错误名>>" + errorCode + " << ,操作数据库失败!!!")

#define logOK qDebug()<<__FUNCTION__<<" ok"

typedef struct
{
    int id;             //id
    QString name;       //企业名称
    int wasteWater;     //废水量
    QString address;    //企业地址
    QString contract;   //联系人
    QString phone;      //电话
    QString lastTime;   //最后次抽中时间
} detail;

class db
{
private:
    QSqlDatabase ddb;
public:
    db(QString fileName);
    void initDB();
    QList<detail> getAllEnterprise();
    bool setDetail(detail myDetail);
    bool delDetail(int id);
    bool updateDetail(detail myDetail);
    QList<detail> searchEnterprise(QString name);
    QList<detail> searchEnterprise(int water ,bool allEnterPrise);
    int getLastId();
    bool cleanTime();
    bool setTime(QString time ,int id);
};

#endif // DB_H
