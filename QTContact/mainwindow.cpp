#include <QDebug>

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
    ui->chkPrivate->setChecked( false );
    ui->chkProfessional->setChecked(true);

    // fill the listWidget
    // ui->listWidget->addItem( newContact->getNumero() );
    fillListContact();
}

void MainWindow::fillListContact()
{
    // clear previous ?
    ui->listContact->clear();

    bool need_cast = true;
    if( ui->chkPrivate->isChecked() && ui->chkProfessional->isChecked() )
        need_cast = false;

    bool IamPro, IamFriend;

    QVector<Contact *> vecToPrint;

    //auto filterPrivate =
    //for( auto ptContact : pMap->getAllContact() ) {
    for( Contact * ptContact : pMap->getAllContact() ) {

        qDebug() << " new contact need_cast " << need_cast;
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
            ui->listContact->addItem( QString("%1, %2").arg(ptContact->getLastName())
                                                       .arg(ptContact->getFirstName()));

        if( IamPro && ui->chkPrivate->isChecked() )
            ui->listContact->addItem( QString("%1, %2").arg(ptContact->getLastName())
                                                       .arg(ptContact->getFirstName()));
    } //end for loop contact

}

MainWindow::~MainWindow()
{
    delete ui;
}
