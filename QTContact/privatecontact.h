#ifndef PRIVATECONTACT_H
#define PRIVATECONTACT_H

#include "contact.h"
#include <QDate>
#include <QObject>

class PrivateContact : public Contact
{
public:
    PrivateContact();
    ~PrivateContact();


    void affiche(QString="") override;


    QDate getBirthDate() const;
    void setBirthDate(const QDate &value);

private:

    QDate birthDate;

};

#endif // PRIVATECONTACT_H
