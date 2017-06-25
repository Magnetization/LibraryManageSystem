#ifndef BORROW_H
#define BORROW_H

#include <QDialog>

namespace Ui {
class Borrow;
}

class Borrow : public QDialog
{
    Q_OBJECT

public:
    explicit Borrow(QWidget *parent = 0);
    ~Borrow();

private slots:
    void on_pushButton_clicked();

    void on_Book_ID_Edit_textChanged(const QString &arg1);

private:
    Ui::Borrow *ui;
};

#endif // BORROW_H
