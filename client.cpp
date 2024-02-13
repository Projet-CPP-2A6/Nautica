#include "client.h"

Client::Client(int CIN, int tel, QDate date_naissance, QString nom, QString prenom, int genre, QString email)
{

    this->CIN = CIN;
    this->tel = tel;
    this->date_naissance = date_naissance;
    this->nom = nom;
    this->prenom = prenom;
    this->genre = genre;
    this->email = email;
}
Client::Ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS"
                  "VALUES (:CIN,:NOM,:PRENOM,:DATE_NAISSANCE,:GENRE,:TELEPHONE,:EMAIL)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", date_naissance);
    query.bindValue(":GENRE", genre);
    query.bindValue(":TELEPHONE", tel);
    query.bindValue(":EMAIL", email);
    if (!query.exec())
    {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    return true;
}
Client::Modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM,DATE_NAISSANCE=:DATE_NAISSANCE, GENRE=:GENRE, TELEPHONE=:TELEPHONE, EMAIL=:EMAIL WHERE CIN = :CIN ");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", date_naissance);
    query.bindValue(":GENRE", genre);
    query.bindValue(":TELEPHONE", tel);
    query.bindValue(":EMAIL", email);
    if (!query.exec())
    {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    return true;
}
bool Client::Supprimer(int)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN=:CIN");
    query.bindValue(0, CIN);
}
QSqlQueryModel *Client::Afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,DATE_NAISSANCE,GENRE,TELEPHONE,EMAIL FROM CLIENTS");
    if (model->lastError().isValid())
    {
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