#include "abonement.h"
#include <QSystemTrayIcon>

Abonement::Abonement()
{

}

Abonement::Abonement(QString i, QString a, QString m,QString c, QString p,QString d,QString e)
{
     id_abnt = i;
     activity= a;
     membre = m;
     cin= c;
     price = p;
     duration = d ;
     PROFESSIONALISME = e;

}

void Abonement::setActivity(const QString &act)
{
    activity = act;
}

void Abonement::setCin(const QString &c)
{
    cin = c;
}

void Abonement::setPrice(const QString &p)
{
    price = p;
}
void Abonement::setDuration(const QString &dur)
{
    duration = dur;
}

void Abonement::setMembre(const QString &mem)
{
    membre = mem;
}

QSqlQueryModel *Abonement::afficher_abonnement()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT CIN, DURATION, MEMBRE, ACTIVITY, PRICE, ID_ABNT FROM ABONNEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("duration"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("membre"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("activity"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("price"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_abnt"));
    return model;
}


bool Abonement::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO abonnement(id_abnt, activity, membre, cin,price,duration) VALUES (:id_abnt, :activity, :membre, :cin,:price,:duration)");
    query.bindValue(":id_abnt", id_abnt);
    query.bindValue(":activity", activity);
    query.bindValue(":membre", membre);
    query.bindValue(":cin", cin);
    query.bindValue(":price", price);
    query.bindValue(":duration", duration);

    return query.exec();
}

bool Abonement::supprimer_abonnement(QString id_abnt)
{
    QSqlQuery query;
    query.prepare("DELETE FROM abonnement WHERE id_abnt = :id_abnt");
    query.bindValue(":id_abnt", id_abnt);
    return query.exec();
}

bool Abonement::modifier(QString id_abnt)
{
    QSqlQuery query;
    query.prepare("UPDATE abonnement SET cin=:cin, duration=:duration, membre=:membre,activity=:activity,price=:price WHERE id_abnt=:id_abnt");
    query.bindValue(":id_abnt", id_abnt);
    query.bindValue(":cin", cin);
    query.bindValue(":duration", duration);
    query.bindValue(":membre", membre);
    query.bindValue(":activity", activity);
    query.bindValue(":price", price);

    return query.exec();
}
QSqlQueryModel * Abonement::researchid(QString i)
{
    QSqlQueryModel * model= new QSqlQueryModel();

         model->setQuery("SELECT CIN, DURATION, MEMBRE, ACTIVITY, PRICE, ID_ABNT FROM ABONNEMENT where CIN like ('%"+i+"%') ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("duration"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("membre"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("activity"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("price"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_abnt"));
             return model;
}
QSqlQueryModel * Abonement::researchidAbnt(QString i)
{
    QSqlQueryModel * model= new QSqlQueryModel();

         model->setQuery("SELECT CIN, DURATION, MEMBRE, ACTIVITY, PRICE, ID_ABNT FROM ABONNEMENT where ID_ABNT like ('%"+i+"%') ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("duration"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("membre"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("activity"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("price"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_abnt"));
             return model;
}
QSqlQueryModel * Abonement::researchidPrice(QString i)
{
    QSqlQueryModel * model= new QSqlQueryModel();

         model->setQuery("SELECT CIN, DURATION, MEMBRE, ACTIVITY, PRICE, ID_ABNT FROM ABONNEMENT where PRICE like ('%"+i+"%') ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("duration"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("membre"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("activity"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("price"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("id_abnt"));
             return model;
}

QString Abonement::Calculer_Professionnalisme(QString cin, int points)
{
    QSqlQuery query;
    query.prepare("SELECT PROFESSIONALISME FROM ABONNEMENT WHERE cin = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
       // qDebug() << "Erreur lors de la récupération des informations de l'employé : " << query.lastError().text();
        return "";
    }

    if (query.next()) {
        QString niveauStr = query.value("PROFESSIONALISME").toString();





        // Mise à jour du professionnalisme dans la base de données
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE ABONNEMENT SET PROFESSIONALISME = :professionnalisme WHERE cin = :cin");
        updateQuery.bindValue(":professionnalisme", QString::number(points));
        updateQuery.bindValue(":cin", cin);

        if (updateQuery.exec()) {
           // qDebug() << "Mise à jour du professionnalisme et du salaire avec succès.";
            return niveauStr;  // Retourner le niveau actuel du professionnalisme
        } else {
           // qDebug() << "Erreur lors de la mise à jour du professionnalisme et du salaire : " << updateQuery.lastError().text();
        }
    } else {
        //qDebug() << "CIN inexistant.";
    }

    return "";
}

