#include "client.h"
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;
Client::Client() {
  this->CIN = 0;
  this->tel = 0;
  this->date_naissance = QDate::currentDate();
  this->nom = "";
  this->prenom = "";
  this->genre = 0;
  this->email = "";
}

Client::Client(int CIN, QString nom, QString prenom, QDate date_naissance,
               int genre, int tel, QString email) {
  // Setters
  if (setCIN(CIN) && setTel(tel) && setEmail(email)) {
    setDateNaissance(date_naissance);
    setNom(nom);
    setPrenom(prenom);
    setGenre(genre);
  } else {
    qDebug() << "Invalid client data";
  }
}

bool Client::Ajouter() {
  if (Recherche(getCIN()) == 0 && Recherche(getCIN()) != 404) {
    QSqlQuery query;
    query.prepare(
        "INSERT INTO CLIENTS (CIN, NOM, PRENOM, DATE_NAISSANCE, GENRE, "
        "TELEPHONE, EMAIL) VALUES "
        "(:CIN,:NOM,:PRENOM,:DATE_NAISSANCE,:GENRE,:TELEPHONE,:EMAIL)");
    query.bindValue(":CIN", getCIN());
    query.bindValue(":NOM", getNom());
    query.bindValue(":PRENOM", getPrenom());
    query.bindValue(":DATE_NAISSANCE", getDateNaissance());
    query.bindValue(":GENRE", getGenre());
    query.bindValue(":TELEPHONE", getTel());
    query.bindValue(":EMAIL", getEmail());
    if (!query.exec()) {
      qDebug() << "Failed to execute query:" << query.lastError().text();
      qDebug() << "Oracle Error:" << query.lastError().databaseText();
      return false;
    }
    return true;
  }
  return false;
}
bool Client::Modifier() {
  QSqlQuery query;
  query.prepare("UPDATE CLIENTS SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, "
                "DATE_NAISSANCE=:DATE_NAISSANCE, GENRE=:GENRE, "
                "TELEPHONE=:TELEPHONE, EMAIL=:EMAIL WHERE CIN = :CIN ");
  query.bindValue(":CIN", getCIN());
  query.bindValue(":NOM", getNom());
  query.bindValue(":PRENOM", getPrenom());
  query.bindValue(":DATE_NAISSANCE", getDateNaissance());
  query.bindValue(":GENRE", getGenre());
  query.bindValue(":TELEPHONE", getTel());
  query.bindValue(":EMAIL", getEmail());
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Oracle Error:" << query.lastError().databaseText();
    return false;
  }

  return true;
}
bool Client::Supprimer() {
  QSqlQuery query;
  query.prepare("DELETE FROM CLIENTS WHERE CIN=:CIN");
  query.bindValue(":CIN", getCIN());
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Oracle Error:" << query.lastError().databaseText();
    return false;
  }

  return true;
}

QSqlQueryModel *Client::Afficher() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery("SELECT CIN,NOM,PRENOM,DATE_NAISSANCE,GENRE,TELEPHONE,EMAIL "
                  "FROM CLIENTS");
  if (model->lastError().isValid()) {
    qDebug() << "Failed to execute query:" << model->lastError().text();
    qDebug() << "Database Error:" << model->lastError().databaseText();
    delete model;
    return nullptr;
  }
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("GENRE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
  return model;
};

QSqlQueryModel *Client::TriPar(QString critere) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery query;
  query.prepare("SELECT CIN,NOM,PRENOM,DATE_NAISSANCE,GENRE,TELEPHONE,EMAIL "
                "FROM CLIENTS ORDER BY :CRITERE");
  query.bindValue(":CRITERE", critere);
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    delete model;
    return nullptr;
  }
  model->setQuery(query);
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("GENRE"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
  return model;
};

int Client::Recherche(int CIN) {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM CLIENTS WHERE CIN=:CIN");
  query.bindValue(":CIN", CIN);
  if (query.exec() && query.next()) {
    int count = query.value(0).toInt();
    if (count > 0) {
      return 1;
    } else {
      return 0;
    }
  } else {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return 404;
  }
};

vector<int> Client::Statistics() {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*), GENRE, DATE_NAISSANCE FROM CLIENTS");
  if (!query.exec()) {
    qDebug() << "Error executing query:" << query.lastError().text();
    return {};
  }
  int mCount = 0;
  int fCount = 0;
  int totalAge = 0;
  int totalCount = query.value(0).toInt();
  while (query.next() && totalCount > 0) {
    int gender = query.value(1).toInt();
    QDate birthdate = query.value(2).toDate();
    int age = QDate::currentDate().year() - birthdate.year();
    if (QDate::currentDate().month() < birthdate.month() ||
        (QDate::currentDate().month() == birthdate.month() &&
         QDate::currentDate().day() < birthdate.day())) {
      age--;
    }
    // Verify gender which is 1 and which is 0 later
    if (gender == 0) {
      mCount++;
      totalAge += age;
    } else if (gender == 1) {
      fCount++;
      totalAge += age;
    }
  }
  double averageAge = (totalAge / totalCount);
  return {totalCount, mCount, fCount, static_cast<int>(averageAge)};
};

Client Client::RechercheClient(int CIN) {
  QSqlQuery query;
  query.prepare("SELECT * FROM CLIENTS WHERE CIN=:CIN");
  query.bindValue(":CIN", CIN);
  if (query.exec() && query.next()) {
    Client client(query.value(0).toInt(), query.value(1).toString(),
                  query.value(2).toString(), query.value(3).toDate(),
                  query.value(4).toInt(), query.value(5).toInt(),
                  query.value(6).toString());
    return client;
  } else {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return Client();
  }
};
// Getters
int Client::getCIN() { return CIN; };

int Client::getTel() { return tel; };

QDate Client::getDateNaissance() { return date_naissance; };

QString Client::getNom() { return nom; };

QString Client::getPrenom() { return prenom; };

int Client::getGenre() { return genre; };

QString Client::getEmail() { return email; };

// Setters
bool Client::setCIN(int CIN) {
  if ((CIN >= 10000000 && CIN <= 99999999)) {
    this->CIN = CIN;
    return true;
  }
  return false;
};

bool Client::setTel(int tel) {
  if ((tel >= 10000000 && tel <= 99999999)) {
    this->tel = tel;
    return true;
  }
  return false;
};

void Client::setDateNaissance(QDate date_naissance) {
  this->date_naissance = date_naissance;
};

void Client::setNom(QString nom) { this->nom = nom; };

void Client::setPrenom(QString prenom) { this->prenom = prenom; };

void Client::setGenre(int genre) { this->genre = genre; };

bool Client::setEmail(QString email) {
  regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
  if (regex_match(email.toLocal8Bit().constData(), pattern)) {
    this->email = email;
    return true;
  }
  return false;
};
