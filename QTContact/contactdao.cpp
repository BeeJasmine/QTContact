#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSettings>

#include "contactdao.h"
#include "privatecontact.h"
#include "professionalcontact.h"

const QString DB = "QSQLITE";

ContactDAO::ContactDAO()
    : connexionDB( new QSqlDatabase(  QSqlDatabase::addDatabase( DB )))
{

    qInfo() << "Construction DAO singleton";
    QSettings myConfig(QSettings::IniFormat, QSettings::UserScope,
                       // organization name , project name
                       "AJC_ProjectQt", "QTContact");
    QString filePathDB  = myConfig.value("db/filepath").toString();
    qInfo() << "Will open the database: " << filePathDB;
    connexionDB->setDatabaseName( filePathDB );

    connexionDB->open();
    if ( connexionDB->isOpenError() ) {
        qWarning() << "Error opening database :";
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


void ContactDAO::insertPrivateContact(PrivateContact *contact) //prendre Contact* en entree!!!
{
    QString req = "insert into contacts(prenom, nom, rue, Complement, cp, Ville, dtNaissance) "
                  "VALUES(:pPren, :pNom, :pRue, :pComplement, :pCp, :pVille, :pdtNaissance);";
        QSqlQuery query;

        query.prepare(req);
        query.bindValue(":pNom", contact->getLastName());
        query.bindValue(":pPren", contact->getFirstName());
        query.bindValue(":pRue", contact->getLabelAdress());
        query.bindValue(":pComplement", contact->getComplementAdress());
        query.bindValue(":pCp", contact->getPostalCode());
        query.bindValue(":pVille", contact->getCity());
        query.bindValue(":pdtNaissance", contact->getBirthDate());

        bool reqOk = query.exec(); // reussite ?
        qDebug() << "Insertion ok:"<< reqOk;

        if (reqOk)
        {
            int nbInserted = query.numRowsAffected();
            qDebug() << "Nb Insertions : " << nbInserted;
        }

        else
        {
            qDebug()<< QString("Bad Query, It's inactive: %1").arg(query.lastError().text());
        }
}

void ContactDAO::insertProfessionalContact(ProfessionalContact *contact)
{
    QString req = "insert into contacts(prenom, nom, rue, Complement, cp, Ville, mail, entreprise)"
                  "VALUES(:pPren, :pNom, :pRue, :pComplement, :pCp, :pVille, :pEmail, :pEntreprise)";
        QSqlQuery query;

        query.prepare(req);
        query.bindValue(":pNom", contact->getLastName());
        query.bindValue(":pPren", contact->getFirstName());
        query.bindValue(":pRue", contact->getLabelAdress());
        query.bindValue(":pComplement", contact->getComplementAdress());
        query.bindValue(":pCp", contact->getPostalCode());
        query.bindValue(":pVille", contact->getCity());
        query.bindValue(":pEmail", contact->getEmailAdress());
        query.bindValue(":pEntreprise", contact->getCompanyName());

        bool reqOk = query.exec(); // reussite ?
        if (reqOk)
        {
            int nbInserted = query.numRowsAffected();
            qDebug() << "Nb Insertions : " << nbInserted;
        }
        else
        {
            qDebug()<< QString("Bad Query, It's inactive: %1").arg(query.lastError().text());
        }
}

void ContactDAO::fillCommonDataFromQuery(Contact *contact, QSqlQuery &query) const
{
    contact->setIdContact( query.value("idContact").toInt() );
    contact->setLastName( query.value("Nom").toString() );
    contact->setFirstName( query.value("Prenom").toString() );
    contact->setGender( query.value("Sexe").toString() );
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


