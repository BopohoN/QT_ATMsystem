#include "transcash.h"
#include "ui_transcash.h"

Transcash::Transcash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transcash)
{
    ui->setupUi(this);
    connect((ChatWindow *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
    connect((ChatWindow *)parent,SIGNAL(transmitname(QString)),this,SLOT(receivename(QString)));
}

Transcash::~Transcash()
{
    delete ui;
}


void Transcash::receivedb(QSqlDatabase db)
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

void Transcash::receivename(QString name)
{
    qDebug()<<"received name";
    s_name = name;
    qDebug()<<s_name;
}

void Transcash::on_pushButton_clicked()
{
    if(ui->rec_name->text()=="" || ui->send_cash->text()=="")
    {
        qDebug()<<"info error";
    }
    else
    {
        float s_cash_change = ui->send_cash->text().toFloat();

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
            float s_cash_send = sql_query.value(2).toFloat();

            sql_query.prepare(select_cash);
            sql_query.addBindValue(ui->rec_name->text());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                sql_query.first();
                float s_cash_rec = sql_query.value(2).toFloat();

                float s_fincash_send = s_cash_send - s_cash_change;
                float s_fincash_rec = s_cash_rec + s_cash_change;
                if(s_fincash_send<0)
                {
                    qDebug()<<"not enough money";
                }
                else
                {
                    sql_query.prepare(update_cash);
                    sql_query.addBindValue(s_fincash_send);
                    sql_query.addBindValue(s_name);
                    if(!sql_query.exec())
                    {
                        qDebug()<<"A:";
                        qDebug()<<sql_query.lastError();
                    }
                    else
                    {
                        sql_query.prepare(update_cash);
                        sql_query.addBindValue(s_fincash_rec);
                        sql_query.addBindValue(ui->rec_name->text());
                        if(!sql_query.exec())
                        {
                            qDebug()<<"B:";
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

    }
}
