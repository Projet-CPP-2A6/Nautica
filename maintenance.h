#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDateTime>
#include <QDoubleValidator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QDate>

class maintenance
{
  private:
    int CIN_employe;
    QString reference_equipement;
    QDate date_debut;
    QDate date_fin;
    int prix_maintenance;

  public:
    maintenance();
    maintenance(int CIN_employe, QString reference_equipement, QDate date_debut, QDate date_fin, int prix_maintenance);

    // Getters
    int getCIN();
    QString getReferenceEquipement();
    QDate getDateDebut();
    QDate getDateFin();
    int getPrixMaintenance();

    // Setters
    void setCIN(int cin);
    void setReferenceEquipement(const QString &reference);
    void setDateDebut(const QDate &date);
    void setDateFin(const QDate &date);
    void setPrixMaintenance(int prix);

    bool ajouter();
};


#endif // MAINTENANCE_H
