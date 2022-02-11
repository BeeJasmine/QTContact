# QTContact

TODO:

Formulaire ajout :
- 1 lineEdit / champs 
- nommage efficient des lineEdit
- récupérer text des lineEdits
- ajouter les valeurs des lineEdits dans la base de données (se servir de ContactDAO)
- création radioButton pro/perso
- affichage des champs à remplir par l'utilisateur selon radioButton
- vérifier le format de email (ReGex)
- vérifier le format de birthdate (ReGex) 
- récupérer les infos du formulaire final : compléter fonction d'ajout avec tous les champs

########################################################################

- ajouter les signals aux checkboxs PRIO
- double-click sur une ligne de la listWidget -> affichage des détails 
- ajouter fonctionnalité de suppression d'un contact
- colorer les lignes pro/perso de la liste (optionnel)
- rendre la classe Contact Abstraite
- exporter la db avec commande sqlite3 .excel (? chercher la possibilité)



CLOSED :
- UML des classes nécessaire d'après la table Contact
- Maquette graphique
- Schéma fonctionnel de l'application
- Créer Classe mère Contact
- créer classe enfants ProfessionalContact PrivateContact
- Créer MapContacts de contacts (pro et particulier)
- Remplissage listWidget avec MapContacts 
- lister les contacts Pro/perso
- ajouter icone spécifique pro/perso
- fonctionnalité quitter
- ajouter toolbar
- ajouter l'icône + à la toolbar
- fonctionnalité rechercher toolbar﻿
- formulaire dans QDialog créé avec le designer
- QDialog codé pouvant s'ouvrir depuis la toolbar
- Qdialog avec designer connecté à la ToolBar
