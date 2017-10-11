#ifndef FORGETPWD_H
#define FORGETPWD_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include "login.h"

namespace Ui {
class Forgetpwd;
}

class Forgetpwd : public QDialog
{
    Q_OBJECT

public:
    explicit Forgetpwd(QWidget *parent = 0);
    ~Forgetpwd();



private:
    Ui::Forgetpwd *ui;

    QSqlDatabase database;

private slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();
    void receivedb(QSqlDatabase db);

};

#endif // FORGETPWD_H
