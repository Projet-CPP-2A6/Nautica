#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

class Client
{
private:
    int CIN;
    int tel;
    QDate date_naissance;
    QString nom;
    QString prenom;
    int genre;
    QString email;

public:
    Client(int CIN, int tel, QDate date_naissance, QString nom, QString prenom, int genre, QString email);

    // CRUD
    bool Ajouter();
    bool Modifier();
    bool Supprimer(int);
    QSqlQueryModel *Afficher();
};

#endif // CLIENT_H
