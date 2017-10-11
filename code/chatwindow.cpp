#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    connect((Login *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
    connect((Login *)parent,SIGNAL(transmitname(QString)),this,SLOT(receivename(QString)));



}

void ChatWindow::receivedb(QSqlDatabase db)
{
    qDebug()<<"received db";
    database=db;
    if(!database.isOpen())
    {
        if(!database.open())
        {
            qDebug()<<database.lastError();
            qFatal("failed to connect.") ;
            return;
        }
        else
        {
        }
    }
}

void ChatWindow::receivename(QString name)
{
    qDebug()<<"received name";
    s_name = name;
    qDebug()<<s_name;
    ui->label_name->setText(s_name);
    QSqlQuery sql_query;
    sql_query.prepare(select_cash);
    sql_query.addBindValue(s_name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        sql_query.first();
        QString s_cash = sql_query.value(2).toString();
        ui->label_cash->setText(s_cash);
    }
}

ChatWindow::~ChatWindow()
{
    delete ui;
}



void ChatWindow::on_btn_change_clicked()
{
    Forgetpwd f(this);
    f.show();
    transmitdb(database);
    f.exec();
    this->show();
}

void ChatWindow::on_btn_save_clicked()
{
    Savemoney f(this);
    f.show();
    transmitdb(database);
    transmitname(s_name);
    f.exec();
    this->show();
}

void ChatWindow::on_btn_take_clicked()
{
    Takemoney f(this);
    f.show();
    transmitdb(database);
    transmitname(s_name);
    f.exec();
    this->show();
}

void ChatWindow::on_btn_trans_clicked()
{
    Transcash f(this);
    f.show();
    transmitdb(database);
    transmitname(s_name);
    f.exec();
    this->show();
}

void ChatWindow::on_pushButton_clicked()
{
    QSqlQuery sql_query;
    sql_query.prepare(select_cash);
    sql_query.addBindValue(s_name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        sql_query.first();
        QString s_cash = sql_query.value(2).toString();
        ui->label_cash->setText(s_cash);
    }
}
