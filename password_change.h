#ifndef PASSWORD_CHANGE_H
#define PASSWORD_CHANGE_H

#include <QDialog>

namespace Ui {
class Password_Change;
}

class Password_Change : public QDialog
{
    Q_OBJECT

public:
    explicit Password_Change(QWidget *parent = 0);
    ~Password_Change();

private slots:
    bool on_pushButton_clicked();
    
private:
    Ui::Password_Change *ui;
};

#endif // PASSWORD_CHANGE_H
