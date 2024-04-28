#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
#include <QTableView>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QUrl>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTextCodec> //je vien d'ajout de la bibliotheque de Qtextcodec !!
#include <QThread>

//#include <QWidget>
#include "employes.h"
#include "client.h"
#include "abonement.h"
#include "arduino.h"
//#include "connection.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduinoConnected = false; // Au début, l'Arduino n'est pas connecté

    Employes e(0,"","","",0,"","","",0);
    ui->listEmployetableView->setModel(e.afficher());
   // int state = 0;

    connect(ui->bouttonArduino, &QPushButton::clicked, this, &MainWindow::toggleArduinoConnection);

          ui->frame_3->setVisible(false);

    ui->stackedWidget->setCurrentIndex(0);

//Arduino A;
   /* int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }*/
                // QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(read_from_arduino())); // permet de lancer
                 //le slot update_label suite à la reception du signal readyRead (reception des données)
                    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(connect_RFID()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//arduino
void MainWindow::toggleArduinoConnection()
{
    if (arduinoConnected) {
        int ret = A.close_arduino(); // Fermer la connexion à Arduino
        if (ret == 0) {
            qDebug() << "Arduino disconnected";
            arduinoConnected = false;
        } else {
            qDebug() << "Failed to disconnect Arduino";
        }
    } else {
        int ret = A.connect_arduino(); // Établir la connexion à Arduino
        switch(ret){
            case(0): {
                qDebug()<< "Arduino connected to port : "<< A.getarduino_port_name();
                arduinoConnected = true;
                break;
            }
            case(1): {
                qDebug() << "Arduino available but not connected to :" << A.getarduino_port_name();
                break;
            }
            case(-1): {
                qDebug() << "Arduino not available";
                break;
            }
        }
    }
}
void MainWindow::connect_RFID()

{
    // pour tester si la connexion lors du passage de la carte rfid a ete effectué ou non avec un label 'RFID_Label'

    //ui->RFID_Label->setText("arduino detected");

     QByteArray dataArduino = A.read_from_arduino();
    QString uid = QTextCodec::codecForMib(106)->toUnicode(dataArduino);

    //qDebug()<<uid;//pour tester dans la console de QT
    qDebug() << uid << endl;



    ui->RFID_Label->setText(uid);/*------- pour tester avec un label----------*/

    Employes E; //remplacez avec le nom de votre classe

     // cas ou elle existe
    if(E.rfidExists(uid))

        {

            QByteArray data1;
            data1.append('1');
            A.write_to_arduino(data1);//envoie 1 a arduino et enclenche /demarre le processus 1

            qDebug()<<"carte existante";

            QString fonction = E.getFunction(uid);
             setPermissions(fonction);

            //prend la valeur du nom
            QString nom = E.rfidName(uid);
            //ui->RFID_NOM->setText(nom);
            ui->stackedWidget->setCurrentIndex(1); //redirige ves la page 1 de l'application (menu)
            ui->frame_3->setVisible(true);
            ui->userStatusLabel->setText("utilisateur: "+nom);

            QByteArray nomData(nom.toUtf8(), 8);
            A.write_to_arduino(nomData);

           // QString CRfid = E.rfidName(uid);



        }

    // cas ou elle n'existe pas
    else if (!E.rfidExists(uid))
        {
            //inexistante
                QByteArray data1;
                data1.append('2');
                A.write_to_arduino(data1); // envoie 2 a arduino et enclenche /demarre le processus 2

                qDebug()<<"carte inexistante";

        }

 }


void MainWindow::setPermissions(const QString& fonction)
{

    if (fonction == "admin")
    {
        ui->employesPushButton->setEnabled(true);
        ui->equipementsPushButton->setEnabled(true);
        ui->clientPushButton->setEnabled(true);
        ui->abonnementPushButton->setEnabled(true);
        ui->evenementsPushButton->setEnabled(true);

        ui->pushButton_7->setEnabled(true);
        ui->login_pushButton_6->setEnabled(true);
        ui->BTmenu_EmpoyepushButton->setEnabled(true);
        ui->Abonnement_pushButton->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->menu_pushButton->setEnabled(true);
    }
    else if(fonction == "employes")
    {
        ui->employesPushButton->setEnabled(true);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);

        ui->pushButton_7->setEnabled(false);
        ui->login_pushButton_6->setEnabled(false);
        ui->BTmenu_EmpoyepushButton->setEnabled(true);
        ui->Abonnement_pushButton->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(true);
    }
    else if(fonction == "clients")
    {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(true);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);

        ui->pushButton_7->setEnabled(true);
        ui->login_pushButton_6->setEnabled(false);
        ui->BTmenu_EmpoyepushButton->setEnabled(false);
        ui->Abonnement_pushButton->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(true);

    }
    else if(fonction == "abonnements")
    {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(true);
        ui->evenementsPushButton->setEnabled(false);

        ui->pushButton_7->setEnabled(false);
        ui->login_pushButton_6->setEnabled(false);
        ui->BTmenu_EmpoyepushButton->setEnabled(false);
        ui->Abonnement_pushButton->setEnabled(true);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(true);
    }
    else if(fonction == "equipements")
    {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(true);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);

        ui->pushButton_7->setEnabled(false);
        ui->login_pushButton_6->setEnabled(true);
        ui->BTmenu_EmpoyepushButton->setEnabled(false);
        ui->Abonnement_pushButton->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(true);
    }
    else if(fonction == "evenements")
    {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(true);

        ui->pushButton_7->setEnabled(false);
        ui->login_pushButton_6->setEnabled(false);
        ui->BTmenu_EmpoyepushButton->setEnabled(false);
        ui->Abonnement_pushButton->setEnabled(true);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(true);
    }
    else
    {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);

        ui->pushButton_7->setEnabled(false);
        ui->login_pushButton_6->setEnabled(false);
        ui->BTmenu_EmpoyepushButton->setEnabled(false);
        ui->Abonnement_pushButton->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        ui->menu_pushButton->setEnabled(false);
    }
}



bool valid_id(QString id)
{
    for (int i = 0;i < id.length(); i++)
    {
       if((id[i] >= '0' && id[i] <= '9'))
       {

       }
           else
       {
       return false ;
       }
    }
    return true ;
}

void MainWindow::on_pushButton_3_clicked()
{
    // Récupération des valeurs des champs
    QString cinStr = ui->CIN_LE->text();
    QString nom = ui->nom_LE->text();
    QString prenom = ui->prenom_LE->text();
    QString adresse = ui->adresse_LE->text();
    QString genre = ui->genre_LE->text().toLower(); // Convertir en minuscules pour la comparaison
    QString email = ui->email_LE->text();
    QString fonction = ui->fonction_LE->text();
    int salaire = ui->salaire_LE->text().toInt();
    QString telephoneStr = ui->telephone_LE->text();

    // Expression régulière pour vérifier le format du CIN (chiffres seulement)
    QRegExp regexCIN("^[0-9]+$");
    // Expression régulière pour vérifier le format du nom et du prénom (lettres seulement)
    QRegExp regexNomPrenom("^[a-zA-Z]+$");
    // Expression régulière pour vérifier le format de l'email
    QRegExp regexEmail("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    // Expression régulière pour vérifier le format du numéro de téléphone (chiffres seulement)
    QRegExp regexTelephone("^[0-9]+$");

    // Vérification des saisies
    if (cinStr.isEmpty() || !regexCIN.exactMatch(cinStr))
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (chiffres seulement).");
        return;
    }

    if (nom.isEmpty() || !regexNomPrenom.exactMatch(nom))
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un nom valide (lettres seulement).");
        return;
    }

    if (prenom.isEmpty() || !regexNomPrenom.exactMatch(prenom))
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un prénom valide (lettres seulement).");
        return;
    }

    if (email.isEmpty() || !regexEmail.exactMatch(email))
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
        return;
    }

    if (telephoneStr.isEmpty() || !regexTelephone.exactMatch(telephoneStr))
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un numéro de téléphone valide (chiffres seulement).");
        return;
    }

    // Vérification du nombre de chiffres dans le numéro de téléphone
    if (telephoneStr.length() != 8)
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un numéro de téléphone valide (8 chiffres).");
        return;
    }

    // Vérification du genre
    if (genre != "homme" && genre != "femme")
    {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un genre valide (homme ou femme).");
        return;
    }

    // Convertir les champs nécessaires en types appropriés
    int CIN = cinStr.toInt();
    int telephone = telephoneStr.toInt();

    // Si toutes les saisies sont valides, ajoutez l'employé
    Employes e(CIN, nom, prenom, genre, telephone, email, adresse, fonction, salaire);
    bool test = e.ajouter();
    if (test)
    {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        ui->listEmployetableView->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Employé existant. Veuillez réessayer.");
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
    // Récupération des valeurs des champs
    int CIN = ui->updateCin_LE->text().toInt();
    QString nom = ui->updateNom_LE->text();
    QString prenom = ui->updatePrenom_LE->text();
    QString adresse = ui->updateAdresse_LE->text();
    QString genre = ui->updateGenre_LE->text();
    QString email = ui->updateEmail_LE->text();
    QString fonction = ui->updateFonction_LE->text();
    int telephone = ui->updateTelephone_LE->text().toInt();
    int salaire = ui->updateSalaire_LE->text().toInt();

    // Vérification des contraintes de saisie
    bool saisieValide = true;
    QString messageErreur;

    // Vérification du nom et prénom
    if(nom.isEmpty() || prenom.isEmpty()) {
        messageErreur += "Veuillez saisir le nom et le prénom.\n";
        saisieValide = false;
    }

    // Vérification du genre
    if(genre.toLower() != "homme" && genre.toLower() != "femme") {
        messageErreur += "Le genre doit être 'Homme' ou 'Femme'.\n";
        saisieValide = false;
    }

    // Vérification du format de l'email
    QRegExp regex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    if(!email.contains(regex)) {
        messageErreur += "Veuillez saisir une adresse email valide.\n";
        saisieValide = false;
    }

    // Vérification de la fonction (lettre seulement)
    QRegExp regexFonction("[A-Za-z]+");
    if (!fonction.contains(regexFonction)) {
        messageErreur += "La fonction doit contenir uniquement des lettres.\n";
        saisieValide = false;
    }



    // Si la saisie est valide, effectuer la modification
    if(saisieValide) {
        Employes e(CIN, nom, prenom, genre, telephone, email, adresse, fonction, salaire);
        bool test = e.modifier();
        if(test) {
            ui->listEmployetableView->setModel(e.afficher());
            // Effacer les champs après la modification réussie
            ui->updateCin_LE->clear();
            ui->updateNom_LE->clear();
            ui->updatePrenom_LE->clear();
            ui->updateAdresse_LE->clear();
            ui->updateGenre_LE->clear();
            ui->updateEmail_LE->clear();
            ui->updateFonction_LE->clear();
            ui->updateTelephone_LE->clear();
            ui->updateSalaire_LE->clear();
        }
    } else {
        // Afficher un message d'erreur si la saisie est invalide
        QMessageBox::critical(this, "Erreur de saisie", messageErreur);
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

void MainWindow::on_triSalaryPushButton_clicked()
{
    Employes e;
    ui->listEmployetableView->setModel(e.triSalary());
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
        ui->frame_3->setVisible(true);

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

                ui->pushButton_7->setEnabled(true);
                ui->login_pushButton_6->setEnabled(true);
                ui->BTmenu_EmpoyepushButton->setEnabled(true);
                ui->Abonnement_pushButton->setEnabled(true);
                ui->pushButton_10->setEnabled(true);
                ui->menu_pushButton->setEnabled(true);

              }
            else if (titre.compare("employes")==0)
              {
                ui->employesPushButton->setEnabled(true);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);

                ui->pushButton_7->setEnabled(false);
                ui->login_pushButton_6->setEnabled(false);
                ui->BTmenu_EmpoyepushButton->setEnabled(true);
                ui->Abonnement_pushButton->setEnabled(false);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(true);

              }
            else if (titre.compare("clients")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(true);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);

                ui->pushButton_7->setEnabled(true);
                ui->login_pushButton_6->setEnabled(false);
                ui->BTmenu_EmpoyepushButton->setEnabled(false);
                ui->Abonnement_pushButton->setEnabled(false);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(true);

              }
            else if (titre.compare("equipements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(true);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);

                ui->pushButton_7->setEnabled(false);
                ui->login_pushButton_6->setEnabled(true);
                ui->BTmenu_EmpoyepushButton->setEnabled(false);
                ui->Abonnement_pushButton->setEnabled(false);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(true);


              }
            else if (titre.compare("abonnements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(true);
                ui->evenementsPushButton->setEnabled(false);

                ui->pushButton_7->setEnabled(false);
                ui->login_pushButton_6->setEnabled(false);
                ui->BTmenu_EmpoyepushButton->setEnabled(false);
                ui->Abonnement_pushButton->setEnabled(true);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(true);


              }
            else if (titre.compare("evenements")==0)
              {
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(true);

                ui->pushButton_7->setEnabled(false);
                ui->login_pushButton_6->setEnabled(false);
                ui->BTmenu_EmpoyepushButton->setEnabled(false);
                ui->Abonnement_pushButton->setEnabled(true);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(true);

              }
            else{
                ui->employesPushButton->setEnabled(false);
                ui->equipementsPushButton->setEnabled(false);
                ui->clientPushButton->setEnabled(false);
                ui->abonnementPushButton->setEnabled(false);
                ui->evenementsPushButton->setEnabled(false);

                ui->pushButton_7->setEnabled(false);
                ui->login_pushButton_6->setEnabled(false);
                ui->BTmenu_EmpoyepushButton->setEnabled(false);
                ui->Abonnement_pushButton->setEnabled(false);
                ui->pushButton_10->setEnabled(false);
                ui->menu_pushButton->setEnabled(false);

                }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            // Vérification des valeurs récupérées
            qDebug() << "Nom récupéré :" << NOM;
            qDebug() << "Prénom récupéré :" << PRENOM;
            ui->userStatusLabel->setText("utilisateur: "+NOM+" "+PRENOM+"");

        }
        else
        {        ui->frame_3->setVisible(false);
                 ui->loginInfoLabel->setText("iditenfiants incorrectes!");
        }
    }
   else
       {
           qDebug() << "Erreur lors de l'exécution de la requête SQL:" << query.lastError().text();
           // Traitez ici l'erreur de requête, par exemple, affichez un message d'erreur ou enregistrez la journalisation.
       }
    ui->loginEmailLineEdit->clear();
    ui->passwordLineEdit->clear();
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

void MainWindow::on_pushButton_clicked()
{
     int CIN = ui->updateCin_LE->text().toInt();
     Employes e;
     if(e.rechercher(CIN))
     {
          ui->updateNom_LE->setText(e.getNom());
          ui->updatePrenom_LE->setText(e.getPrenom());
          ui->updateAdresse_LE->setText(e.getAdresse());
          ui->updateGenre_LE->setText(e.getGenre());
          ui->updateEmail_LE->setText(e.getEmail());
          ui->updateFonction_LE->setText(e.getFonction());
          ui->updateTelephone_LE->setText(QString::number(e.getTel()));
          ui->updateSalaire_LE->setText(QString::number(e.getSalaire()));

     }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    Employes e;
  if(ui->nomRadioButton->isChecked()==true)
  {
       e.chercherEmpCin(ui->listEmployetableView,arg1);
  }
   if (ui->CinRadioButton_2->isChecked()==true)
   {
       e.chercherEmpNom(ui->listEmployetableView,arg1);
   }
   if (ui->PhoneradioButton->isChecked()==true)
   {
       e.chercherEmpTel(ui->listEmployetableView,arg1);
   }

}

void MainWindow::on_PDFpushButton_clicked()
{
    // Demander à l'utilisateur de choisir l'emplacement et le nom du fichier PDF
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer le PDF"), "", tr("Fichiers PDF (*.pdf)"));

    // Si l'utilisateur annule la sélection, quitter la fonction
    if (filePath.isEmpty()) {
        return;
    }

    // Création d'un objet QPrinter + configuration pour avoir un fichier PDF
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Créatoin d'un objet QPainter pour l'objet QPrinter
    QPainter painter;
    if (!painter.begin(&printer)) {
        qWarning("Failed to open file, is it writable?");
        return;
    }

    // Obtenir le modèle de la table à partir de la QTableView
    QAbstractItemModel *model = ui->listEmployetableView->model();

    // Obtenir les dimensions de la table
    int rows = model->rowCount();
    int columns = model->columnCount();

    // Définissez la taille de la cellule pour le dessin
    int cellWidth = 100;
    int cellHeight = 30;

    // Insérer les noms des colonnes
    for (int col = 0; col < columns; ++col) {
        QString headerData = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(col * cellWidth, 0, cellWidth, cellHeight, Qt::AlignCenter, headerData);
    }

    // Insérer les données de la table sur le périphérique de sortie PDF
    for (int row = 1; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            // Obtenir les données de la cellule
            QModelIndex index = model->index(row, col);
            QString data = model->data(index).toString();

            // Insérer les données de la cellule
            painter.drawText(col * cellWidth, row * cellHeight, cellWidth, cellHeight, Qt::AlignLeft, data);
        }
    }

    // Terminez avec QPainter
    painter.end();
}

void MainWindow::on_importCSV_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir fichier CSV"), QString(), tr("Fichiers CSV (*.csv)"));
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier."));
        return;
    }

    QTextStream in(&file);
    bool firstLine = true; // Indicateur pour la première ligne

    try {
        while (!in.atEnd()) {
            QString line = in.readLine();

            // Si c'est la première ligne, passer à la suivante
            if(firstLine) {
                firstLine = false;
                continue;
            }

            QStringList fields = line.split(';');

            if (fields.size() < 9) {
                // Afficher un avertissement ou gérer le cas où la ligne ne contient pas suffisamment de champs
                qDebug() << "La ligne CSV ne contient pas suffisamment de champs";
                continue; // Passer à la prochaine ligne
            }

            // Créer un objet Employes avec les données lues depuis le fichier CSV
            Employes employee;
            employee.setCin(fields[0].toInt());
            employee.setNom(fields[1]);
            employee.setPrenom(fields[2]);
            employee.setGenre(fields[3]);
            employee.setTel(fields[4].toInt());
            employee.setEmail(fields[5]);
            employee.setAdresse(fields[6]);
            employee.setFonction(fields[7]);
            employee.setSalaire(fields[8].toFloat()); // Convertir en float

            // Ajouter l'employé à la base de données
            if (!employee.ajouter()) {
                QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ajouter l'employé à la base de données."));
                return;
            }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Erreur"), tr("Une erreur s'est produite lors de l'importation du fichier CSV : %1").arg(e.what()));
    }

    file.close();
    QMessageBox::information(this, tr("Succès"), tr("Données ajoutées avec succès à la base de données."));
}


void MainWindow::on_statGenderPushButton_clicked() {
    QChartView *chartView ;
    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0;
    q1.prepare("SELECT * FROM EMPLOYES");
    q1.exec();
    q2.prepare("SELECT * FROM EMPLOYES WHERE GENRE='homme'");
    q2.exec();
    q3.prepare("SELECT * FROM EMPLOYES WHERE GENRE='femme'");
    q3.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    c1 = c1 / tot;
    c2 = c2 / tot;

    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("homme (" + QString::number(c1 * 100, 'f', 2) + "%)", c1);
    QPieSlice *slice2 = series->append("femme (" + QString::number(c2 * 100, 'f', 2) + "%)", c2);

    slice1->setLabelVisible(true);
    slice2->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart, ui->Employe_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);
    chartView->show();
}



void MainWindow::on_statSalaryPushButton_clicked()
{
    QChartView *chartView;
    QSqlQuery q1, q2, q3, q4;
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0;
    q1.prepare("SELECT * FROM EMPLOYES");
    q1.exec();
    q2.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=1000");
    q2.exec();
    q3.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=2000");
    q3.exec();
    q4.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=1500");
    q4.exec();
    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }
    while (q4.next()) { c3++; }
    c1 = c1 / tot;
    c2 = c2 / tot;
    c3 = c3 / tot;

    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("1000 (" + QString::number(c1 * 100, 'f', 2) + "%)", c1);
    QPieSlice *slice2 = series->append("2000 (" + QString::number(c2 * 100, 'f', 2) + "%)", c2);
    QPieSlice *slice3 = series->append("1500 (" + QString::number(c3 * 100, 'f', 2) + "%)", c3);

    slice1->setLabelVisible(true);
    slice2->setLabelVisible(true);
    slice3->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart, ui->Employe_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);
    chartView->show();
}



void MainWindow::on_statFonctionPushButton_clicked()
{
    QChartView *chartView;
    QSqlQuery q1, q2, q3, q4, q5, q6;
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
    q1.prepare("SELECT * FROM EMPLOYES");
    q1.exec();
    q2.prepare("SELECT * FROM EMPLOYES WHERE FONCTION='employes'");
    q2.exec();
    q3.prepare("SELECT * FROM EMPLOYES WHERE FONCTION='clients'");
    q3.exec();
    q4.prepare("SELECT * FROM EMPLOYES WHERE FONCTION='abonnements'");
    q4.exec();
    q5.prepare("SELECT * FROM EMPLOYES WHERE FONCTION='evenements'");
    q5.exec();
    q6.prepare("SELECT * FROM EMPLOYES WHERE FONCTION='equipements'");
    q6.exec();
    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }
    while (q4.next()) { c3++; }
    while (q5.next()) { c4++; }
    while (q6.next()) { c5++; }
    c1 = c1 / tot;
    c2 = c2 / tot;
    c3 = c3 / tot;
    c4 = c4 / tot;
    c5 = c5 / tot;

    // meilleure choix des couleurs
    QStringList colors;
    colors << "#ff0000" << "#00ff00" << "#ffff00" << "#ff00ff" << "#0000ff"; // Rouge, Vert, Jaune, Violet, Bleu

    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("employes (" + QString::number(c1 * 100, 'f', 2) + "%)", c1);
    QPieSlice *slice2 = series->append("clients (" + QString::number(c2 * 100, 'f', 2) + "%)", c2);
    QPieSlice *slice3 = series->append("abonnements (" + QString::number(c3 * 100, 'f', 2) + "%)", c3);
    QPieSlice *slice4 = series->append("evenements (" + QString::number(c4 * 100, 'f', 2) + "%)", c4);
    QPieSlice *slice5 = series->append("equipements (" + QString::number(c5 * 100, 'f', 2) + "%)", c5);

    slice1->setLabelVisible(true);
    slice2->setLabelVisible(true);
    slice3->setLabelVisible(true);
    slice4->setLabelVisible(true);
    slice5->setLabelVisible(true);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);

    // Appliquer les couleurs aux tranches du graphique
    QList<QPieSlice *> slices = series->slices();
    for (int i = 0; i < slices.size(); ++i) {
       slices.at(i)->setBrush(QColor(colors[i % colors.size()]));
    }

    chartView = new QChartView(chart, ui->Employe_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);
    chartView->show();
}



void MainWindow::on_AjouterButton_clicked() {
  int CIN = ui->ACIN->text().toInt();
  QString nom = ui->ANom->text();
  QString prenom = ui->APrenom->text();
  QDate date_naissance = ui->AdateEdit->date();
  qDebug() << date_naissance;
  int genre = ui->FradioButton->isChecked()
                  ? 1
                  : (ui->MradioButton->isChecked() ? 0 : -1);
  int tel = ui->ATel->text().toInt();
  QString email = ui->AEmail->text();
  //(int CIN, QString nom, QString prenom, QDate date_naissance,
  // int genre, int tel, QString email)
  Client NC(CIN, nom, prenom, date_naissance, genre, tel, email);
  if (NC.Ajouter()) {
    // ui->listClientsView->setModel(NC.afficher());
    ui->ACIN->clear();
    ui->ANom->clear();
    ui->APrenom->clear();
    ui->AdateEdit->clear();
    ui->FradioButton->setChecked(false);
    ui->MradioButton->setChecked(false);
    ui->ATel->clear();
    ui->AEmail->clear();
    qDebug() << "Ajout reussi";
    // Write message to label
  }
}

void MainWindow::on_DeleteClientBtn_clicked() {
  int CIN = ui->CINtoDelete->text().toInt();
  Client C;
  C.setCIN(CIN);
  C.Supprimer();
  ui->CINtoDelete->clear();
  C.Afficher();
}

void MainWindow::on_ShowAllClients_clicked() {}

// Abonnements
void MainWindow::on_add_abonnement_push_clicked()
{
    QString id_abnt = ui->ref_abonnement->text();
    QString activity = ui->activity_abonnement->currentText();
    QString membre = ui->number_abonnement->text();
    QString cin = ui->cin_abonnement->text();
    QString price = ui->price_abonnement->text();
    QString duration = ui->duration_abonnement->currentText();
    Abonement abonnement(id_abnt, activity, membre, cin, price, duration);

    if (!price.isEmpty() && !cin.isEmpty())
    {
        if (cin.size() == 8 && valid_id(cin) && id_abnt.size() == 8 && valid_id(id_abnt))
        {
            if ( valid_id(membre) &&  valid_id(price))
            {
            bool ajoutReussi = abonnement.ajouter();
            if (ajoutReussi)
            {
                QMessageBox::information(this, "Ajout réussi", "Le Abonement a été ajouté avec succès.");
                ui->table_abonnement->setModel(abonnement.afficher_abonnement());
                ui->table_abonnement_2->setModel(abonnement.afficher_abonnement());
            }
            else
            {
                QMessageBox::critical(this, "Erreur d'ajout", "Une erreur est survenue lors de l'ajout du Abonement.");
            }
            }
            else
            {
                QMessageBox::warning(this, "price or number invalide", "Le price et number doit contenir exactement des caractères numériques.");
            }
        }
        else
        {
            QMessageBox::warning(this, "CIN or id_abnt invalide", "Le CIN et id_abnt doit contenir exactement 8 caractères numériques.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le prix et le CIN.");
    }
}


void MainWindow::on_delete_abonnement_button_clicked()
{
    QString id = ui->delete_abonnement_field->text();
    Abonement Abonement;
               bool test=supp.supprimer_abonnement(id);
                if(test)
                {
                     QMessageBox::information(nullptr, QObject::tr("Supprimer ABONEMENT"),
                                             QObject::tr("Le ABONEMENT HAS BEEN DELETED SUCCESSFULLY.\n"
                                                         "CLICK OK TO EXIST."), QMessageBox::Ok);
                      }
                          else
                    {
                    QMessageBox::information(nullptr, QObject::tr("DELETE ABONEMENTs"),
                                          QObject::tr("Le ABONEMENT HASN'T BEEN DELETED.\n"
                                                    "CLICK OK TO EXIST."), QMessageBox::Ok);
                    }
           ui->table_abonnement->setModel(Abonement.afficher_abonnement());
           ui->table_abonnement_2->setModel(Abonement.afficher_abonnement());

}

void MainWindow::on_aupdate_abnt_clicked()
{
    QString id_abnt = ui->ref_update_abnt->text();
    QString activity =ui->activity_update_abnt->currentText();
    QString membre = ui->number_update_abnt->text();
    QString cin = ui->idclient_update_abnt->text();
    QString price = ui->price_update_abnt->text();
    QString duration = ui->comboBox_3->currentText();
    Abonement Abonement(id_abnt, activity, membre, cin,price,duration);
        bool test = Abonement.modifier(id_abnt);
                if (test)
               {
                   QMessageBox::information(this, "Modification réussie", "Les informations du Abonement ont été modifiées avec succès.");
                   ui->table_abonnement->setModel(Abonement.afficher_abonnement());
                   ui->table_abonnement_2 ->setModel(Abonement.afficher_abonnement());

               }
               else
               {
                   QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification du Abonement.");
               }
}

void MainWindow::on_refreshTableV_3_clicked()
{
    ui->table_abonnement->setModel(display.afficher_abonnement());
    ui->table_abonnement_2 ->setModel(display.afficher_abonnement());
}


void MainWindow::on_pushButton_7_clicked()
{
    // Bouton pour rediriger vers CLIENTS
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_BTmenu_EmpoyepushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Abonnement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_menu_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_login_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_10_clicked()
{
   ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pb_logOut_clicked()
{

    // Envoyer un signal à l'Arduino pour afficher le message "Au revoir"
        /*QByteArray goodbyeSignal;
        goodbyeSignal.append('3'); // Signal de déconnexion
        A.write_to_arduino(goodbyeSignal);*/



    ui->frame_3->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);


}


