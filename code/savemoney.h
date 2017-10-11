#ifndef SAVEMONEY_H
#define SAVEMONEY_H

#include <QDialog>
#include "chatwindow.h"
#include <QtSql>

namespace Ui {
class Savemoney;
}

class Savemoney : public QDialog
{
    Q_OBJECT

public:
    explicit Savemoney(QWidget *parent = 0);
    ~Savemoney();

private slots:
    void on_pushButton_clicked();
    void receivedb(QSqlDatabase db);
    void receivename(QString name);

private:
    Ui::Savemoney *ui;
    QSqlDatabase database;

    QString select_cash = "select * from cash where name = ?";
    QString update_cash = "update cash set cash = ? where name = ?";
    QString s_name;
};

#endif // SAVEMONEY_H
