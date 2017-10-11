#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "forgetpwd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void transmitdb(QSqlDatabase db);

private slots:
    void on_btn_save_clicked();
    void on_btn_take_clicked();
    void on_btn_trans_clicked();
    void on_btn_change_clicked();
    void receivedb(QSqlDatabase db);

private:
    QSqlDatabase database;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
