#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include "employes.h"

Employes::Employes()
{   CIN=0;
    nom=" ";
    prenom="  ";
    genre="   ";
    tel=0;
    email="  ";
    adresse="  ";
    fonction="   ";
    salaire=0;

};
 Employes:: Employes(int CIN,QString nom,QString prenom,QString genre,int tel,QString email, QString adresse,QString fonction,float salaire,QString RFID)
 {
     this->CIN=CIN;
     this->nom=nom;
     this->prenom=prenom;
     this->genre=genre;
     this->tel=tel;
     this->email=email;
     this->adresse=adresse;
     this->fonction=fonction;
     this->salaire=salaire;
     this->RFID=RFID;
 };

//getters---
int  Employes::getcin()
{
    return CIN;
};
QString Employes::getNom()
{
    return nom;
};
QString Employes::getPrenom()
{
    return prenom;
};
QString Employes::getGenre()
{
    return genre;
};
int   Employes::getTel()
{
    return tel;
};
QString Employes::getEmail()
{
    return email;
};
QString Employes::getAdresse()
{
    return adresse;
};
QString Employes::getFonction()
{
    return fonction;
};
float Employes::getSalaire()
{
  return salaire;

};
QString Employes::getRFID()
{
     return RFID;
};

//setters
void Employes::setCin(int CIN)
{
    this->CIN=CIN;
};
void Employes::setNom(QString nom )
{
    this->nom=nom;
};
void Employes::setPrenom(QString prenom)
{
    this->prenom=prenom;
};
void Employes::setGenre(QString genre)
{
    this->genre=genre;
};
void Employes::setTel(int tel)
{
    this->tel=tel;
};
void Employes::setEmail(QString email)
{
    this->email=email;
};
void Employes::setAdresse(QString adresse)
{
    this->adresse=adresse;
};
void Employes::setFonction(QString fonction)
{
    this->fonction=fonction;
};
void Employes::setSalaire(float salaire)
{
    this->salaire=salaire;
};

void Employes::setRFID(QString RFID)
{
    this->RFID=RFID;
};

//-----------partie crud--------------------
bool Employes::rechercheAvantAjout(int CIN)
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE CIN = ?");
        query.addBindValue(CIN);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                qDebug() << "L'employé avec le CIN" << CIN << "existe déjà.";
                return false;
            } else {
                qDebug() << "L'employé avec le CIN" << CIN << "n'existe pas.";
                return true;
            }
        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
            qDebug() << "Oracle Error:" << query.lastError().databaseText();
            return false;
        }
};

bool Employes::ajouter()
{
    if (!rechercheAvantAjout(CIN))
       {
           return false;
       }
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES(CIN,NOM,PRENOM,GENRE,TELEPHONE,EMAIL,ADRESSE,FONCTION,SALAIRE,RFID)"
                  "VALUES (:CIN,:NOM,:PRENOM,:GENRE,:TELEPHONE,:EMAIL,:ADRESSE,:FONCTION,:SALAIRE,:RFID)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":GENRE", genre);
    query.bindValue(":TELEPHONE", tel);
    query.bindValue(":EMAIL", email);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":FONCTION", fonction);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":RFID", RFID);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    return true;
}

bool Employes::rechercher(int CIN)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE CIN = ?");
    query.addBindValue(CIN);

    if (query.exec() && query.next())
    {
        nom = query.value(1).toString();
        prenom = query.value(2).toString();
        genre = query.value(3).toString();
        tel = query.value(4).toInt();
        email = query.value(5).toString();
        adresse = query.value(6).toString();
        fonction = query.value(7).toString();
        salaire = query.value(8).toFloat();
        RFID = query.value(9).toString();
        return true;
    }
    else
    {
        return false;
    }
}


bool Employes::modifier()
{
  QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, GENRE=:GENRE, TELEPHONE=:TELEPHONE, EMAIL=:EMAIL, ADRESSE=:ADRESSE, FONCTION=:FONCTION, SALAIRE=:SALAIRE, RFID=:RFID WHERE CIN = :CIN ");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":GENRE", genre);
    query.bindValue(":TELEPHONE", tel);
    query.bindValue(":EMAIL", email);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":FONCTION", fonction);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":RFID", RFID);
    return query.exec();
};

bool Employes::supprimer(int)
{
  QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES where CIN= :CIN");
    query.bindValue(0, CIN);
    return query.exec();
};

QSqlQueryModel* Employes::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GENRE,TELEPHONE,EMAIL,ADRESSE,FONCTION,SALAIRE,RFID FROM EMPLOYES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));


    return  model;
};

QSqlQueryModel* Employes::triCin()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES order by CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));
    return  model;

};

QSqlQueryModel* Employes::triNom()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));
    return  model;
};

QSqlQueryModel* Employes::triSalary()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES order by SALAIRE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENRE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("FONCTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("RFID"));
    return  model;

};

void Employes::chercherEmpCin(QTableView *table, QString l)
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery *query =new QSqlQuery;
        query->prepare("select * from EMPLOYES where regexp_like(CIN,:CIN)");
        query->bindValue(":CIN",l);
        if(l==0)
        {
            query->prepare("select * from EMPLOYES");
        }
        query->exec();
        model->setQuery(*query);
        table->setModel(model);
        table->show();

};
void Employes::chercherEmpNom(QTableView *table, QString l)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EMPLOYES where regexp_like(NOM,:NOM)");
    query->bindValue(":NOM",l);
    if(l==0)
      {
          query->prepare("select * from EMPLOYES;");
      }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

};

void Employes::chercherEmpTel(QTableView *table, QString l)
{
    QSqlQueryModel *model = new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery;

       query->prepare("SELECT * FROM EMPLOYES WHERE TELEPHONE = :TELEPHONE");
       query->bindValue(":TELEPHONE", l);

       // Si le numéro de téléphone est vide, afficher tous les employés
       if (l.isEmpty()) {
           query->prepare("SELECT * FROM EMPLOYES");
       }

       query->exec();
       model->setQuery(*query);
       table->setModel(model);
       table->show();

};
bool Employes::rfidExists(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT RFID FROM EMPLOYES WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
                // s'il y a retour donc le rfid existe
                qDebug() << "RFID found:" << uid;
                return true;
            } else {
                // pas de retour il n'existe pas
                qDebug() << "RFID not found:" << uid;
            }

    // pas de retour il n'existe pas mafamech chay wallou
    return false;
}

QString Employes::rfidName(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT NOM FROM EMPLOYES WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            // existance equivaut a recuperation du nom
            return query.value(0).toString();
        }
        // pas de retour pas de nom akahaw


        return "";
}

QString Employes::getFunction(const QString& uid)
{
    QString fonction;

    // Requête SQL pour récupérer la fonction de l'employé en fonction de l'UID de la carte RFID
    QSqlQuery query;
    query.prepare("SELECT fonction FROM EMPLOYES WHERE RFID = :RFID");
    query.bindValue(":RFID", uid);

    if(query.exec() && query.next())
    {
        // Récupération de la fonction de l'employé depuis la base de données
        fonction = query.value(0).toString();
    }
    else
    {
        qDebug() << "Erreur lors de la récupération de la fonction de l'employé :" << query.lastError().text();
        // Gestion de l'erreur, par exemple, retourner une chaîne vide ou une valeur par défaut
    }

    return fonction;
}