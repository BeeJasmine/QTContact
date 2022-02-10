#include "privatecontact.h"
#include <QString>

PrivateContact::PrivateContact()
    :Contact()
{

}

PrivateContact::~PrivateContact()
{

}

void PrivateContact::affiche(QString)
{

}

QDate PrivateContact::getBirthDate() const
{
    return birthDate;
}

void PrivateContact::setBirthDate(const QDate &value)
{
    birthDate = value;
}
