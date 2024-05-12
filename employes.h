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
  QString RFID;

public:
  Employes();
  Employes(int CIN, QString nom, QString prenom, QString genre, int tel,
           QString email, QString adresse, QString fonction, float salaire,
           QString RFID);

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
  QString getRFID();

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
  void setRFID(QString RFID);

  // arduino
  bool rfidExists(QString uid);
  QString rfidName(QString uid);
  QString getFunction(const QString &uid);
};
#endif // EMPLOYES_H
