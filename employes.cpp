#include "employes.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>

Employes::Employes() {
  CIN = 0;
  nom = " ";
  prenom = "  ";
  genre = "   ";
  tel = 0;
  email = "  ";
  adresse = "  ";
  fonction = "   ";
  salaire = 0;
};
Employes::Employes(int CIN, QString nom, QString prenom, QString genre, int tel,
                   QString email, QString adresse, QString fonction,
                   float salaire) {
  this->CIN = CIN;
  this->nom = nom;
  this->prenom = prenom;
  this->genre = genre;
  this->tel = tel;
  this->email = email;
  this->adresse = adresse;
  this->fonction = fonction;
  this->salaire = salaire;
};

// getters---
int Employes::getcin() { return CIN; };
QString Employes::getNom() { return nom; };
QString Employes::getPrenom() { return prenom; };
QString Employes::getGenre() { return genre; };
int Employes::getTel() { return tel; };
QString Employes::getEmail() { return email; };
QString Employes::getAdresse() { return adresse; };
QString Employes::getFonction() { return fonction; };
float Employes::getSalaire() { return salaire; };

// setters
void Employes::setCin(int CIN) { this->CIN = CIN; };
void Employes::setNom(QString nom) { this->nom = nom; };
void Employes::setPrenom(QString prenom) { this->prenom = prenom; };
void Employes::setGenre(QString genre) { this->genre = genre; };
void Employes::setTel(int tel) { this->tel = tel; };
void Employes::setEmail(QString email) { this->email = email; };
void Employes::setAdresse(QString adresse) { this->adresse = adresse; };
void Employes::setFonction(QString fonction) { this->fonction = fonction; };
void Employes::setSalaire(float salaire) { this->salaire = salaire; };

//-----------partie crud--------------------
bool Employes::rechercheAvantAjout(int CIN) {
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

bool Employes::ajouter() {
  if (!rechercheAvantAjout(CIN)) {
    return false;
  }
  QSqlQuery query;
  query.prepare(
      "INSERT INTO "
      "EMPLOYES(CIN,NOM,PRENOM,GENRE,TELEPHONE,EMAIL,ADRESSE,FONCTION,SALAIRE)"
      "VALUES "
      "(:CIN,:NOM,:PRENOM,:GENRE,:TELEPHONE,:EMAIL,:ADRESSE,:FONCTION,:"
      "SALAIRE)");
  query.bindValue(":CIN", CIN);
  query.bindValue(":NOM", nom);
  query.bindValue(":PRENOM", prenom);
  query.bindValue(":GENRE", genre);
  query.bindValue(":TELEPHONE", tel);
  query.bindValue(":EMAIL", email);
  query.bindValue(":ADRESSE", adresse);
  query.bindValue(":FONCTION", fonction);
  query.bindValue(":SALAIRE", salaire);

  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Oracle Error:" << query.lastError().databaseText();
    return false;
  }

  return true;
}

bool Employes::rechercher(int CIN) {
  QSqlQuery query;
  query.prepare("SELECT * FROM EMPLOYES WHERE CIN = ?");
  query.addBindValue(CIN);

  if (query.exec() && query.next()) {
    nom = query.value(1).toString();
    prenom = query.value(2).toString();
    genre = query.value(3).toString();
    tel = query.value(4).toInt();
    email = query.value(5).toString();
    adresse = query.value(6).toString();
    fonction = query.value(7).toString();
    salaire = query.value(8).toFloat();
    return true;
  } else {
    return false;
  }
}

bool Employes::modifier() {
  QSqlQuery query;
  query.prepare(
      "UPDATE EMPLOYES SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, GENRE=:GENRE, "
      "TELEPHONE=:TELEPHONE, EMAIL=:EMAIL, ADRESSE=:ADRESSE, "
      "FONCTION=:FONCTION, SALAIRE=:SALAIRE WHERE CIN = :CIN ");
  query.bindValue(":CIN", CIN);
  query.bindValue(":NOM", nom);
  query.bindValue(":PRENOM", prenom);
  query.bindValue(":GENRE", genre);
  query.bindValue(":TELEPHONE", tel);
  query.bindValue(":EMAIL", email);
  query.bindValue(":ADRESSE", adresse);
  query.bindValue(":FONCTION", fonction);
  query.bindValue(":SALAIRE", salaire);
  return query.exec();
};

bool Employes::supprimer(int) {
  QSqlQuery query;
  query.prepare("DELETE FROM EMPLOYES where CIN= :CIN");
  query.bindValue(0, CIN);
  return query.exec();
};

QSqlQueryModel *Employes::afficher() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery(
      "SELECT CIN,NOM,PRENOM,GENRE,TELEPHONE,EMAIL,ADRESSE,FONCTION,SALAIRE "
      "FROM EMPLOYES");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENRE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("TELEPHONE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
  model->setHeaderData(7, Qt::Horizontal, QObject::tr("FONCTION"));
  model->setHeaderData(8, Qt::Horizontal, QObject::tr("SALAIRE"));
  return model;
};

QSqlQueryModel *Employes::triCin() {
  QSqlQueryModel *model = new QSqlQueryModel();
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
  return model;
};

QSqlQueryModel *Employes::triNom() {
  QSqlQueryModel *model = new QSqlQueryModel();
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
  return model;
};

QSqlQueryModel *Employes::triSalary() {
  QSqlQueryModel *model = new QSqlQueryModel();
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
  return model;
};

void Employes::chercherEmpCin(QTableView *table, QString l) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery;
  query->prepare("select * from EMPLOYES where regexp_like(CIN,:CIN)");
  query->bindValue(":CIN", l);
  if (l == 0) {
    query->prepare("select * from EMPLOYES");
  }
  query->exec();
  model->setQuery(*query);
  table->setModel(model);
  table->show();
};

void Employes::chercherEmpTel(QTableView *table, QString l) {
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

void Employes::chercherEmpNom(QTableView *table, QString l) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery;
  query->prepare("select * from EMPLOYES where regexp_like(NOM,:NOM)");
  query->bindValue(":NOM", l);
  if (l == 0) {
    query->prepare("select * from EMPLOYES;");
  }
  query->exec();
  model->setQuery(*query);
  table->setModel(model);
  table->show();
};
