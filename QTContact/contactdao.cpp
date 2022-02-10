#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QDebug>

#include "contactdao.h"
#include "privatecontact.h"
#include "professionalcontact.h"


const QString DATABASE_FILENAME = "../dbContacts.db";
const QString DB = "QSQLITE";


ContactDAO::ContactDAO()
    : connexionDB( new QSqlDatabase(  QSqlDatabase::addDatabase( DB )))
{
    connexionDB->setDatabaseName( DATABASE_FILENAME );
    connexionDB->open();
    if ( connexionDB->isOpenError() ) {
        qInfo() << "Error opening database :";
        connexionDB->lastError().text();
    }
}

ContactDAO& ContactDAO::instance()
{
    static ContactDAO singleton; // execute une seule fois
    return singleton;
}

QVector<Contact *> ContactDAO::getAllContacts() const
{
    QSqlQuery query("SELECT * FROM contacts");

    bool resQuery = query.exec();
    if( ! resQuery ) {
        qDebug() << "LA BD est cassée !!! ContactDao.cpp l38";
    }

    // to check as concrete type of contact
    QVector<Contact *> vecContact;
    while( query.next() ) {
        // Professional Contact
        if( ! query.value("Entreprise").isNull() ) {
            ProfessionalContact* profContact = new ProfessionalContact();
            profContact->setCompanyName( query.value("Entreprise").toString() );
            profContact->setEmailAdress( query.value("mail").toString() );

            fillCommonDataFromQuery( profContact, query );
            vecContact.push_back( profContact );

        // Copains
        } else {
            PrivateContact* privContact = new PrivateContact();
            privContact->setBirthDate( query.value("dtNaissance").toDate() );

            fillCommonDataFromQuery( privContact, query );
            vecContact.push_back( privContact );
       }
    }
    return vecContact;
}

void ContactDAO::fillCommonDataFromQuery(Contact *contact, QSqlQuery &query) const
{
    contact->setIdContact( query.value("idContact").toInt() );
    contact->setLastName( query.value("Nom").toString() );
    contact->setFirstName( query.value("Prenom").toString() );
    contact->setGender( query.value("Sexe").toChar() );
    contact->setLabelAdress(  query.value("rue").toString() );
    contact->setComplementAdress(  query.value("Complement").toString() );
    contact->setCity( query.value("Ville").toString() );
    contact->setPostalCode( query.value("cp").toString() );
}


ContactDAO::~ContactDAO()
{
    if( connexionDB->isOpen() ) {
        qDebug() << "Destructor ContactDAO";
        connexionDB->close();
    }
    delete connexionDB;
}


