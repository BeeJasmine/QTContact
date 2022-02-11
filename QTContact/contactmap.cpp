#include <QDebug>
#include "contactmap.h"
#include "contactdao.h"

ContactMap::ContactMap()
{
    initFromDB();
}

bool ContactMap::initFromDB()
{
    // C'est pas beau, on avait oublié de rajouter le nouveau contact dans la map...
    // moyen le plus rapide de tout recharger
    if( ! mapContact.isEmpty() ) {
        qDeleteAll( mapContact );
        mapContact.clear();
    }

    QVector<Contact*> allContacts = ContactDAO::instance().getAllContacts();
    // remplir la map
    for( auto contact : allContacts)
        mapContact.insert( contact->getIdContact(), contact );

    return true;
}

QVector<Contact *> ContactMap::getAllContact()
{
    QVector<Contact *> vectorReturn;
    for(auto contact : mapContact ) {
        vectorReturn.push_back( contact ); //
    }
    return vectorReturn;
}

QVector<Contact *> ContactMap::getFilterName(const QString &text)
{

    QVector<Contact *> vectorReturn;
    for(auto contact : mapContact ) {

        if ( ( contact->getLastName().contains(text, Qt::CaseInsensitive)
         ||  (contact->getFirstName().contains(text, Qt::CaseInsensitive)))
             )
        vectorReturn.push_back( contact );
    }
    return vectorReturn;
}

Contact *ContactMap::loadContactWithName(const QString &lastName, const QString &firstName)
{
    for( auto it = mapContact.begin(); it != mapContact.end(); it++ ) {
        if( ( it.value()->getLastName() == lastName)
         || ( it.value()->getFirstName() == firstName ) ) {
            return it.value();
        }
    }
    return nullptr;
}

ContactMap::~ContactMap()
{
    qDeleteAll( mapContact );
    mapContact.clear();
}


