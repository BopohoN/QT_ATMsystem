#include "forgetpwd.h"
#include "ui_forgetpwd.h"

Forgetpwd::Forgetpwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Forgetpwd)
{
    ui->setupUi(this);

    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(on_okBtn_clicked()));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(on_cancelBtn_clicked()));

    connect((Login *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
    connect((ChatWindow *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
}

Forgetpwd::~Forgetpwd()
{
    delete ui;
}

QString update_sql_password = "update user set passwd = :passwd where email = :email";


void Forgetpwd::on_okBtn_clicked()
{
    bool b_infoflag = false;
    bool b_pwdflag = false;


    QString s_email=NULL;
    QString s_pwd=NULL;

    if(ui->mail_box->text() == ""||ui->pwd_box->text() == ""||ui->pwdcfm_box->text() == "")
    {
        qDebug()<<"info err";
        b_infoflag = false;
    }
    else if (ui->pwd_box->text() == ui->pwdcfm_box->text())
    {
        b_infoflag = true;
        b_pwdflag = true;
    }
    else
    {
        qDebug()<<"passwd err";
        b_pwdflag = false;
    }

    QSqlQuery sql_query;

    s_email = ui->mail_box->text();
    s_pwd = ui->pwdcfm_box->text();


    if(b_infoflag && b_pwdflag)
    {
        sql_query.prepare(update_sql_password);
        sql_query.bindValue(":email", s_email);
        sql_query.bindValue(":passwd", s_pwd);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<<"修改成功";
        }
    }
    else
    {
        qDebug()<<"修改失败";
    }

}

void Forgetpwd::receivedb(QSqlDatabase db)
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

void Forgetpwd::on_cancelBtn_clicked()
{
    this->close();
}
