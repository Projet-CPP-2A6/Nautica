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
#include "equipements.h"

Equipements::Equipements()
{   reference=0;
    prix=0;
    nombre=0;
    fonctionalite="   ";
    type=" ";
    etat="  ";
    image="  ";

};
 Equipements::Equipements(int reference,float prix,int nombre,QString fonctionalite,QString type,QString etat,QString image)
 {
     this->reference=reference;
     this->prix=prix;
     this->nombre=nombre;
     this->fonctionalite=fonctionalite;
     this->type=type;
     this->etat=etat;
     this->image=image;
 };

//getters
int  Equipements::getReference()
{
    return reference;
};
float Equipements::getPrix()
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
QString Equipements::getImage()
{
    return image;
};

//setters
void Equipements::setReference(int reference)
{
    this->reference=reference;
};
void Equipements::setPrix(float prix )
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
void Equipements::setImage(QString image)
{
    this->image=image;
};

//-----------partie crud--------------------

bool Equipements::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Equipements(REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT,IMAGE)"
                  "VALUES (:REFERENCE,:PRIX,:NOMBRE,:FONCTIONALITE,:TYPE,:ETAT,:IMAGE)");
    query.bindValue(":REFERENCE", reference);
    query.bindValue(":PRIX", prix);
    query.bindValue(":NOMBRE", nombre);
    query.bindValue(":FONCTIONALITE", fonctionalite);
    query.bindValue(":TYPE", type);
    query.bindValue(":ETAT", etat);
    query.bindValue(":IMAGE", image);

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
    query.prepare("UPDATE EQUIPEMENTS SET REFERENCE=:REFERENCE, PRIX=:PRIX, NOMBRE=:NOMBRE, FONCTIONALITE=:FONCTIONALITE, TYPE=:TYPE, IMAGE=:IMAGE WHERE REFERENCE = :REFERENCE ");
    query.bindValue(":REFERENCE", reference);
    query.bindValue(":PRIX", prix);
    query.bindValue(":NOMBRE", nombre);
    query.bindValue(":FONCTIONALITE", fonctionalite);
    query.bindValue(":TYPE", type);
    query.bindValue(":ETAT", etat);
    query.bindValue(":IMAGE", image);
    return query.exec();
};

bool Equipements::supprimer(int)
{
  QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENTS where REFERENCE= :REFERENCE");
    query.bindValue(0, reference);
    return query.exec();
};

QSqlQueryModel* Equipements::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT,IMAGE FROM EQUIPEMENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("IMAGE"));
    return  model;
};
