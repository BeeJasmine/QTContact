#include <QDebug>
#include "contactmap.h"
#include "contactdao.h"

ContactMap::ContactMap()
{
    qDebug() << "contr. ContactMap ";
    /*bool ret =*/
    initFromDB();
    qDebug() << "Size of mapContact " << mapContact.size();
}

bool ContactMap::initFromDB()
{
    QVector<Contact*> allContacts = ContactDAO::instance().getAllContacts();

    qDebug() << " Init  size from DB " << allContacts.size();

    // remplir la map
    // QMap::iterator	insert(const Key &key, const T &value)
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

ContactMap::~ContactMap()
{
    //qDeleteAll( mapContact );
}


