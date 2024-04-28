#ifndef ABONEMENT_H
#define ABONEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Abonement
{
public:
    Abonement();
    Abonement(QString i, QString a, QString m,QString c, QString p,QString d);

    QSqlQueryModel *afficher_abonnement();
    bool ajouter();
    bool supprimer_abonnement(QString);
    bool modifier(QString id_abnt);

    QString getIdAbnt() const;

        QString getActivity() const;

        QString getMembre() const;

        QString getCin() const;

        QString getPrice() const;

        QString getDuration() const ;

        void setIdAbnt(const QString &id) ;

        void setActivity(const QString &act) ;

        void setMembre(const QString &mem);

        void setCin(const QString &c);


        void setPrice(const QString &p);

        void setDuration(const QString &dur);

     QSqlQueryModel *displayClause(QString cls);
     QSqlQueryModel *tri_id();
     QSqlQueryModel *tri_prix();
     QSqlQueryModel *tri_type();


     void notification_ajoutAbonement();
     void notification_suppAbonement();
     void notification_modifAbonement();
     void notification_pdf();

private:
    QString id_abnt;
    QString activity;
    QString membre;
    QString cin;
    QString price ;
    QString duration ;

};

#endif // ABONEMENT_H
