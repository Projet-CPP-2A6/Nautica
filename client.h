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
    Client();
    Client(int CIN, int tel, QDate date_naissance, QString nom, QString prenom, int genre, QString email);
    // Getters
    int getCIN();
    int getTel();
    QDate getNaissance();
    QString getNom();
    QString getPrenom();
    int getGenre();
    QString getEmail();
    
    // setters
    void setCIN(int cin);
    void setTel(int tel);
    void setNaissance(QDate Naissance);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setGenre(int genre);
    void setEmail(QString email);

    // CRUD
    bool Ajouter();
    bool Modifier();
    bool Supprimer(int);
    QSqlQueryModel *Afficher();
};

#endif // CLIENT_H
