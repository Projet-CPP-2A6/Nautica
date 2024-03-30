#include "client.h"
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QTableView>
#include <QtDebug>
#include <regex>
using namespace std;
Client::Client() {
  this->CIN = 0;
  this->tel = 0;
  this->date_naissance = QDate::currentDate();
  this->nom = "";
  this->prenom = "";
  this->genre = 0;
  this->email = "";
};

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
    qDebug() << CIN << nom << prenom << date_naissance << genre << tel << email;
  }
};

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
};
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
};

QSqlQueryModel *Client::Afficher() {
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery(
      "SELECT TO_CHAR(CIN), NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, "
      "'DD-MM-YYYY'),  CASE WHEN GENRE = 0 THEN 'M' "
      "ELSE 'F' END AS GENRE, TO_CHAR(TELEPHONE), EMAIL  FROM CLIENTS");
  if (model->lastError().isValid()) {
    qDebug() << "Failed to execute query:" << model->lastError().text();
    qDebug() << "Database Error:" << model->lastError().databaseText();
    delete model;
    return nullptr;
  }

  /*for (int row = 0; row < model->rowCount(); ++row) {
    QString cin = model->record(row).value("CIN").toString();
    QString telephone = model->record(row).value("TELEPHONE").toString();
    cin = QString::number(cin.toLongLong());
    telephone = QString::number(telephone.toLongLong());
    model->setData(model->index(row, model->record(row).indexOf("CIN")), cin);
    model->setData(model->index(row, model->record(row).indexOf("TELEPHONE")),
                   telephone);
  }

  for (int row = 0; row < model->rowCount(); ++row) {
    QDateTime dateNaissance =
        model->record(row).value("DATE_NAISSANCE").toDateTime();
    QString formattedDate = dateNaissance.toString("dd-MM-yyyy");
    model->setData(
        model->index(row, model->record(row).indexOf("DATE_NAISSANCE")),
        formattedDate);
  }*/

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
  QString queryString = "SELECT TO_CHAR(CIN), NOM, PRENOM, "
                        "TO_CHAR(DATE_NAISSANCE, 'DD-MM-YYYY'), "
                        "CASE WHEN GENRE = 0 THEN 'M' ELSE 'F' END AS GENRE, "
                        "TO_CHAR(TELEPHONE), EMAIL "
                        "FROM CLIENTS ORDER BY ";

  QStringList allowedCriteria = {
      "CIN", "NOM", "PRENOM", "DATE_NAISSANCE", "GENRE", "TELEPHONE", "EMAIL"};
  if (!allowedCriteria.contains(critere)) {
    delete model;
    return nullptr;
  }

  queryString += critere;
  query.prepare(queryString);

  if (!query.exec()) {
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

QSqlQueryModel *Client::RechercherEtAfficher(QString searchedText) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery query;
  query.prepare(
      "SELECT TO_CHAR(CIN), NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, "
      "'DD-MM-YYYY'), "
      "CASE WHEN GENRE = 0 THEN 'M' ELSE 'F' END AS GENRE, "
      "TO_CHAR(TELEPHONE), EMAIL "
      "FROM CLIENTS WHERE TO_CHAR(CIN) LIKE '%' || :SEARCHEDTEXT || '%'"
      "OR NOM LIKE '%' || :SEARCHEDTEXT || '%'"
      "OR PRENOM LIKE '%' || :SEARCHEDTEXT || '%'"
      "OR TO_CHAR(TELEPHONE) LIKE '%' || :SEARCHEDTEXT || '%'"
      "OR EMAIL LIKE '%' || :SEARCHEDTEXT || '%' ");
  query.bindValue(":SEARCHEDTEXT", searchedText);
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    delete model;
    return nullptr;
  }
  if (searchedText == "") {
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
}

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
  query.prepare("SELECT GENRE, DATE_NAISSANCE FROM CLIENTS");
  if (!query.exec()) {
    qDebug() << "Error executing query:" << query.lastError().text();
    return {};
  }
  int totalCount = 0;
  int mCount = 0;
  int fCount = 0;
  int totalAge = 0;
  while (query.next()) {
    totalCount++;
    int gender = query.value(0).toInt();
    QDate birthdate = query.value(1).toDate();
    int age = QDate::currentDate().year() - birthdate.year();
    if (QDate::currentDate().month() < birthdate.month() ||
        (QDate::currentDate().month() == birthdate.month() &&
         QDate::currentDate().day() < birthdate.day())) {
      age--;
    }
    if (gender == 0) {
      mCount++;
      totalAge += age;
    } else if (gender == 1) {
      fCount++;
      totalAge += age;
    }
  }
  double averageAge =
      (totalCount > 0) ? (static_cast<double>(totalAge) / totalCount) : 0.0;
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
QString Client::compareClients(Client oldClient, Client newClient) {
  QStringList changes;

  if (oldClient.getCIN() != newClient.getCIN()) {
    changes.append("CIN: " + QString::number(oldClient.getCIN()) + " -> " +
                   QString::number(newClient.getCIN()) + "\n");
  }

  if (oldClient.getTel() != newClient.getTel()) {
    changes.append("Telephone: " + QString::number(oldClient.getTel()) +
                   " -> " + QString::number(newClient.getTel()) + "\n");
  }

  if (oldClient.getDateNaissance() != newClient.getDateNaissance()) {
    changes.append("Date of Birth: " + oldClient.getDateNaissance().toString() +
                   " -> " + newClient.getDateNaissance().toString() + "\n");
  }

  if (oldClient.getNom() != newClient.getNom()) {
    changes.append("Last Name: " + oldClient.getNom() + " -> " +
                   newClient.getNom() + "\n");
  }

  if (oldClient.getPrenom() != newClient.getPrenom()) {
    changes.append("First Name: " + oldClient.getPrenom() + " -> " +
                   newClient.getPrenom() + "\n");
  }

  if (oldClient.getGenre() != newClient.getGenre()) {
    changes.append("Gender: " + QString::number(oldClient.getGenre()) + " -> " +
                   QString::number(newClient.getGenre()) + "\n");
  }

  if (oldClient.getEmail() != newClient.getEmail()) {
    changes.append("Email: " + oldClient.getEmail() + " -> " +
                   newClient.getEmail() + "\n");
  }

  return changes.join(";");
};

bool Client::saveLog(QDateTime datetime, int Client_CIN, QString action,
                     QString changes) {
  QSqlQuery query;
  query.prepare("INSERT INTO LOGS (DATETIME, CIN, ACTION, CHANGES) VALUES "
                "(:DATETIME, :CLIENT_CIN, :ACTION, :CHANGES)");
  query.bindValue(":DATETIME", datetime);
  query.bindValue(":CLIENT_CIN", Client_CIN);
  query.bindValue(":ACTION", action);
  query.bindValue(":CHANGES", changes);
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return false;
  }
  return true;
}
QSqlQueryModel *Client::getLogs(QDate startDate, QDate endDate) {
  QSqlQuery query;
  if (startDate > endDate) {

    return nullptr;
  }
  if (startDate.isValid() && endDate.isValid()) {
    query.prepare("SELECT TO_CHAR(*) FROM LOGS WHERE DATETIME BETWEEN "
                  ":START_DATE AND :END_DATE");
  } else {
    query.prepare("SELECT TO_CHAR(*) FROM LOGS");
  }
  query.bindValue(":START_DATE", startDate);
  query.bindValue(":END_DATE", endDate);
  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return nullptr;
  }
  QSqlQueryModel *model = new QSqlQueryModel();
  model->setQuery(query);
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATETIME"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("ACTION"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("CHANGES"));
  return model;
}
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
