#include <QDebug>


#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "contactmap.h"
#include "professionalcontact.h"
#include "privatecontact.h"

// just to set the filepath
#include "contactdao.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//, pMap( new ContactMap() )
{
    ui->setupUi(this);

    // read configuration: /home/michael/.config/AJC_ProjectQt/QTContact.ini
    // Native or IniFormat equivalent on unix, user scope should be in personal directory
    QSettings myConfig(QSettings::IniFormat, QSettings::UserScope,
                       // organization name , project name
                       "AJC_ProjectQt", "QTContact");
    qDebug() << "Const Main Qsetting name :" << myConfig.fileName();
    // DB filepath retrieved from CustomerDAO
    // to use for preference
    // exemple
    //myConfig.setValue("infos/fichier","txtext.txt");

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

    //qActionAdd->triggered()



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
            //qDebug() << "Je suis un Pro";
            IamPro = true;
        }

        if(  dynamic_cast<PrivateContact *>( ptContact ) != nullptr ) {
            //qDebug() << "Je suis un ami";
            IamFriend = true;
        }

        // qDebug()<<"Je suis la valeur de IamFriend"<<IamFriend; //TRUE (peut-être car la dernière valeur de la map est un ami ??)
        if( IamFriend && ui->chkProfessional->isChecked() )
            // may factorize, addItemToListContact( private/pro )
            ui->listContact->addItem(
                    new QListWidgetItem( QIcon(":/images/ress/image/homersimpson.png"),
                                QString("%1, %2").arg(ptContact->getLastName())
                                                 .arg(ptContact->getFirstName())));
        // qDebug()<<"Je suis la valeur de IamPro"<<IamPro; //FALSE (peut-être car la dernière valeur de la map est un ami et non un pro??)
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

void MainWindow::on_actionQuitter_triggered()
{
      this->close();
}

void MainWindow::closeEvent(QCloseEvent * eventClose)
{

    QMessageBox msgBox(this);
    msgBox.setText("Voulez vous Quitter ?");
    msgBox.setInformativeText("Quitter ?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int reponse = msgBox.exec();

    switch(reponse)
    {
        case QMessageBox::Yes:
            eventClose->accept();
            break;
        default:
            eventClose->ignore();
            break;
    }

}
