#include <QTableView>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include "equipement.h"

Equipements::Equipements()
{   reference="  ";
    prix=0;
    nombre=0;
    fonctionalite="   ";
    type=" ";
    etat="  ";
};

maintenance::maintenance()
{
    CIN_employe=0;
    reference_equipement=" ";
    date_debut=QDate::currentDate();
    date_fin=QDate::currentDate();
    prix_maintenance=0;
};


 Equipements::Equipements(QString reference,int prix,int nombre,QString fonctionalite,QString type,QString etat)
 {
     this->reference=reference;
     this->prix=prix;
     this->nombre=nombre;
     this->fonctionalite=fonctionalite;
     this->type=type;
     this->etat=etat;
 };

 maintenance::maintenance(float CIN_employe,QString reference_equipement,QDate date_debut,QDate date_fin,float prix_maintenance)
 {
     this->CIN_employe=CIN_employe;
     this->reference_equipement=reference_equipement;
     this->date_debut=date_debut;
     this->date_fin=date_fin;
     this->prix_maintenance=prix_maintenance;
 };

//getters
float maintenance::getCIN_employe()
{
  return CIN_employe;
};
QString maintenance::getReference_equipement()
{
    return reference_equipement;
};
QDate maintenance::getDate_debut()
{
    return date_debut;
};
QDate maintenance::getDate_fin()
{
    return date_fin;
};
float maintenance::getPrix_maintenance()
{
    return prix_maintenance;
};
QString  Equipements::getReference()
{
    return reference;
};
int Equipements::getPrix()
{
    return prix;
};
int Equipements::getNombre()
{
    return nombre;
};
QString Equipements::getFonctionalite()
{
    return fonctionalite;
};
QString   Equipements::getType()
{
    return type;
};
QString Equipements::getEtat()
{
    return etat;
};

//setters
void maintenance::setCIN_equipement(float CIN_employe)
{
    this->CIN_employe=CIN_employe;
};
void maintenance::setReference_equipement(QString reference_equipement)
{
    this->reference_equipement=reference_equipement;
};
void maintenance::setDate_debut(QDate date_debut)
{
    this->date_debut=date_debut;
};
void maintenance::setDate_fin(QDate date_fin)
{
    this->date_fin=date_fin;
};
void maintenance::setPrix_maintenance(float prix_maintenance)
{
    this->prix_maintenance=prix_maintenance;
};
void Equipements::setReference(QString reference)
{
    this->reference=reference;
};
void Equipements::setPrix(int prix )
{
    this->prix=prix;
};
void Equipements::setNombre(int nombre)
{
    this->nombre=nombre;
};
void Equipements::setFonctionalite(QString fonctionalite)
{
    this->fonctionalite=fonctionalite;
};
void Equipements::setType(QString type)
{
    this->type=type;
};
void Equipements::setEtat(QString etat)
{
    this->etat=etat;
};

//-----------partie crud--------------------

bool Equipements::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT(REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT)"
                  "VALUES (:REFERENCE,:PRIX,:NOMBRE,:FONCTIONALITE,:TYPE,:ETAT)");
    query.bindValue(":REFERENCE", getReference());
    query.bindValue(":PRIX", getPrix());
    query.bindValue(":NOMBRE", getNombre());
    query.bindValue(":FONCTIONALITE", getFonctionalite());
    query.bindValue(":TYPE", getType());
    query.bindValue(":ETAT", getEtat());

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        return false;
    }

    return true;
}

bool maintenance::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO MAINTENANCE(CIN_EMPLOYE,REFERENCE_EQUIPEMENT,DATE_DEBUT,DATE_FIN,PRIX_MAINTENANCE) "
                  "VALUES (:CIN_EMPLOYE, :REFERENCE_EQUIPEMENT, :DATE_DEBUT, :DATE_FIN, CAST(:PRIX_MAINTENANCE AS FLOAT))");

    query.bindValue(":CIN_EMPLOYE", getCIN_employe());
    query.bindValue(":REFERENCE_EQUIPEMENT", getReference_equipement());
    query.bindValue(":DATE_DEBUT", getDate_debut()); // Directly bind QDate
    query.bindValue(":DATE_FIN", getDate_fin()); // Directly bind QDate
    query.bindValue(":PRIX_MAINTENANCE", getPrix_maintenance());
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
        qDebug() << "Values bound:";
        qDebug() << "CIN_EMPLOYE:" << getCIN_employe();
        qDebug() << "REFERENCE_EQUIPEMENT:" << getReference_equipement();
        qDebug() << "DATE_DEBUT:" << getDate_debut();
        qDebug() << "DATE_FIN:" << getDate_fin();
        qDebug() << "PRIX_MAINTENANCE:" << getPrix_maintenance();
        qDebug() << "Oracle Error:" << query.lastError().databaseText();
        qDebug() << "Value bound to PRIX_MAINTENANCE:" << QString::number(getPrix_maintenance());

        return false;
    }

    qDebug() << "Query executed successfully:" << query.lastQuery();
    return true;
}



bool Equipements::modifier()
{
  QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENTS SET REFERENCE=:REFERENCE, PRIX=:PRIX, NOMBRE=:NOMBRE, FONCTIONALITE=:FONCTIONALITE, TYPE=:TYPE WHERE REFERENCE = :REFERENCE ");
    query.bindValue(":REFERENCE", reference);
    query.bindValue(":PRIX", prix);
    query.bindValue(":NOMBRE", nombre);
    query.bindValue(":FONCTIONALITE", fonctionalite);
    query.bindValue(":TYPE", type);
    query.bindValue(":ETAT", etat);
    return query.exec();
};

bool Equipements::supprimer()
{
  QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENT where REFERENCE= :REFERENCE");
    query.bindValue(0, getReference());
    return query.exec();
};

QSqlQueryModel* Equipements::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT REFERENCE,PRIX,NOMBRE,FONCTIONALITE,TYPE,ETAT FROM EQUIPEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    return  model;
};

bool Equipements::rechercher(int reference)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Equipement WHERE REFERENCE = ?");
    query.addBindValue(reference);

    if (query.exec() && query.next())
    {
        prix = query.value(1).toInt();
        nombre = query.value(2).toInt();
        fonctionalite = query.value(3).toString();
        type = query.value(4).toString();
        etat = query.value(5).toString();
        return true;
    }
    else
    {
        return false;
    }
}

void Equipements::chercherEquipRef(QTableView *table, QString l)
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery *query =new QSqlQuery;
        query->prepare("select * from EQUIPEMENT where regexp_like(REFERENCE,:REFERENCE)");
        query->bindValue(":REFERENCE",l);
        if(l==0)
        {
            query->prepare("select * from EQUIPEMENT");
        }
        query->exec();
        model->setQuery(*query);
        table->setModel(model);
        table->show();

};
void Equipements::chercherEquipType(QTableView *table, QString l)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EQUIPEMENT where regexp_like(TYPE,:TYPE)");
    query->bindValue(":TYPE",l);
    if(l==0)
      {
          query->prepare("select * from EQUIPEMENT;");
      }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

};
void Equipements::chercherEquipEtat(QTableView *table, QString l)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EQUIPEMENT where regexp_like(ETAT,:ETAT)");
    query->bindValue(":ETAT",l);
    if(l==0)
      {
          query->prepare("select * from EQUIPEMENT;");
      }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();

};

QSqlQueryModel* Equipements::triRef()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT order by REFERENCE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    return  model;

};
QSqlQueryModel* Equipements::triType()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT order by TYPE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    return  model;

};
QSqlQueryModel* Equipements::triEtat()
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT order by ETAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FONCTIONALITE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NOMBRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ETAT"));
    return  model;

};

