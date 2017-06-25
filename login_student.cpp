#include "login_student.h"
#include "ui_login_student.h"
#include "mainwindow.h"
#include <QDebug>
#include <data.h>
#include "password_change.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
Login_Student::Login_Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Student)
{
    ui->setupUi(this);
}

Login_Student::~Login_Student()
{
    delete ui;
}

void Login_Student::on_Change_Password_clicked()
{
    qDebug() << data::ID ;
    Password_ChangeWindow->show();
    Password_ChangeWindow->exec();
    if(data::Password_changed==true){
        this->close();
        data::Password_changed = false;
    }

}

void Login_Student::on_Search_Books_clicked()
{
    SearchStuWindow->show();
    SearchStuWindow->exec();
}

void Login_Student::on_Borrow_Books_clicked()
{
    BorrowWindow->show();
    BorrowWindow->exec();
}

void Login_Student::on_Return_Books_clicked()
{
    ReturnWindow->show();
    ReturnWindow->exec();

}

void Login_Student::on_pushButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select bno , borrow_date from borrow where cno ='"+data::ID+"' and return_date = '0' ");
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);

}
