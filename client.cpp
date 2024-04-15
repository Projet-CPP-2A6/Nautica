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

QSqlQueryModel *Client::RechercherEtAfficher(QString criteria, QString searchedText) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    QString queryString = QString("SELECT TO_CHAR(CIN), NOM, PRENOM, TO_CHAR(DATE_NAISSANCE, 'DD-MM-YYYY'), "
                                  "CASE WHEN GENRE = 0 THEN 'M' ELSE 'F' END AS GENRE, "
                                  "TO_CHAR(TELEPHONE), EMAIL "
                                  "FROM CLIENTS WHERE ");

    if (criteria == "CIN") {
        queryString.append("TO_CHAR(CIN) LIKE :searchedText");
    } else if (criteria == "NAME") {
        queryString.append("PRENOM LIKE :searchedText");
    } else if (criteria == "LASTNAME") {
        queryString.append("NOM LIKE :searchedText");
    } else if (criteria == "EMAIL") {
        queryString.append("EMAIL LIKE :searchedText");
    } else if (criteria == "TELEPHONE") {
        queryString.append("TO_CHAR(TELEPHONE) LIKE :searchedText");
    } else {
        qDebug() << "Invalid criteria.";
        delete model;
        return nullptr;
    }

    query.prepare(queryString);
    query.bindValue(":searchedText", "%" + searchedText + "%");

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Database Error:" << query.lastError().databaseText();
        delete model;
        return nullptr;
    }

    if (searchedText.isEmpty() || criteria.isEmpty()) {
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("LAST NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FIRST NAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE OF BIRTH"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PHONE NUMBER"));
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

std::vector<int> Client::AgeStatistics() {
  std::vector<int> ageStats(3, 0); // Initialize with three zeros: total, under 18, over 18
  QSqlQuery query;
  query.prepare("SELECT DATE_NAISSANCE FROM CLIENTS");
  if (!query.exec()) {
    qDebug() << "Error executing query:" << query.lastError().text();
    return ageStats;
  }

  while (query.next()) {
    QDate birthDate = query.value(0).toDate();
    int age = QDate::currentDate().year() - birthDate.year();
    if (age < 18)
      ageStats[1]++; // Increment count of people under 18
    else
      ageStats[2]++; // Increment count of people over 18
    ageStats[0]++; // Increment total count
  }

  return ageStats;
};

std::vector<int> Client::GenderStatistics() {
    std::vector<int> genderStats(3, 0); // Initialize with three zeros: total count, male count, and female count
    QSqlQuery query;
    query.prepare("SELECT GENRE FROM CLIENTS");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return genderStats;
    }

    while (query.next()) {
        int gender = query.value(0).toInt(); // Assuming 0 for male, 1 for female
        if (gender == 0)
            genderStats[1]++; // Increment male count
        else if (gender == 1)
            genderStats[2]++; // Increment female count
        // Increment total count regardless of gender
        genderStats[0]++;
    }

    return genderStats;
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

  return changes.join(" ; ");
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
  QSqlQueryModel *model = new QSqlQueryModel();

  if (!startDate.isValid() || !endDate.isValid() || startDate > endDate) {
    qDebug() << "Invalid date range.";
    return nullptr;
  }

  QSqlQuery query;
  if (startDate == endDate) {
    query.prepare("SELECT DATETIME, TO_CHAR(CIN), ACTION, CHANGES FROM LOGS");
  } else {
    query.prepare("SELECT DATETIME, TO_CHAR(CIN), ACTION, CHANGES FROM LOGS "
                  "WHERE TRUNC(DATETIME) BETWEEN TO_DATE(:START_DATE, "
                  "'DD/MM/YYYY') AND TO_DATE(:END_DATE, 'DD/MM/YYYY')");
    query.bindValue(":START_DATE", startDate.toString("dd/MM/yyyy"));
    query.bindValue(":END_DATE", endDate.toString("dd/MM/yyyy"));
  }

  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return nullptr;
  }

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

bool Client::SavePerformance(int CIN, int SessionNote, QDate SessionDate) {
  QSqlQuery query;
  query.prepare("INSERT INTO CLIENT_PERFORMANCE (CIN, SESSIONNOTE, "
                "SESSIONDATE) VALUES (:CIN, :SessionNote, :SessionDate)");
  query.bindValue(":CIN", CIN);
  query.bindValue(":SessionNote", SessionNote); // corrected binding
  query.bindValue(":SessionDate", SessionDate);

  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return false;
  }
  return true;
}

QMap<int, Client::PerformanceStats> Client::RetrievePerformanceStats(int CIN) {
  QMap<int, Client::PerformanceStats> performanceData;

  QSqlQuery query;
  query.prepare(
      "SELECT EXTRACT(MONTH FROM SESSIONDATE) AS month, EXTRACT(YEAR FROM "
      "SESSIONDATE) AS year, SUM(SESSIONNOTE) AS total_notes, COUNT(*) AS "
      "session_count FROM CLIENT_PERFORMANCE WHERE CIN = :CIN GROUP BY "
      "EXTRACT(YEAR FROM SESSIONDATE), EXTRACT(MONTH FROM SESSIONDATE)");
  query.bindValue(":CIN", CIN);

  if (!query.exec()) {
    qDebug() << "Failed to execute query:" << query.lastError().text();
    qDebug() << "Database Error:" << query.lastError().databaseText();
    return performanceData;
  }

  while (query.next()) {
    int month = query.value("month").toInt();
    int year = query.value("year").toInt();
    int totalNotes = query.value("total_notes").toInt();
    int sessionCount = query.value("session_count").toInt();

    double averageNote = (sessionCount > 0)
                             ? static_cast<double>(totalNotes) / sessionCount
                             : 0.0;
    Client::PerformanceStats stats;
    stats.month = month;
    stats.year = year;
    stats.averageNote = averageNote;

    performanceData.insertMulti(month, stats);
  }

  return performanceData;
}
