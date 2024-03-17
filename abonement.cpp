#include "abonement.h"
#include <QSystemTrayIcon>

Abonement::Abonement()
{

}

Abonement::Abonement(QString i, QString a, QString m,QString c, QString p,QString d)
{
     id_abnt = i;
     activity= a;
     membre = m;
     cin= c;
     price = p;
     duration = d ;


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



