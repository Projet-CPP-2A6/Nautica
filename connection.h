#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class Connection
{
    QSqlDatabase db;

public:
    Connection();
    bool createconnection();
    void closeConnection();
};

#endif //CONNECTION_H
