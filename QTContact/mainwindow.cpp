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

    connect( ui->chkPrivate, &QCheckBox::clicked,
             [this]() { slotCkeckBoxOfListContact();});
    connect( ui->chkProfessional, &QCheckBox::clicked,
             [this]() { slotCkeckBoxOfListContact();});

    // fill toolbar
    initToolBar();

    // fill the listWidget with all contacts
    fillListContact();
}

/*
void MainWindow::open_dialog()
{
    QDialog *dialogue = new QDialog(this);
    dialogue->setModal(true);
    QPalette pal = dialogue->palette();
    pal.setColor(dialogue->backgroundRole(),Qt::white);
    dialogue->setPalette(pal);

      QLabel *title = new QLabel("Informations relatives au contact");
      QLabel *nameLabel = new QLabel("Nom:");
      QLineEdit *nameLineEdit = new QLineEdit;
      QLabel *prenomLabel = new QLabel("Prénom:");
      QLineEdit *prenomLineEdit = new QLineEdit;
      QLabel *birthLabel = new QLabel("Date de naissance :");
      QLineEdit *birthLineEdit = new QLineEdit;
      QLabel *cpnyLabel = new QLabel("Entreprise :");
      QLineEdit *cpnyLineEdit = new QLineEdit;

      QPushButton *btnSave = new QPushButton("Ajouter");
      QPushButton *btnQuit = new QPushButton("Fermer");

      QGridLayout *layout = new QGridLayout;
      layout->addWidget(title,0, 0);
      layout->addWidget(nameLabel, 2, 0);
      layout->addWidget(nameLineEdit, 2, 2,1,3);
      layout->addWidget(prenomLabel, 3, 0);
      layout->addWidget(prenomLineEdit, 3,2, 1,3);
      layout->addWidget(birthLabel, 4, 0);
      layout->addWidget(birthLineEdit, 4, 2);

      layout->addWidget(cpnyLabel, 5, 0);
      layout->addWidget(cpnyLineEdit, 5, 2);

      //layout->addWidget(Label, 4, 0);
      //^layout->addWidget(LineEdit, 4, 2);

      layout->addWidget(btnSave, 8, 3);
      layout->addWidget(btnQuit, 8, 4);

      dialogue->setLayout(layout);
      dialogue->show();

      //QObject::connect(btnSave, SIGNAL(clicked()), dialogue, SLOT());
      QObject::connect(btnQuit, SIGNAL(clicked()), dialogue, SLOT(close()));

}
*/

void MainWindow::initToolBar()
{
    QToolBar * toolbar = ui->toolBar;

    QLabel* label = new QLabel("Recherche :"); //, this);
    inputSearch = new QLineEdit(); // this
    inputSearch->setMinimumWidth(150);
    //lineEd->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Preferred);
    inputSearch->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    toolbar->addWidget(label);
    toolbar->addWidget(inputSearch);
    toolbar->addSeparator();

    //QAction *qActionAdd = toolbar->addAction(QIcon(":/images/ress/image/plus.png"),"Nouveau contact");
    //QPushButton *btn = new QPushButton( QIcon(":/images/ress/image/plus.png"),"");
    //toolbar->addWidget(btn);
    //toolBar->setFixedHeight( 25 ); // ok works, not seem easy for nice design

    QAction *dialogAdd = toolbar->addAction("Nouveau contact");
    toolbar->addAction(dialogAdd);
    dialogAdd->setShortcut(QKeySequence("Ctrl+A"));
    dialogAdd->setIcon(QIcon(":/images/ress/image/plus.png"));
    //QObject::connect(dialogAdd, SIGNAL(triggered()), this, SLOT(open_dialog()));
    QObject::connect( dialogAdd, SIGNAL(triggered()),
                      this, SLOT(on_action_Ajouter_contact_triggered()));


    // connectionon_action_Ajouter_contact_triggered
    connect( inputSearch, &QLineEdit::textChanged,
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

        if( IamFriend && ui->chkPrivate->isChecked() )
            // may factorize, addItemToListContact( private/pro )
            ui->listContact->addItem(
                    new QListWidgetItem( QIcon(":/images/ress/image/homersimpson.png"),
                                QString("%1, %2").arg(ptContact->getLastName())
                                                 .arg(ptContact->getFirstName())));

        if( IamPro && ui->chkProfessional->isChecked() )
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

void MainWindow::slotCkeckBoxOfListContact()
{
    qDebug() << "Check box ";
    // check if restricted by the search field in toolbar
    if( ! inputSearch->text().isEmpty() )
        fillListContact ( pMap->getFilterName( inputSearch->text() ) );
    // default, just refresh with all
    else
        fillListContact();
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




/* POUR AJOUTER UNE ENTREE

void MainWindow::on_btnAdd_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../dbContacts.db");
    bool ok = db.open();

    //qDebug() << ok;

    if (ok)
    {
        QString req = "insert into contacts(firstname, lastname) VALUES(:pPren, :pNom)";

        QString nom = ui->lineEdit->text();
        QString pren = ui->txtpren->text();

        QSqlQuery query(db);
        query.prepare(req);

        query.bindValue(":pNom", nom);
        query.bindValue(":pPren", pren);

        bool reqOk = query.exec();
        qDebug() << reqOk;

        if (reqOk)
        {
            int nbInserted = query.numRowsAffected();
            qDebug() << "Nb Insert : " << nbInserted;
        }

        db.close();
    }
}


MODALE OU NON MODALE ???


void MainWindow::on_pushButton_clicked()
{
    DialogFermer dialogModal;

    dialogModal.exec();

}

void MainWindow::on_pushButton_2_clicked()
{

    //DialogFermer dialogModal;

    //dialogModal.show();

    dialogNonModal = new DialogFermer(this);
    ui->label->setText(dialogNonModal->getMessage());


    dialogNonModal->show();

    dialogNonModal->changerCouleur("blue");

    QLabel* lbl = dialogNonModal->getLabel();

    lbl->setText("Coucou");
    lbl->setStyleSheet("color:red;");
}

*/

void MainWindow::on_action_Ajouter_contact_triggered()
{
    DialogAdd myDialog;

    myDialog.exec();

}
