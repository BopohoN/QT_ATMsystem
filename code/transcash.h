#ifndef TRANSCASH_H
#define TRANSCASH_H

#include <QDialog>
#include "chatwindow.h"
#include <QtSql>

namespace Ui {
class Transcash;
}

class Transcash : public QDialog
{
    Q_OBJECT

public:
    explicit Transcash(QWidget *parent = 0);
    ~Transcash();

private slots:
    void on_pushButton_clicked();
    void receivedb(QSqlDatabase db);
    void receivename(QString name);

private:
    Ui::Transcash *ui;
    QSqlDatabase database;

    QString select_cash = "select * from cash where name = ?";
    QString update_cash = "update cash set cash = ? where name = ?";
    QString s_name;
};

#endif // TRANSCASH_H
