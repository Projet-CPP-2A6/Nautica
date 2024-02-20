#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "employes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Employes e(0,"","","",0,"","","",0);
    ui->listEmployetableView->setModel(e.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    int CIN = ui->CIN_LE->text().toInt();
    qDebug() << "Type of variable 'a': " << typeid(CIN).name();
    QString nom = ui->nom_LE->text();
    QString prenom = ui->prenom_LE->text();
    QString adresse = ui->adresse_LE->text();
    QString genre = ui->genre_LE->text();
    QString email = ui->email_LE->text();
    QString fonction = ui->fonction_LE->text();
    int salaire = ui->salaire_LE->text().toInt();
   qDebug() << "Type of variable 'salaire': " << typeid(salaire).name();
    int telephone = ui->telephone_LE->text().toInt();
    qDebug() << "Type of variable 'teelephone': " << typeid(telephone).name();

    Employes e(CIN,nom,prenom,genre,telephone,email,adresse,fonction,salaire);
    e.ajouter();
    bool test=e.ajouter();
    if(test)
    {

      ui->listEmployetableView->setModel(e.afficher());

    }

}

void MainWindow::on_refreshTableV_clicked()
{
    Employes e(0,"","","",0,"","","",0);

    ui->listEmployetableView->setModel(e.afficher());

}

void MainWindow::on_deletePushButton_clicked()
{
     Employes e;
     e.setCin(ui->cinDlineEdit->text().toInt());
     bool test=e.supprimer(e.getcin());
    if(test)
    {
        ui->listEmployetableView->setModel(e.afficher());
    }

}

void MainWindow::on_updatePushButton_clicked()
{
    int CIN = ui->updateCin_LE->text().toInt();
    QString nom = ui->updateNom_LE->text();
    QString prenom = ui->updatePrenom_LE->text();
    QString adresse = ui->updateAdresse_LE->text();
    QString genre = ui->updateGenre_LE->text();
    QString email = ui->updateEmail_LE->text();
    QString fonction = ui->updateFonction_LE->text();
    int telephone = ui->updateTelephone_LE->text().toInt();
    int salaire = ui->updateSalaire_LE->text().toInt();
    Employes e(CIN,nom,prenom,genre,telephone,email,adresse,fonction,salaire);
    e.modifier();
    bool test=e.modifier();
    if(test)
    {
        ui->listEmployetableView->setModel(e.afficher());
    }
}

void MainWindow::on_triCinPushButton_clicked()
{
    Employes e;
    ui->listEmployetableView->setModel(e.triCin());
}

void MainWindow::on_triNomPushButton_clicked()
{
    Employes e;
    ui->listEmployetableView->setModel(e.triNom());
}

void MainWindow::on_loginPushButton_clicked()
{
    QString EMAIL=ui->loginEmailLineEdit->text();
    QString CIN=ui->passwordLineEdit->text();
    qDebug() << "email récupéré :" << EMAIL;
    qDebug() << "cin récupéré :" << CIN;
    QSqlQuery query;
    QString titre;
    query.prepare("SELECT * FROM EMPLOYES WHERE EMAIL = :EMAIL AND CIN = :CIN");
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":CIN", CIN);
    if(query.exec())
      {
        if(query.next())
        {
            ui->stackedWidget->setCurrentIndex(1);
            titre = query.value(7).toString();
             qDebug() << "fonction récupéré :" << titre;

            if (titre.compare("admin")==0)
              {
                ui->employesPushButton->setEnabled(true);
                ui->equipementsPushButton->setEnabled(true);
                ui->clientPushButton->setEnabled(true);
                ui->abonnementPushButton->setEnabled(true);
                ui->evenementsPushButton->setEnabled(true);
              }
            if (titre.compare("employes")==0)
              {
                ui->employesPushButton->setEnabled(true);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);
              }
            if (titre.compare("clients")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(true);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);
              }
            if (titre.compare("equipements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(true);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);
              }
            if (titre.compare("abonnements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(true);
                ui->evenementsPushButton->setEnabled(false);
              }
            if (titre.compare("evenements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(true);
              }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            // Vérification des valeurs récupérées
            qDebug() << "Nom récupéré :" << NOM;
            qDebug() << "Prénom récupéré :" << PRENOM;
            ui->userStatusLabel->setText("utilisateur: "+NOM+" "+PRENOM+"");

        }
        else
        {
            ui->loginInfoLabel->setText("iditenfiants incorrectes!");
        }
    }
   else
       {
           qDebug() << "Erreur lors de l'exécution de la requête SQL:" << query.lastError().text();
           // Traitez ici l'erreur de requête, par exemple, affichez un message d'erreur ou enregistrez la journalisation.
       }
}

void MainWindow::on_employesPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_clientPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_equipementsPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_evenementsPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_abonnementPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

int modes=0;
void MainWindow::on_showHidepushButton_clicked()
{
    if (modes == 1) {
            ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
            ui->showHidepushButton->setText("Hide");
            modes = 0;
        } else {
            ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
            ui->showHidepushButton->setText("Show");
            modes = 1;
        }
}
