#ifndef PROFESSIONALCONTACT_H
#define PROFESSIONALCONTACT_H

#include "contact.h"
#include <QObject>

class ProfessionalContact : public Contact
{
public:
    ProfessionalContact();
    ~ProfessionalContact();

    QString getCompanyName() const;
    void setCompanyName(const QString &value);

    QString getEmailAdress() const;
    void setEmailAdress(const QString &value);

    QString affiche(QString="") override;

private:
    QString companyName;
    QString emailAdress;

};

#endif // PROFESSIONALCONTACT_H
