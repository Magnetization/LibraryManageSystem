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
    dbconn.setDatabaseName("Database_Name");//数据库名字
    dbconn.open("Username","Password");//用户名、密码，成功返回1
    query = (QSqlQuery)dbconn;
    MainWindow w;
    w.show();
    w.setWindowTitle("Welcome");
    return a.exec();
}
