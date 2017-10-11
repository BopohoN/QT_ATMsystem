#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include "forgetpwd.h"
#include "savemoney.h"
#include "takemoney.h"
#include "transcash.h"
#include <QtSql>


namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

signals:
    void transmitdb(QSqlDatabase db);
    void transmitname(QString name);

private slots:
    void on_btn_change_clicked();
    void on_btn_save_clicked();
    void on_btn_take_clicked();
    void on_btn_trans_clicked();
    void receivedb(QSqlDatabase db);
    void receivename(QString name);

    void on_pushButton_clicked();

private:
    QSqlDatabase database;
    QString s_name;
    Ui::ChatWindow *ui;
    bool tableFlag;

    QString select_cash = "select * from cash where name = ?";
};

#endif // CHATWINDOW_H
