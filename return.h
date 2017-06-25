#ifndef RETURN_H
#define RETURN_H

#include <QDialog>

namespace Ui {
class Return;
}

class Return : public QDialog
{
    Q_OBJECT

public:
    explicit Return(QWidget *parent = 0);
    ~Return();

private slots:
    void on_ReturnButton_clicked();

    void on_Return_ID_textChanged(const QString &arg1);

private:
    Ui::Return *ui;
};

#endif // RETURN_H
