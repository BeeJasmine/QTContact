#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMainWindow>
#include "contactmap.h"
#include "dialogadd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void fillListContact();
    void fillListContact( QVector<Contact*> contacttoPrint );

    ~MainWindow();

private slots:
    void on_actionQuitter_triggered();
    void slotCkeckBoxOfListContact();
    void selectedContact( QListWidgetItem *item);
    void updateDetailsContact( Contact * contact );

    void on_action_Ajouter_contact_triggered();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    ContactMap * pMap;
    QLineEdit* inputSearch; // search name filed in toolbar

    void initToolBar();
    void loadUserSettings();
    DialogAdd *dialogAdd;


};
#endif // MAINWINDOW_H
