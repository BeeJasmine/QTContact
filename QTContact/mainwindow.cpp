#include <QDebug>


#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "contactmap.h"
#include "professionalcontact.h"
#include "privatecontact.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//, pMap( new ContactMap() )
{
    ui->setupUi(this);
    qDebug() << "Const Main";
    pMap = new ContactMap();

    // default checkButtons activated
    ui->chkPrivate->setChecked( true );
    ui->chkProfessional->setChecked(true);

    // fill toolbar
    initToolBar();

    // fill the listWidget
    // ui->listWidget->addItem( newContact->getNumero() );
    fillListContact();

    // connection
}

void MainWindow::initToolBar()
{
    QToolBar * toolbar = ui->toolBar;

    QLabel* label = new QLabel("Recherche :"); //, this);
    QLineEdit* lineEd = new QLineEdit(); // this
    lineEd->setMinimumWidth(150);
    //lineEd->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Preferred);
    lineEd->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    toolbar->addWidget(label);
    toolbar->addWidget(lineEd);
    toolbar->addSeparator();

    QAction *qActionAdd = toolbar->addAction(QIcon(":/images/ress/image/plus.png"),"Nouveau contact");
    //QPushButton *btn = new QPushButton( QIcon(":/images/ress/image/plus.png"),"");
    //toolbar->addWidget(btn);
    //toolBar->setFixedHeight( 25 ); // ok works, not seem easy for nice design

    // connection
    connect( lineEd, &QLineEdit::textChanged,
             [this](const QString & text) {
                qDebug() << "text changed" << text;
                fillListContact ( pMap->getFilterName(text) );
            });
}

void MainWindow::fillListContact()
{
    fillListContact( pMap->getAllContact() );
}

void MainWindow::fillListContact( QVector<Contact*> contactToPrint )
{
    // clear previous
    ui->listContact->clear();

    bool IamPro, IamFriend;

    for( Contact * ptContact : contactToPrint ) {

        IamPro = false;
        IamFriend = false;

        if ( dynamic_cast<ProfessionalContact *>( ptContact ) != nullptr )  {
            qDebug() << "Je suis un Pro";
            IamPro = true;
        }

        if(  dynamic_cast<PrivateContact *>( ptContact ) != nullptr ) {
            qDebug() << "Je suis un ami";
            IamFriend = true;
        }

        if( IamFriend && ui->chkProfessional->isChecked() )
            ui->listContact->addItem(
                    new QListWidgetItem( QIcon(":/images/ress/image/homersimpson.png"),
                                QString("%1, %2").arg(ptContact->getLastName())
                                                 .arg(ptContact->getFirstName())));

        if( IamPro && ui->chkPrivate->isChecked() )
            ui->listContact->addItem(
                        new QListWidgetItem( QIcon(":/images/ress/image/boss.png"),
                                    QString("%1, %2").arg(ptContact->getLastName())
                                                     .arg(ptContact->getFirstName())));
    } //end for loop contact
}

MainWindow::~MainWindow()
{
    delete ui;
}
