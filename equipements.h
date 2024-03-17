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
    int reference;
    float prix;
    int nombre;
    QString fonctionalite;
    QString type;
    QString etat;
    QString image;

public:
    Equipements();
    Equipements(int reference,float prix,int nombre,QString fonctionalite,QString type,QString etat,QString image);

//getters
int getReference();
float getPrix();
int getNombre();
QString getFonctionalite();
QString getType();
QString getEtat();
QString getImage();

//setters
void setReference(int reference );
void setPrix(float prix );
void setNombre(int nombre);
void setFonctionalite(QString fonctionalite);
void setType(QString type);
void setEtat(QString etat);
void setImage(QString image);

//partie crud
bool ajouter();
bool modifier();
bool supprimer(int);
QSqlQueryModel* afficher();



};

#endif // EQUIPEMENTS_H
