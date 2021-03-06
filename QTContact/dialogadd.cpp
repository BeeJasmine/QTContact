#include "dialogadd.h"
#include "ui_dialogadd.h"

#include <QButtonGroup>
#include <QDebug>
#include <QSqlQuery>

#include "contactdao.h"
#include "privatecontact.h"
#include "professionalcontact.h"


DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdd)
{
    ui->setupUi(this);
    QButtonGroup* btnGrp = new QButtonGroup(this);
    btnGrp->addButton( ui->radioBtn_Perso, 0); // to avoid strange numbering (why negative?)
    btnGrp->addButton( ui->radioBtn_Pro, 1);

    connect(ui->radioBtn_Perso, SIGNAL(toggled(bool)), this, SLOT(refreshRadioBtn(bool)));
    ui->radioBtn_Perso->setChecked(true);
}

void DialogAdd::refreshRadioBtn(bool)
{
    ui->lbl_email->hide();
    ui->lineEdit_email->setVisible(false);
    ui->lbl_company->hide();
    ui->lineEdit_company->setVisible(false);
    ui->lbl_birthdate->setVisible(false);
    ui->lineEdit_birth->setVisible(false);

    if (ui->radioBtn_Perso->isChecked())
    {
        qDebug()<< "check is perso";
        ui->lbl_birthdate->setVisible(true);
        ui->lineEdit_birth->setVisible(true);
       }
    else
    {
        qDebug()<< "check is pro";
        ui->lineEdit_email->show();
        ui->lbl_email->setVisible(true);
        ui->lbl_company->show();
        ui->lineEdit_company->setVisible(true);
    }
}

DialogAdd::~DialogAdd()
{
    delete ui;
}

void DialogAdd::on_buttonBox_accepted()
{
    QString firstname;
    if((ui->lineEdit_firstname->text()).size()<30 && (ui->lineEdit_firstname->text())!=nullptr)
    {
        firstname=(ui->lineEdit_firstname->text()).toLower(); //la première lettre en capitale ??
    }

    QString lastname;
    if((ui->lineEdit_name->text()).size()<30 && (ui->lineEdit_name->text())!=nullptr)
    {
        lastname = (ui->lineEdit_name->text()).toUpper(); // tout en capitale comme dans la db
    }


    QString gender; // en fonction du radio button Genre ??? un deuxième groupe de radio bouton.... oubien des checkboxs

    QString street;
    if((ui->lineEdit_street->text())!=nullptr)
    {
        street = (ui->lineEdit_street->text()).toLower(); // pas de règle dans la db
    }

    QString complement;
    if((ui->lineEdit_complement->text())!=nullptr)
    {
        street = (ui->lineEdit_complement->text()).toLower(); // pas de règle dans la db
    }

    QString postalCode; //^[0-9]{5}$
    if((ui->lineEdit_name->text()).size()==5 &&(ui->lineEdit_cp->text())!=nullptr)
    {
        postalCode = (ui->lineEdit_cp->text()); // pas de règle dans la db
    }

     QString city;
     if((ui->lineEdit_city->text())!=nullptr)
     {
         city = (ui->lineEdit_city->text()); // pas de règle dans la db
     }

     QString email; //^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$
     if((ui->lineEdit_email->text())!=nullptr)
     {

         QRegExp regExp("^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$");

        if (regExp.exactMatch(ui->lineEdit_email->text()) ==true)
        {
            email = (ui->lineEdit_email->text());
        }

        else
        {
            ui->lbl_email->setText("Email \n Veuillez entrer une adresse format nom@mail.com ");
        }
     }

     QString stringDate;
     QDate birthdate;
     if((ui->lineEdit_birth->text())!=nullptr)
     {
         stringDate = (ui->lineEdit_birth->text()); // pas de règle dans la db
         birthdate.fromString(stringDate,"YYYY-MM-dd");
     }

     QString companyName;
     if((ui->lineEdit_company->text())!=nullptr)
     {
         email = (ui->lineEdit_company->text()); // pas de règle dans la db
     }

    //instance d'un contact contact pro, remplir avec les setter

    if (ui->radioBtn_Pro->isChecked())
        {
            ProfessionalContact* contactPro = new ProfessionalContact;
            contactPro->setFirstName(firstname);
            contactPro->setLastName(lastname);
            contactPro->setLabelAdress(street);
            contactPro->setComplementAdress(complement);
            contactPro->setPostalCode(postalCode);
            contactPro->setCity(city);
            contactPro->setEmailAdress(email);
            contactPro->setCompanyName(companyName);
            ContactDAO::instance().insertProfessionalContact(contactPro);
        }

    else
        {
            PrivateContact* contactPerso= new PrivateContact;
            contactPerso->setFirstName(firstname);
            contactPerso->setLastName(lastname);
            contactPerso->setLabelAdress(street);
            contactPerso->setComplementAdress(complement);
            contactPerso->setPostalCode(postalCode);
            contactPerso->setCity(city);
            contactPerso->setBirthDate(birthdate);
            qDebug() << "birthday " << contactPerso->getBirthDate();
            ContactDAO::instance().insertPrivateContact(contactPerso);
        }
}
