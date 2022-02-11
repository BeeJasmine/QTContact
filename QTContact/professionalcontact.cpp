#include <sstream>

#include "professionalcontact.h"
#include <QDebug>

ProfessionalContact::ProfessionalContact()
    :Contact()
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

QString ProfessionalContact::affiche(QString)
{
    QString str = Contact::affiche();
    str.append( "\n\n--- details relation ---\n");
    str.append( "nom de la société: " + getCompanyName() + "\n");
    str.append( "email: " + getEmailAdress() + "\n");

    return str;
}
