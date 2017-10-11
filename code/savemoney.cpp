#include "savemoney.h"
#include "ui_savemoney.h"

Savemoney::Savemoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Savemoney)
{
    ui->setupUi(this);

    connect((ChatWindow *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
    connect((ChatWindow *)parent,SIGNAL(transmitname(QString)),this,SLOT(receivename(QString)));
}

Savemoney::~Savemoney()
{
    delete ui;
}

void Savemoney::receivedb(QSqlDatabase db)
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

void Savemoney::receivename(QString name)
{
    qDebug()<<"received name";
    s_name = name;
    qDebug()<<s_name;
}

void Savemoney::on_pushButton_clicked()
{
    if(ui->lineEdit->text()=="")
    {
        qDebug()<<"money is empty";

    }
    else
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
            float s_cash = sql_query.value(2).toFloat();
            float s_money = ui->lineEdit->text().toFloat();
            float s_add = s_cash + s_money;
            sql_query.prepare(update_cash);
            sql_query.addBindValue(s_add);
            sql_query.addBindValue(s_name);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"updated";
                this->close();
            }
        }
    }
}
