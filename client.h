#ifndef CLIENT_H
#define CLIENT_H
#include <QDate>
#include <QDebug>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>
#include <vector>
using namespace std;
class Client {
private:
  int CIN;
  int tel;
  QDate date_naissance;
  QString nom;
  QString prenom;
  int genre;
  QString email;

public:
  struct PerformanceStats {
    int month;
    int year;
    double averageNote;
  };
  Client();
  Client(int CIN, QString nom, QString prenom, QDate date_naissance, int genre,
         int tel, QString email);
  // Note: You can avoid getters and setters by using the this pointer directly
  // (this->CIN) Getters
  int getCIN();
  int getTel();
  QDate getDateNaissance();
  QString getNom();
  QString getPrenom();
  int getGenre();
  QString getEmail();

  // Setters
  bool setCIN(int cin);
  bool setTel(int tel);
  void setDateNaissance(QDate date_naissance);
  void setNom(QString nom);
  void setPrenom(QString prenom);
  void setGenre(int genre);
  bool setEmail(QString email);

  // CRUD
  bool Ajouter();
  bool Modifier();
  bool Supprimer();
  QSqlQueryModel *Afficher();
  QSqlQueryModel *RechercherEtAfficher(QString searchedText);
  QSqlQueryModel *TriPar(QString critere);
  int Recherche(int CIN);
  Client RechercheClient(int CIN);
  vector<int> Statistics();
  bool saveLog(QDateTime datetime, int Client_CIN, QString action,
               QString changes);
  QSqlQueryModel *getLogs(QDate startDate, QDate endDate);
  QString compareClients(Client oldClient, Client newClient);
  bool SavePerformance(int CIN, int SessionNote, QDate SessionDate);
  QMap<int, PerformanceStats> RetrievePerformanceStats(int CIN);
};

#endif // CLIENT_H
