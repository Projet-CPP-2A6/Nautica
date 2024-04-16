#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H
#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QDateTime>
#include <QDoubleValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
class Equipements {
private:
  QString reference;
  float prix;
  int nombre;
  QString fonctionalite;
  QString type;
  QString etat;

public:
  Equipements();
  Equipements(QString reference, int prix, int nombre, QString fonctionalite,
              QString type, QString etat);

  // getters
  QString getReference();
  int getPrix();
  int getNombre();
  QString getFonctionalite();
  QString getType();
  QString getEtat();

  // setters
  bool setReference(QString reference);
  bool setPrix(int prix);
  bool setNombre(int nombre);
  void setFonctionalite(QString fonctionalite);
  bool setType(QString type);
  bool setEtat(QString etat);

  // partie crud
  bool ajouter();
  bool modifier();
  bool supprimer();
  QSqlQueryModel *afficher();
  bool rechercher(int reference);
  void chercherEquipRef(QTableView *table, QString l);
  void chercherEquipType(QTableView *table, QString l);
  void chercherEquipEtat(QTableView *table, QString l);
  QSqlQueryModel *triRef();
  QSqlQueryModel *triType();
  QSqlQueryModel *triEtat();
};

#endif // EQUIPEMENTS_H

class Equipement {
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
