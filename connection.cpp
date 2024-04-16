#include "connection.h"

Connection::Connection() {}

bool Connection::createconnection() {
  bool test = false;
  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("source_projet2A");
  db.setUserName("amine");    // Insert the username
  db.setPassword("esprit18"); // Insert the password

  if (db.open()) {
    test = true;
    qDebug() << "CONNECTE A LA BASE ";
  } else {
    qDebug() << "Failed to connect to Oracle Express Database via ODBC:"
             << db.lastError().text();
    qDebug() << "Oracle Error:" << db.lastError().databaseText();
  }

  return test;
}
