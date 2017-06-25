#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <search.h>
#include <login_student.h>
#include <login_teacher.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString ID;

private slots:
    void on_BookSearch_clicked();

    void on_Login_Button_clicked();

private:
    Ui::MainWindow *ui;
    Search * SearchWindow = new Search;
    Login_Student * StudentWindow = new Login_Student;
    Login_Teacher * TeacherWindow = new Login_Teacher;

 };

#endif // MAINWINDOW_H
