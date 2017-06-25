#include "return.h"
#include "ui_return.h"
#include "data.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>
Return::Return(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Return)
{
    ui->setupUi(this);
}

Return::~Return()
{
    delete ui;
}

void Return::on_ReturnButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString Book_ID = ui->Return_ID->text();
    if(Book_ID!=NULL){
        QSqlQuery Return;
        Return.exec("select * from borrow where bno ='"+Book_ID+"' and cno = '"+data::ID+"' ");
        Return.next();
        if(Return.value(0).toString()!=NULL){
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
        Return.exec("update borrow set return_date = '"+current_date+"' where bno = '"+Book_ID+"' and cno = '"+data::ID+"'");
        Return.exec("update book set stock = stock + 1 where bno = '"+Book_ID+"'");
        QMessageBox::warning(this,"warning","You have sueecssfully returned the book!",QMessageBox::Yes);
        }
        else{
            QMessageBox::warning(this,"warning","You haven't borrowed this book before!",QMessageBox::Yes);
        }



    model->setQuery("select * from book where bno = '"+Book_ID+"'");
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
    int row_count = model->rowCount();
        for(int i =0;i<row_count;i++){
            ui->tableView->setRowHeight(i,20);
        }
    }
}

void Return::on_Return_ID_textChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString Book_ID = ui->Return_ID->text();
    if(Book_ID!=NULL){
    model->setQuery("select * from book where bno = '"+Book_ID+"'");
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
    int row_count = model->rowCount();
        for(int i =0;i<row_count;i++){
            ui->tableView->setRowHeight(i,20);
        }
    }
}
