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
#include "equipement.h"

Equipements::Equipements()
{   reference="  ";
    prix=0;
    nombre=0;
    fonctionalite="   ";
    type=" ";
    etat="  ";
};
 Equipements::Equipements(QString reference,int prix,int nombre,QString fonctionalite,QString type,QString etat)
 {
     this->reference=reference;
     this->prix=prix;
     this->nombre=nombre;
     this->fonctionalite=fonctionalite;
     this->type=type;
     this->etat=etat;
 };

//getters
QString  Equipements::getReference()
{
    return reference;
};
int Equipements::getPrix()
{
    return prix;
};
int Equipements::getNombre()
{
    return nombre;
};
QString Equipements::getFonctionalite()
{
    return fonctionalite;
};
QString   Equipements::getType()
{
    return type;
};
QString Equipements::getEtat()
{
    return etat;
};

//setters
void Equipements::setReference(QString reference)
{
    this->reference=reference;
};
void Equipements::setPrix(int prix )
{
    this->prix=prix;
};
void Equipements::setNombre(int nombre)
{
    this->nombre=nombre;
};
void Equipements::setFonctionalite(QString fonctionalite)
{
    this->fonctionalite=fonctionalite;
};
void Equipements::setType(QString type)
{
    this->type=type;
};
void Equipements::setEtat(QString etat)
{
    this->etat=etat;
};

//-----------partie crud--------------------

bool Equipements::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT(REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT)"
                  "VALUES (:REFERENCE,:PRIX,:NOMBRE,:FONCTIONALITE,:TYPE,:ETAT)");
    query.bindValue(":REFERENCE", getReference());
    query.bindValue(":PRIX", getPrix());
    query.bindValue(":NOMBRE", getNombre());
    query.bindValue(":FONCTIONALITE", getFonctionalite());
    query.bindValue(":TYPE", getType());
    query.bindValue(":ETAT", getEtat());

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    return true;
}

bool Equipements::modifier()
{
  QSqlQuery query;
    query.prepare("UPDATE Equipement SET REFERENCE=:REFERENCE, FONCTIONALITE=:FONCTIONALITE, PRIX=:PRIX, TYPE=:TYPE, NOMBRE=:NOMBRE, ETAT=:ETAT WHERE REFERENCE = :REFERENCE ");
    query.bindValue(":REFERENCE", getReference());
    query.bindValue(":FONCTIONALITE", getFonctionalite());
    query.bindValue(":PRIX", getPrix());
    query.bindValue(":TYPE", getType());
    query.bindValue(":NOMBRE", getNombre());
    query.bindValue(":ETAT", getEtat());
    return query.exec();
};

bool Equipements::supprimer()
{
  QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENT where REFERENCE= :REFERENCE");
    query.bindValue(0, getReference());
    return query.exec();
};

QSqlQueryModel* Equipements::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT FROM EQUIPEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    return  model;
};
