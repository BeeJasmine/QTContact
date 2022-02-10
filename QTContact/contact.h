#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QChar>

class Contact
{
public:
    Contact();
    virtual ~Contact();

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QChar getGender() const;
    void setGender(QChar value);

    // Adress
    QString getPostalCode() const;
    void setPostalCode(const QString &value);

    QString getCity() const;
    void setCity(const QString &value);

    QString getLabelAdress() const;
    void setLabelAdress(const QString &value);

    QString getComplementAdress() const;
    void setComplementAdress(const QString &value);

    virtual void affiche(QString="");

    int getIdContact() const;
    void setIdContact(int value);

protected:
    int IdContact;
    QString lastName;
    QString firstName;
    QChar gender;
    QString postalCode;
    QString city;
    QString labelAdress;
    QString complementAdress;
};

#endif // CONTACT_H
