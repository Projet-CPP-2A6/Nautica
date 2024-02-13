#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
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
