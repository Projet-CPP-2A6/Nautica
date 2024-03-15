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
bool rechercher(int reference);
void chercherEquipRef(QTableView *table, QString l);
void chercherEquipType(QTableView *table, QString l);
void chercherEquipEtat(QTableView *table, QString l);
QSqlQueryModel* afficher();



};

#endif // EQUIPEMENTS_H
