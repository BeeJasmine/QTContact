#ifndef CONTACTMAP_H
#define CONTACTMAP_H

#include <QMap>
#include "contact.h"

class ContactMap
{
public:
    ContactMap();
    ~ContactMap();
    // ContactPro getContactPro()

    //template<typename Func>
    QVector<Contact*> getAllContact();

private:
    bool initFromDB();

    QMap<int, Contact*> mapContact;
};

#endif // CONTACTMAP_H
