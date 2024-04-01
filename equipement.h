#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H

#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QDateTime>
#include <QSqlDatabase>
class Equipements
{
private:
    QString reference;
    float prix;
    int nombre;
    QString fonctionalite;
    QString type;
    QString etat;

public:
    Equipements();
    Equipements(QString reference,int prix,int nombre,QString fonctionalite,QString type,QString etat);

//getters
QString getReference();
int getPrix();
int getNombre();
QString getFonctionalite();
QString getType();
QString getEtat();

//setters
void setReference(QString reference );
void setPrix(int prix );
void setNombre(int nombre);
void setFonctionalite(QString fonctionalite);
void setType(QString type);
void setEtat(QString etat);

//partie crud
bool ajouter();
bool modifier();
bool supprimer();
QSqlQueryModel* afficher();
bool rechercher(int reference);
void chercherEquipRef(QTableView *table, QString l);
void chercherEquipType(QTableView *table, QString l);
void chercherEquipEtat(QTableView *table, QString l);
QSqlQueryModel* triRef();
QSqlQueryModel* triType();
QSqlQueryModel* triEtat();


};

class maintenance
{
private:
    float CIN_employe;
    QString reference_equipement;
    QDate date_debut;
    QDate date_fin;
    float prix_maintenance;
public:
    maintenance();
    maintenance(float CIN_employe,QString reference_equipement,QDate date_debut,QDate date_fin,float prix_maintenance);
    //getters
    float getCIN_employe();
    QString getReference_equipement();
    QDate getDate_debut();
    QDate getDate_fin();
    float getPrix_maintenance();
    //setters
    void setCIN_equipement(float CIN_employe);
    void setReference_equipement(QString reference_equipement);
    void setDate_debut(QDate date_debut);
    void setDate_fin(QDate date_fin);
    void setPrix_maintenance(float prix_maintenance);

    bool ajouter();
};


#endif // EQUIPEMENTS_H

