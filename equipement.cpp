#include "equipement.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>
#include <regex>

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

// Setters
bool Equipements::setReference(QString reference) {
  // Define the new regular expression pattern requiring at least two capital
  // letters
  std::regex pattern("^(.*[A-Z].*){2,}$");

  // Check if the provided string matches the new pattern
  if (std::regex_match(reference.toLocal8Bit().constData(), pattern)) {
    // If it matches, set the reference and return true
    this->reference = reference;
    return true;
  }
  // If it doesn't match, return false
  qDebug() << "Error: Reference must contain at leasttwo capital letters.";
  return false;
}
bool Equipements::setPrix(int prix) {
  // Check if prix is non-negative
  if (prix >= 0) {
    this->prix = prix;
    return true;
  }
  // If prix is negative, return false
  qDebug() << "Error: Prix must be positive.";
  return false;
}
bool Equipements::setNombre(int nombre) {
  // Check if nombre is strictly positive
  if (nombre > 0) {
    this->nombre = nombre;
    return true;
  }
  // If nombre is not strictly positive, return false
  qDebug() << "Error: Nombre must be strictly positive .";
  return false;
}

void Equipements::setFonctionalite(QString fonctionalite) {
  this->fonctionalite = fonctionalite;
};
bool Equipements::setType(QString type) {
  // Check if the provided type is either "sport" or "help"
  if (type == "sport" || type == "help") {
    this->type = type;
    return true;
  }
  // If the provided type is not "sport" or "help", return false
  qDebug() << "Error: Type must be either 'sport' or 'help'.";
  return false;
}

bool Equipements::setEtat(QString etat) {
  // Check if the provided etat is either "bien" or "mauvais"
  if (etat == "bien" || etat == "mauvais") {
    this->etat = etat;
    return true;
  }
  // If the provided etat is not "bien" or "mauvais", return false with an error
  // message
  qDebug() << "Error: Etat must be either 'bien' or 'mauvais'.";
  return false;
}
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

int Equipements::getPrixParRef(QString ref) {
  QSqlQuery query;
  query.prepare("SELECT PRIX FROM EQUIPEMENT WHERE REFERENCE = :REFERENCE");
  query.bindValue(":REFERENCE", ref);
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Oracle Error:" << query.lastError().databaseText();
    return -1;
  }
  // Check if the query has returned any records
  if (!query.next()) {
    qDebug() << "No record found for reference:" << ref;
    return -1;
  }
  // Retrieve the price (PRIX) value from the first record
  return query.value(0).toInt();
}
