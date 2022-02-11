#ifndef CONTACTMAP_H
#define CONTACTMAP_H

#include <QMap>
#include "contact.h"

class ContactMap
{
public:
    ContactMap();
    ~ContactMap();

    QVector<Contact*> getAllContact();
    /** accept for any occurence of the substring text in firstName or LastName **/
    QVector<Contact*> getFilterName(const QString & text);
    /** search exact match, otherwise nullptr **/
    Contact* loadContactWithName( const QString& lastName,
                                  const QString& firstName );

    bool initFromDB();
private:

    QMap<int, Contact*> mapContact;
};

#endif // CONTACTMAP_H
