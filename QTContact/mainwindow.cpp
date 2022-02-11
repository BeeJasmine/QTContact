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

#include "contactdao.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fieldDetailContact->setReadOnly(true);

    // load user settings
    loadUserSettings();

    //this->setStyleSheet( )
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
    connect( ui->listContact, &QListWidget::itemDoubleClicked,
             this, &MainWindow::selectedContact);
}

// data relative to the database are used in CustomerDAO
void MainWindow::loadUserSettings() {

    // read configuration: /home/michael/.config/AJC_ProjectQt/QTContact.ini
    // Native or IniFormat equivalent on unix, user scope should be in personal directory
    QSettings myConfig(QSettings::IniFormat, QSettings::UserScope,
                       // organization name , project name
                       "AJC_ProjectQt", "QTContact");
    qDebug() << "User Settings user file located at :" << myConfig.fileName();

    QString pathQSS =":/css/ress/qss/";
    QFile fileINI( myConfig.fileName() );
    if( fileINI.exists() ) {
        qDebug() << "fileINI exists";
        pathQSS += myConfig.value("preference/css").toString();

    } else {
        qDebug() << "fileINI does not exists, you should add the path to the databse manually...sorry !!";
        // set default value, it will create the file ?
        myConfig.setValue("db/filepath","/home/your-name/.../dbContacts.db");
        myConfig.setValue("preference/css", "jour.qss");
        pathQSS += "jour.qss";
    }

    QFile fileQSS( pathQSS );
    bool openOK = fileQSS.open(QIODevice::ReadOnly);
    if(openOK) {
        this->setStyleSheet(fileQSS.readAll());
        fileQSS.close();
    }
}

void MainWindow::initToolBar()
{
    QToolBar * toolbar = ui->toolBar;

    QLabel* label = new QLabel("Recherche :");
    inputSearch = new QLineEdit();
    inputSearch->setMinimumWidth(150);
    inputSearch->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    toolbar->addWidget(label);
    toolbar->addWidget(inputSearch);
    toolbar->addSeparator();

    QAction *dialogAdd = toolbar->addAction("Nouveau contact");
    toolbar->addAction(dialogAdd);
    dialogAdd->setShortcut(QKeySequence("Ctrl+A"));
    dialogAdd->setIcon(QIcon(":/images/ress/image/plus.png"));

    QObject::connect( dialogAdd, SIGNAL(triggered()),
                      this, SLOT(on_action_Ajouter_contact_triggered()));

    // connect search as soon text is modified
    connect( inputSearch, &QLineEdit::textChanged,
             [this](const QString & text) {
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

void MainWindow::selectedContact( QListWidgetItem *item)
{
    QStringList lastAndfirstName = item->text().split(",");
    Contact * contact = pMap->loadContactWithName( lastAndfirstName.at(0).trimmed(), lastAndfirstName.at(1).trimmed());
    updateDetailsContact( contact );
}

void MainWindow::updateDetailsContact( Contact * contact )
{
    QPlainTextEdit* details = ui->fieldDetailContact;
    //details->clear(); done by doc->setTextPlain() ?
    QTextDocument* doc = details->document();
    doc->setPlainText( contact->affiche() );
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

void MainWindow::on_action_Ajouter_contact_triggered()
{
    DialogAdd myDialog;
    myDialog.exec();
    pMap->initFromDB();
    fillListContact();
}
