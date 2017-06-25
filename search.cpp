#include "search.h"
#include "ui_search.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

Search::~Search()
{
    delete ui;
}

void Search::on_SearchButton_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    if(ui->ID_Edit->text()!=NULL && ui->Name_Edit->text()==NULL){

  //  QSqlQuery query;
        QString Book_ID = ui->ID_Edit->text();
        model->setQuery("select * from book where bno ='"+Book_ID+"'");

    }
    else if(ui->ID_Edit->text()==NULL && ui->Name_Edit->text()!=NULL){
        QString Book_Name_search = "%";
        QString Book_Name_temp = ui->Name_Edit->text();
        Book_Name_search.append(Book_Name_temp);
        Book_Name_search.append("%");
    //model->setQuery("select * from book where title like '"+Book_Name_temp+"' ");
        model->setQuery("select * from book where title like '"+Book_Name_search+"'");
    }
    else if(ui->ID_Edit->text()!=NULL && ui->Name_Edit->text()!=NULL){
        QString Book_ID = ui->ID_Edit->text();
        QString Book_Name_search = "%";
        QString Book_Name_temp = ui->Name_Edit->text();
        Book_Name_search.append(Book_Name_temp);
        Book_Name_search.append("%");
        model->setQuery("select * from book where title like '"+Book_Name_search+"' and bno = '"+Book_ID+"'");
    }

    ui->SearchResult->setModel(model);
    ui->SearchResult->setAlternatingRowColors(true);
    int row_count  = model->rowCount();
    for(int i;i<row_count;i++){
        ui->SearchResult->setRowHeight(i,15);
    }
}
