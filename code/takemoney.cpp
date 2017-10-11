#include "takemoney.h"
#include "ui_takemoney.h"

Takemoney::Takemoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Takemoney)
{
    ui->setupUi(this);
    connect((ChatWindow *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
    connect((ChatWindow *)parent,SIGNAL(transmitname(QString)),this,SLOT(receivename(QString)));
}

Takemoney::~Takemoney()
{
    delete ui;
}

void Takemoney::receivedb(QSqlDatabase db)
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

void Takemoney::receivename(QString name)
{
    qDebug()<<"received name";
    s_name = name;
    qDebug()<<s_name;
}

void Takemoney::on_pushButton_clicked()
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
            float s_add = s_cash - s_money;
            if(s_add <0)
            {
                qDebug()<<"not enough money";
            }
            else
            {
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
}
