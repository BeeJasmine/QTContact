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

Contact *ContactMap::loadContactWithName(const QString &lastName, const QString &firstName)
{
    //int contactId = 0;
    //Contact * contact;

    for( auto it = mapContact.begin(); it != mapContact.end(); it++ ) {
        if( ( it.value()->getLastName() == lastName)
         || ( it.value()->getFirstName() == firstName ) ) {
            //contactId = it.key();
            //break;
            return it.value();
        }

    }
    //int contactId = it.key();
    return nullptr;
}

ContactMap::~ContactMap()
{
    //qDeleteAll( mapContact );
}


