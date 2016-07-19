#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"

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

private slots:

    void on_addEnterprise_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
