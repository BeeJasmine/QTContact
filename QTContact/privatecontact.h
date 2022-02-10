#ifndef PRIVATECONTACT_H
#define PRIVATECONTACT_H

#include "contact.h"
#include <QDate>
#include <QObject>

class PrivateContact : public Contact
{
public:
    PrivateContact(QString, QDate);
    ~PrivateContact();

    void affiche(QString="") override;

    private:

    QDate birthDate;



};

#endif // PRIVATECONTACT_H
