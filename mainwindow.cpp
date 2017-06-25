#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <data.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BookSearch_clicked()
{
    this->hide();
    SearchWindow->setWindowTitle("图书查询");
    SearchWindow->show();
    SearchWindow->exec();
    this->show();
}

void MainWindow::on_Login_Button_clicked()
{
    QString UserName = ui->UserName_Edit->text();
    QString PassWord = ui->PassWord_Edit->text();
    QSqlQuery SearchMatch;
    QString Type;
    int flag = 0;
    SearchMatch.exec("select * from card");
    while(SearchMatch.next()){
        QString Name_Temp = SearchMatch.value(0).toString();
        QString Pass_Temp = SearchMatch.value(4).toString();
        Type = SearchMatch.value(3).toString();
        if(UserName.compare(Name_Temp)==0&&PassWord.compare(Pass_Temp)==0){
            data::ID = UserName;
            //ID = UserName; // 全局变量赋值
          //  qDebug() << ID ;
            if(Type.compare("T")==0){
                this->hide();
                TeacherWindow->setWindowTitle("Teacher Window");
                TeacherWindow->show();
                TeacherWindow->exec();
                this->show();
                flag = 1;
                break;
            }
            else if(Type.compare("S")==0){
                this->hide();
                StudentWindow->setWindowTitle("Student Window");
                StudentWindow->show();
                StudentWindow->exec();
                this->show();
                flag = 1;
                break;
            }
        }
    }
    if(flag==0){
        QMessageBox::warning(this,"Warning","Invalid UserName or Password",QMessageBox::Yes);
        ui->UserName_Edit->clear();
        ui->PassWord_Edit->clear();
        ui->UserName_Edit->setFocus();
    }
}
