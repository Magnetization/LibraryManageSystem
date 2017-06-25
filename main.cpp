#include "mainwindow.h"
#include <QApplication>
#include <QApplication>
#include <Qtsql>
#include <QDialog>
#include <search.h>
#include <QString>
#include <data.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSqlQuery  query;
    QSqlDatabase    dbconn;

    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName("localhost");//主机名字
    dbconn.setDatabaseName("library");//数据库名字
    dbconn.open("root","Tiffany19");//用户名、密码，成功返回1
    query = (QSqlQuery)dbconn;
    MainWindow w;
    w.show();
    w.setWindowTitle("欢迎使用浙江大学图书管理系统");
    return a.exec();
}
