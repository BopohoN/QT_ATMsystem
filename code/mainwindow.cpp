#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect((Login *)parent,SIGNAL(transmitdb(QSqlDatabase)),this,SLOT(receivedb(QSqlDatabase)));
}

void MainWindow::receivedb(QSqlDatabase db)
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_save_clicked()
{

}

void MainWindow::on_btn_take_clicked()
{

}

void MainWindow::on_btn_trans_clicked()
{

}

void MainWindow::on_btn_change_clicked()
{
    Forgetpwd f(this);
    this->hide();
    f.show();
    transmitdb(database);
    f.exec();
    this->show();
}
