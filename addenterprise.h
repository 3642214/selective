#ifndef ADDENTERPRISE_H
#define ADDENTERPRISE_H

#include <QDialog>
#include "db.h"
#include <QList>

namespace Ui {
class AddEnterprise;
}

class AddEnterprise : public QDialog
{
    Q_OBJECT

public:
    explicit AddEnterprise(db* myDB,QWidget *parent = 0);
    ~AddEnterprise();
    void addRow(QList<detail> d);


private slots:
    void on_exit_clicked();

    void on_add_clicked();

    void on_del_clicked();

    void on_commit_clicked();

    void on_modify_clicked();

    void on_cancel_clicked();

    void on_search_clicked();

private:
    Ui::AddEnterprise *ui;
    void initItem(int row);
    void setCulReadOnlay();
    db* myDB;
    int modiftRow = -1;
    void setRowCanWrite(int row);
    void setRowUnWrite();
    void setAllUnWrite();
    Qt::ItemFlags defalutFlag;
    Qt::ItemFlags unWriteFlag;
    void hideBtn();
    void showBtn();
};

#endif // ADDENTERPRISE_H
