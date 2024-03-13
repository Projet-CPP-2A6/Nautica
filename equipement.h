#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QDateTime>
#include <QSqlDatabase>

class Equipement
{
    QString reference;
    QString fonctionalite;
    float prix;
    QString nom;
    QString prenom;
    QString genre;
    QString email;
    QString adresse;
    QString fonction;
public:
    Equipement();
};

#endif // EQUIPEMENT_H
