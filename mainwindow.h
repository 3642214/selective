#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"
#include "db.h"
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    db* myDB;
public slots:
     void addRow(QList<detail> d);

private slots:

    void on_addEnterprise_clicked();

    void on_seletiveButton_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
