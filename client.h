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
#include <QDate>
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
    
    // Note: You can avoid getters and setters by using the this pointer directly (this->CIN)
    // Getters
    int getCIN();
    int getTel();
    QDate getDateNaissance();
    QString getNom();
    QString getPrenom();
    int getGenre();
    QString getEmail();
    
    // Setters
    void setCIN(int cin);
    void setTel(int tel);
    void setDateNaissance(QDate date_naissance);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setGenre(int genre);
    void setEmail(QString email);

    // CRUD
    bool Ajouter();
    bool Modifier();
    bool Supprimer();
    QSqlQueryModel *Afficher();
    QSqlQueryModel *TriPar(QString critere);
};

#endif // CLIENT_H
