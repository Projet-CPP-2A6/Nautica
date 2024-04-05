#include "maintenance.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QtDebug>
#include <regex>

maintenance::maintenance() {
  CIN_employe=0;
  reference_equipement=" ";
  date_debut=QDate::currentDate();
  date_fin=QDate::currentDate();
  prix_maintenance=0;
};

maintenance::maintenance(int CIN_employe, QString reference_equipement, QDate date_debut, QDate date_fin, int prix_maintenance)
{
    // Constructor implementation
    this->CIN_employe = CIN_employe;
    this->reference_equipement = reference_equipement;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
    this->prix_maintenance = prix_maintenance;
}

// Getter methods
int maintenance::getCIN() { return CIN_employe; };
QString maintenance::getReferenceEquipement() { return reference_equipement; };
QDate maintenance::getDateDebut() { return date_debut; };
QDate maintenance::getDateFin() { return date_fin; };
int maintenance::getPrixMaintenance() { return prix_maintenance; };

// Setter methods
void maintenance::setCIN(int cin) { CIN_employe = cin; }
void maintenance::setReferenceEquipement(const QString &reference) { reference_equipement = reference; }
void maintenance::setDateDebut(const QDate &date) { date_debut = date; }
void maintenance::setDateFin(const QDate &date) { date_fin = date; }
void maintenance::setPrixMaintenance(int prix) { prix_maintenance = prix; }

bool maintenance::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO MAINTENANCE(CIN_EMPLOYE, REFERENCE_EQUIPEMENT, DATE_DEBUT, DATE_FIN, PRIX_MAINTENANCE) "
                  "VALUES (:CIN_EMPLOYE, :REFERENCE_EQUIPEMENT, :DATE_DEBUT, :DATE_FIN, :PRIX_MAINTENANCE)");
    query.bindValue(":CIN_EMPLOYE", CIN_employe);
    query.bindValue(":REFERENCE_EQUIPEMENT", reference_equipement);
    query.bindValue(":DATE_DEBUT", date_debut);
    query.bindValue(":DATE_FIN", date_fin);
    query.bindValue(":PRIX_MAINTENANCE", prix_maintenance);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    // Return true if the query executes successfully
    return true;
}





