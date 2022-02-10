#include "contact.h"

Contact::Contact()
{}

Contact::~Contact()
{

}

QString Contact::getLastName() const
{
    return lastName;
}

void Contact::setLastName(const QString &value)
{
    lastName = value;
}

QString Contact::getFirstName() const
{
    return firstName;
}

void Contact::setFirstName(const QString &value)
{
    firstName = value;
}

QChar Contact::getGender() const
{
    return gender;
}

void Contact::setGender(QChar value)
{
    gender = value;
}

QString Contact::getCity() const
{
    return city;
}

void Contact::setCity(const QString &value)
{
    city = value;
}

QString Contact::getLabelAdress() const
{
    return labelAdress;
}

void Contact::setLabelAdress(const QString &value)
{
    labelAdress = value;
}

QString Contact::getComplementAdress() const
{
    return complementAdress;
}

void Contact::setComplementAdress(const QString &value)
{
    complementAdress = value;
}

void Contact::affiche(QString)
{

}

int Contact::getIdContact() const
{
    return IdContact;
}

void Contact::setIdContact(int value)
{
    IdContact = value;
}

QString Contact::getPostalCode() const
{
    return postalCode;
}

void Contact::setPostalCode(const QString &value)
{
    postalCode = value;
}
