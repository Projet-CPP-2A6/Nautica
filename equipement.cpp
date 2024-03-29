#include "equipement.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>

Equipements::Equipements() {
  reference = "  ";
  prix = 0;
  nombre = 0;
  fonctionalite = "   ";
  type = " ";
  etat = "  ";
};
Equipements::Equipements(QString reference, int prix, int nombre,
                         QString fonctionalite, QString type, QString etat) {
  this->reference = reference;
  this->prix = prix;
  this->nombre = nombre;
  this->fonctionalite = fonctionalite;
  this->type = type;
  this->etat = etat;
};

// getters
QString Equipements::getReference() { return reference; };
int Equipements::getPrix() { return prix; };
int Equipements::getNombre() { return nombre; };
QString Equipements::getFonctionalite() { return fonctionalite; };
QString Equipements::getType() { return type; };
QString Equipements::getEtat() { return etat; };

// setters
void Equipements::setReference(QString reference) {
  this->reference = reference;
};
void Equipements::setPrix(int prix) { this->prix = prix; };
void Equipements::setNombre(int nombre) { this->nombre = nombre; };
void Equipements::setFonctionalite(QString fonctionalite) {
  this->fonctionalite = fonctionalite;
};
void Equipements::setType(QString type) { this->type = type; };
void Equipements::setEtat(QString etat) { this->etat = etat; };

//-----------partie crud--------------------

bool Equipements::ajouter() {
  QSqlQuery query;
  query.prepare(
      "INSERT INTO EQUIPEMENT(REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT)"
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

bool Equipements::modifier() {
  QSqlQuery query;
  query.prepare("UPDATE EQUIPEMENTS SET REFERENCE=:REFERENCE, PRIX=:PRIX, "
                "NOMBRE=:NOMBRE, FONCTIONALITE=:FONCTIONALITE, TYPE=:TYPE "
                "WHERE REFERENCE = :REFERENCE ");
  query.bindValue(":REFERENCE", reference);
  query.bindValue(":PRIX", prix);
  query.bindValue(":NOMBRE", nombre);
  query.bindValue(":FONCTIONALITE", fonctionalite);
  query.bindValue(":TYPE", type);
  query.bindValue(":ETAT", etat);
  return query.exec();
};

bool Equipements::supprimer() {
  QSqlQuery query;
  query.prepare("DELETE FROM EQUIPEMENT where REFERENCE= :REFERENCE");
  query.bindValue(0, getReference());
  return query.exec();
};

QSqlQueryModel *Equipements::afficher() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery(
      "SELECT REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT FROM EQUIPEMENT");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
  return model;
};

bool Equipements::rechercher(int reference) {
  QSqlQuery query;
  query.prepare("SELECT * FROM Equipement WHERE REFERENCE = ?");
  query.addBindValue(reference);

  if (query.exec() && query.next()) {
    prix = query.value(1).toInt();
    nombre = query.value(2).toInt();
    fonctionalite = query.value(3).toString();
    type = query.value(4).toString();
    etat = query.value(5).toString();
    return true;
  } else {
    return false;
  }
}

void Equipements::chercherEquipRef(QTableView *table, QString l) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery;
  query->prepare(
      "select * from EQUIPEMENT where regexp_like(REFERENCE,:REFERENCE)");
  query->bindValue(":REFERENCE", l);
  if (l == 0) {
    query->prepare("select * from EQUIPEMENT");
  }
  query->exec();
  model->setQuery(*query);
  table->setModel(model);
  table->show();
};
void Equipements::chercherEquipType(QTableView *table, QString l) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery;
  query->prepare("select * from EQUIPEMENT where regexp_like(TYPE,:TYPE)");
  query->bindValue(":TYPE", l);
  if (l == 0) {
    query->prepare("select * from EQUIPEMENT;");
  }
  query->exec();
  model->setQuery(*query);
  table->setModel(model);
  table->show();
};
void Equipements::chercherEquipEtat(QTableView *table, QString l) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery;
  query->prepare("select * from EQUIPEMENT where regexp_like(ETAT,:ETAT)");
  query->bindValue(":ETAT", l);
  if (l == 0) {
    query->prepare("select * from EQUIPEMENT;");
  }
  query->exec();
  model->setQuery(*query);
  table->setModel(model);
  table->show();
};

QSqlQueryModel *Equipements::triRef() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM EQUIPEMENT order by REFERENCE");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
  return model;
};
QSqlQueryModel *Equipements::triType() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM EQUIPEMENT order by TYPE");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
  return model;
};
QSqlQueryModel *Equipements::triEtat() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM EQUIPEMENT order by ETAT");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
  return model;
};
#include "equipement.h"

Equipement::Equipement() {}
