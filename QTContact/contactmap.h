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

    /** accept for any occurence of the substring text in firstName or LastName **/
    QVector<Contact*> getFilterName(const QString & text);

    Contact* loadContactWithName( const QString& lastName,
                                  const QString& firstName );

private:
    bool initFromDB();

    QMap<int, Contact*> mapContact;
};

#endif // CONTACTMAP_H
