#include "privatecontact.h"
#include <QString>

PrivateContact::PrivateContact()
    :Contact()
{

}

PrivateContact::~PrivateContact()
{

}

QString PrivateContact::affiche(QString)
{
    QString str = Contact::affiche();
    str.append( "\n\n--- à ne pas oublier ---\n");
    str.append( getBirthDate().toString() + "\n");
    return str;
}

QDate PrivateContact::getBirthDate() const
{
    return birthDate;
}

void PrivateContact::setBirthDate(const QDate &value)
{
    birthDate = value;
}
