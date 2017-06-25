#include "borrow.h"
#include "ui_borrow.h"
#include <QString>'
#include <QSqlQueryModel>
#include <data.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
Borrow::Borrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Borrow)
{
    ui->setupUi(this);
}

Borrow::~Borrow()
{
    delete ui;
}

void Borrow::on_pushButton_clicked()
{
    QString Borrow_ID = ui->Book_ID_Edit->text();
    QSqlQuery Query;
    if(Borrow_ID!=NULL){
        Query.exec("select * from book where bno = '"+Borrow_ID+"'");
        Query.next();
        if(Query.value(0).toString()!=NULL){

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
        //qDebug() << current_date <<endl;
        if(Query.value(8).toInt()==0){
            QMessageBox::warning(this,"warning","The book you selected is out of stock!Try another one.",QMessageBox::Yes);
        }else{
            QSqlQuery Borrow;
            Borrow.prepare("insert into borrow(cno,bno,borrow_date,return_date)" "values(?,?,?,?)");
            Borrow.bindValue(0,data::ID);
            Borrow.bindValue(1,Borrow_ID);
            Borrow.bindValue(2,current_date);
            Borrow.bindValue(3,NULL);
            Borrow.exec();
            QSqlQuery Stock_Update;
            Stock_Update.exec("update book set stock = stock -1 where bno = '"+Borrow_ID+"'");
            QMessageBox::warning(this,"warning","You have successfully borrowed the book: "+Query.value(2).toString(),QMessageBox::Yes);
        }
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("Select * from book where bno = '"+Borrow_ID+"'");
        ui->tableView->setModel(model);
        //ui->SearchResult->setModel(model);
        ui->tableView->setAlternatingRowColors(true);
        int row_count  = model->rowCount();
            for(int i;i<row_count;i++){
                ui->tableView->setRowHeight(i,20);
            }
        //借书
        }
        else {
          QMessageBox::warning(this,"Warning","Please Enter the correct ID if books!",QMessageBox::Yes);
        }
    }
}

void Borrow::on_Book_ID_Edit_textChanged(const QString &arg1)
{
    QString match = "%";
    QString Borrow_ID = ui->Book_ID_Edit->text();
    match.append(Borrow_ID);
    match.append("%");
    QSqlQuery Query;
    if(Borrow_ID!=NULL){
        Query.exec("select * from book where bno like '"+match+"'");
        Query.next();
        if(Query.value(0).toString()!=NULL){
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("Select * from book where bno like  '"+match+"'");
        ui->tableView->setModel(model);
        //ui->SearchResult->setModel(model);
        ui->tableView->setAlternatingRowColors(true);
        int row_count  = model->rowCount();
            for(int i;i<row_count;i++){
                ui->tableView->setRowHeight(i,20);
            }
        }

    }
}
