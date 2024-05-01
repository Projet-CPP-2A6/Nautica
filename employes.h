#ifndef EMPLOYES_H
#define EMPLOYES_H

#include <QDateTime>
#include <QDoubleValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>

class Employes {
private:
  int CIN;
  int tel;
  int salaire;
  QString nom;
  QString prenom;
  QString genre;
  QString email;
  QString adresse;
  QString fonction;

public:
  Employes();
  Employes(int CIN, QString nom, QString prenom, QString genre, int tel,
           QString email, QString adresse, QString fonction, float salaire);

  // getters
  int getcin();
  int getTel();
  float getSalaire();
  float getTelephone();
  QString getNom();
  QString getPrenom();
  QString getGenre();
  QString getEmail();
  QString getAdresse();
  QString getFonction();

  // setters
  void setCin(int CIN);
  void setNom(QString nom);
  void setPrenom(QString prenom);
  void setGenre(QString genre);
  void setTel(int tel);
  void setEmail(QString email);
  void setAdresse(QString adresse);
  void setFonction(QString fonction);
  void setSalaire(float salaire);

  // partie crud
  bool rechercheAvantAjout(int CIN);
  bool ajouter();
  bool modifier();
  bool supprimer(int);
  bool rechercher(int CIN);
  void chercherEmpCin(QTableView *table, QString l);
  void chercherEmpNom(QTableView *table, QString l);
  void chercherEmpTel(QTableView *table, QString l);
  QSqlQueryModel *afficher();
  QSqlQueryModel *triCin();
  QSqlQueryModel *triNom();
  QSqlQueryModel *triSalary();

  //arduino
  bool rfidExists(QString uid);
  QString rfidName(QString uid);
  QString getFunction(const QString& uid);
  };

#endif // EMPLOYES_H
