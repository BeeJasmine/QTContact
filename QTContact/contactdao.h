#ifndef CONTACTDAO_H
#define CONTACTDAO_H

#include "contact.h"

// forward declaration
class QSqlDatabase;
class QSqlQuery;

/**
 * @brief The ContactDAO class
 * Only 1 DAO, made as singleton with a "static" connection to the DB
 *
 * Usage , from anywhere :
 *  ContactDAO::instance().getAllContacts()
 */
class ContactDAO
{
public:

    static ContactDAO& instance();
    ~ContactDAO();

    /** Requetes  **/
    QVector<Contact*> getAllContacts() const;

    void insertContact(Contact * contact);

private:
    ContactDAO();
    void fillCommonDataFromQuery( Contact * contact, QSqlQuery& query ) const;

    QSqlDatabase* connexionDB;
};

#endif // CONTACTDAO_H
