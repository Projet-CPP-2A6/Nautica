#ifndef CONNEXION_H
#define CONNEXION_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class Connection {
  QSqlDatabase db;

public:
  Connection();
  bool createconnection();
  void closeConnection();
};

#endif // CONNECTION_H
