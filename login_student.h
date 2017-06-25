#ifndef LOGIN_STUDENT_H
#define LOGIN_STUDENT_H

#include <QDialog>
#include <password_change.h>
#include <search.h>
#include <borrow.h>
#include <return.h>
namespace Ui {
class Login_Student;
}

class Login_Student : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Student(QWidget *parent = 0);
    ~Login_Student();

private slots:
    void on_Change_Password_clicked();

    void on_Search_Books_clicked();

    void on_Borrow_Books_clicked();

    void on_Return_Books_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login_Student *ui;
    Password_Change * Password_ChangeWindow = new Password_Change;
    Search * SearchStuWindow = new Search;
    Borrow * BorrowWindow = new Borrow;
    Return * ReturnWindow = new Return;
};

#endif // LOGIN_STUDENT_H
