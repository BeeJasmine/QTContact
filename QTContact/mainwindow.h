#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


private:
    Ui::MainWindow *ui;
    ContactMap * pMap;

    void initToolBar();
};
#endif // MAINWINDOW_H
