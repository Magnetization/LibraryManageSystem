#include "password_change.h"
#include "ui_password_change.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "data.h"
Password_Change::Password_Change(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password_Change)
{
    ui->setupUi(this);
}

Password_Change::~Password_Change()
{
    delete ui;
}

bool Password_Change::on_pushButton_clicked()
{
    QString NewPas = ui->New->text();
    QString NewPasAgain = ui->New_Again->text();
    QSqlQuery ChangePas;
    qDebug() << data::ID;
    if(NewPas.compare(NewPasAgain)==0){
       int yes = ChangePas.exec("update card set password = '"+NewPas+"' where cno = '"+data::ID+"';");
        if(yes) QMessageBox::warning(this,"Warning","Success! Please Login Again",QMessageBox::Yes);
        this->close();
        data::Password_changed = true;
        return true;
    }
    else{
        QMessageBox::warning(this,"Warning","Two Passwords are not the same",QMessageBox::Yes);
        ui->New->clear();
        ui->New_Again->clear();
        ui->New->setFocus();
    }
    return false;

}
