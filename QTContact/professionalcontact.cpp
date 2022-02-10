#include "professionalcontact.h"
#include <QDebug>

ProfessionalContact::ProfessionalContact(QString name, QString companyName, QString emailAdress)
    :Contact(name)
{
    this->setCompanyName(companyName);
    this->setEmailAdress(emailAdress);

}

ProfessionalContact::~ProfessionalContact()
{
    //qDebug<<"Dtor Professional";
}

QString ProfessionalContact::getCompanyName() const
{
    return companyName;
}

void ProfessionalContact::setCompanyName(const QString &value)
{
    companyName = value;
}

QString ProfessionalContact::getEmailAdress() const
{
    return emailAdress;
}

void ProfessionalContact::setEmailAdress(const QString &value)
{
    emailAdress = value;
}

void ProfessionalContact::affiche(QString)
{

}
