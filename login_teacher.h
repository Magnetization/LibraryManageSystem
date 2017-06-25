#ifndef LOGIN_TEACHER_H
#define LOGIN_TEACHER_H

#include <QDialog>

namespace Ui {
class Login_Teacher;
}

class Login_Teacher : public QDialog
{
    Q_OBJECT

public:
    explicit Login_Teacher(QWidget *parent = 0);
    ~Login_Teacher();

private slots:
    void on_pushButton_clicked();

    void on_BookFromFile_clicked();

private:
    Ui::Login_Teacher *ui;
};

#endif // LOGIN_TEACHER_H
