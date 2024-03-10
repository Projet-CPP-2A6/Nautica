#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Projet2A");
    db.setUserName("YOUSSEF");
    db.setPassword("youssef");
    if (db.open()) {
               test = true;
               qDebug() << "CONNECTE A LA BASE ";
           } else {
               qDebug() << "Failed to connect to Oracle Express Database via ODBC:" << db.lastError().text();
               qDebug() << "Oracle Error:" << db.lastError().databaseText();
           }
    return test;
}
void Connection::closeConnection(){db.close();}


