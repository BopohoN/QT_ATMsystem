#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include "chatwindow.h"
#include "forgetpwd.h"
#include <QPainter>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void transmitdb(QSqlDatabase db);
    void transmitname(QString name);

private slots:
    void login_clicked();   //登录按键槽函数
    void register_clicked();    //注册按键槽函数
    void getUserInfo(QString name);
    void on_fpBtn_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase database;
    bool tableFlag;

    int usr_id;
    QString usr_passwd;
    QString usr_name;
    QString usr_email;
    int usr_history;
    bool matchFlag;

    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    QString create_sql_user = "create table user (chatid int primary key, passwd varchar(30), name varchar(30), email varchar(30), history int)";
    QString create_sql_cash = "create table cash (chatid int primary key, name varchar(30), cash float)";
    QString select_max_sql = "select max(chatid) from user";
    QString insert_sql_user = "insert into user values (?, ?, ?, ? ?)";
    //QString update_sql = "update user set name = :name where chatid = :chatid";
    QString select_sql_user = "select name from user";
    //QString select_all_sql = "select * from user";
    //QString delete_sql = "delete from user where chatid = ?";
    //QString clear_sql = "delete from user";

    QString select_nameInfo = "selcet * from user where name=";


};

#endif // LOGIN_H
