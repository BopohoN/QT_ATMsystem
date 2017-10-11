#ifndef TAKEMONEY_H
#define TAKEMONEY_H

#include <QDialog>
#include "chatwindow.h"
#include <QtSql>

namespace Ui {
class Takemoney;
}

class Takemoney : public QDialog
{
    Q_OBJECT

public:
    explicit Takemoney(QWidget *parent = 0);
    ~Takemoney();

private slots:
    void on_pushButton_clicked();
    void receivedb(QSqlDatabase db);
    void receivename(QString name);

private:
    Ui::Takemoney *ui;
    QSqlDatabase database;

    QString select_cash = "select * from cash where name = ?";
    QString update_cash = "update cash set cash = ? where name = ?";
    QString s_name;
};

#endif // TAKEMONEY_H
