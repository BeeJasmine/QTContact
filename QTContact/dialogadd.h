#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include "contact.h"



namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = nullptr);
    ~DialogAdd();
    //void insertContact2(Contact * contact);

private slots:
    void on_buttonBox_accepted();
    void refreshRadioBtn(bool);

private:
    Ui::DialogAdd *ui;
};

#endif // DIALOGADD_H
