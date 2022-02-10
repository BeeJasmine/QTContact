#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include "contactmap.h"

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

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    ContactMap * pMap;

    void initToolBar();
};
#endif // MAINWINDOW_H
