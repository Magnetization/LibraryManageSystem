#include "login_teacher.h"
#include "ui_login_teacher.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <fstream>
#include <iostream>
#include<set>
#include<sstream>
#define MAXLEN 10000
Login_Teacher::Login_Teacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Teacher)
{
    ui->setupUi(this);
}

Login_Teacher::~Login_Teacher()
{
    delete ui;
}

void Login_Teacher::on_pushButton_clicked()
{
    ui->ID_Edit->setFocus();
    QString Book_ID = ui->ID_Edit->text();
    QString Category = ui->Category_Edit->text();
    QString Title = ui->Title_Edit->text();
    QString Press = ui->Press_Edit->text();
    QString Yearstr = ui->Year_Edit->text();
    QString Author = ui->Author_Edit->text();
    QString pricestr = ui->Price_lineEdit->text();
    QString numberstr = ui->Number_lineEdit->text();
    int Year = Yearstr.toInt();
    double price = pricestr.toDouble();
    int number = numberstr.toInt();
    QSqlQuery Query ;
//    QSqlQuery Query;
//    QSqlQuery Update;
//    QSqlQuery Insert;
    if(Book_ID!=NULL){
        Query.exec("select * from book where bno = '"+Book_ID+"'");
        Query.next();       //QSqlQuery返回的数据集，record是停在第一条记录之前的。所以，获得数据集后，必须执行next()或first()到第一条记录，这时候record才是有效的。否则，exec完直接value肯定报这个错
        //qDebug() << Query.value(0).toString();
        if(Query.value(0).toString()!=NULL){
            //qDebug() << Query.value(1).toString() <<endl;
            //qDebug() << Query.value(2).toString() <<endl;
            //qDebug() << Query.value(3).toString() <<endl;
            //qDebug() << Query.value(4).toString() <<endl;
            //() << Query.value(5).toString() <<endl;
            if(Category.compare(Query.value(1).toString())==0 && Title.compare(Query.value(2).toString())==0 && Press.compare(Query.value(3).toString())==0 && Yearstr.compare(Query.value(4).toString())==0 && Author.compare(Query.value(5).toString())==0 && pricestr.compare(Query.value(6).toString())==0)
            {
                //int yes = Query.exec("update book set total = total + :add, stock = stock + :add where bno = '"+Book_ID+"'");
                int yes = Query.exec("update book set total = total + ?, stock = stock + ? where bno = ?" );
                Query.addBindValue(number);
                Query.addBindValue(number);
                Query.addBindValue(Book_ID);
                Query.exec();
                qDebug() << "1" <<yes;
            }
            else {
                QMessageBox::warning(this,"Warning","Comflict Information for this book",QMessageBox::Yes);
                ui->ID_Edit->setFocus();
            }
        }
        else{
            int yes = Query.prepare("insert into book(bno,category,title,press,year,author,price,total,stock)" "values(?,?,?,?,?,?,?,?,?)");
            Query.bindValue(0,Book_ID);
            Query.bindValue(1,Category);
            Query.bindValue(2,Title);
            Query.bindValue(3,Press);
            Query.bindValue(4,Year);
            Query.bindValue(5,Author);
            Query.bindValue(6,price);
            Query.bindValue(7,number);
            Query.bindValue(8,number);
            Query.exec();
//            int yes = Query.exec("insert into book values('"+Book_ID+"','"+Category+"','"+Title+"','"+Press+"',:year,'"+Author+"', :money, :add)");
//            Query.bindValue(":year",Year);
//            Query.bindValue(":money",price);
//            Query.bindValue(":add",number);
           // qDebug() << "2 "<<yes;
        //    QMessageBox::warning(this,"Warning","Book Storage Completed",QMessageBox::Yes);

        }
        QMessageBox::warning(this,"Warning","Book Storage Completed",QMessageBox::Yes);

    }
    else{
        QMessageBox::warning(this,"Warning","Invalid Book Storage Instructions",QMessageBox::Yes);
    }
}

void Login_Teacher::on_BookFromFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Txt"),".",tr("Txt Files(*.txt)"));
    if(path.length()==0){
        QMessageBox::information(NULL,"Path","You didn't select any files.");
    }else{
        QMessageBox::information(NULL,"Path","You Select " + path);
    }
    qDebug() << path << endl;
    QFile *file = new  QFile(path);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open the file" << endl;
    }
    else {
        int index = 0;
        QString Input[MAXLEN][8];
        while(!file->atEnd()){
            QString temp = file->readLine();
            QStringList InList = temp.split(";");
            for(int i=0;i<8;i++){
                Input[index][i] = InList.at(i);
            }
            index ++;
        }
        for(int i =0;i<index;i++){
            QSqlQuery Query;
            if(Input[i][0]!=NULL){
                Query.exec("select * from book where bno = '"+Input[i][0]+"'");
                Query.next();
                bool comfilct = false;
                if(Query.value(0).toString()!=NULL){
                    for(int j = 1; j<=6; j++){
                        if(Input[i][j].compare(Query.value(j).toString())!=0){
                            comfilct = true;
                            break;
                        }
                    }
                    if(comfilct){
                        continue;
                    }
                    else{
                        int yes = Query.exec("update book set total = total + ?, stock = stock + ? where bno = ?" );
                        Query.addBindValue(Input[i][7]);
                        Query.addBindValue(Input[i][7]);
                        Query.addBindValue(Input[i][0]);
                        Query.exec();
                        qDebug() << "3" <<yes;
                    }
                }
                else {
                    int yes = Query.prepare("insert into book(bno,category,title,press,year,author,price,total,stock)" "values(?,?,?,?,?,?,?,?,?)");
                    Query.bindValue(0,Input[i][0]);
                    Query.bindValue(1,Input[i][1]);
                    Query.bindValue(2,Input[i][2]);
                    Query.bindValue(3,Input[i][3]);
                    Query.bindValue(4,Input[i][4]);
                    Query.bindValue(5,Input[i][5]);
                    Query.bindValue(6,Input[i][6]);
                    Query.bindValue(7,Input[i][7]);
                    Query.bindValue(8,Input[i][7]);
                    Query.exec();
                }
            }
        }
    }

    // 得到path,之后对文件进行操作
}
