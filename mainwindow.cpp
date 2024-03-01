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
#include <QDesktopServices>
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
}

void MainWindow::on_PDFpushButton_clicked()
{
    // Créez un objet QPrinter et configurez-le pour générer un fichier PDF
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/Users/chihe/Desktop/deuxieme annee esprit/s2/projet nautique/listeEmployes.pdf");

    // Créez un objet QPainter associé à l'objet QPrinter
    QPainter painter;
    if (!painter.begin(&printer)) {
        qWarning("failed to open file, is it writable?");
        return;
    }

    // Obtenez le modèle de la table à partir de la QTableView
    QAbstractItemModel *model = ui->listEmployetableView->model();

    // Obtenez les dimensions de la table
    int rows = model->rowCount();
    int columns = model->columnCount();


    // Définissez la taille de la cellule pour le dessin
    int cellWidth = 100;
    int cellHeight = 30;

    // Dessinez les noms des colonnes
      for (int col = 0; col < columns; ++col) {
          QString headerData = model->headerData(col, Qt::Horizontal).toString();
          painter.drawText(col * cellWidth, 0, cellWidth, cellHeight, Qt::AlignCenter, headerData);
      }
    // Dessinez les données de la table sur le périphérique de sortie PDF
    for (int row = 1; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            // Obtenez les données de la cellule
            QModelIndex index = model->index(row, col);
            QString data = model->data(index).toString();

            // Dessinez les données de la cellule
            painter.drawText(col * cellWidth, row * cellHeight, cellWidth, cellHeight, Qt::AlignLeft, data);
        }
    }

    // Terminez le dessin avec QPainter
    painter.end();


}



void MainWindow::on_statGenderPushButton_clicked()
{
    QChartView *chartView ;
       QSqlQuery q1,q2,q3,q4;
       qreal tot=0,c1=0,c2=0/*,c3=0*/;
       q1.prepare("SELECT * FROM EMPLOYES");
       q1.exec();
       q2.prepare("SELECT * FROM EMPLOYES WHERE GENRE='homme'");
       q2.exec();
       q3.prepare("SELECT * FROM EMPLOYES WHERE GENRE='femme'");
       q3.exec();
       /*q4.prepare("SELECT * FROM EMPLOYES WHERE GENRE='Autre'");
       q4.exec();*/
       while (q1.next()){tot++;}
       while (q2.next()){c1++;}
       while (q3.next()){c2++;}
       /*while (q4.next()){c3++;}*/
       c1=c1/tot; c2=c2/tot; /*c3=c3/tot*/;
       QPieSeries *series = new QPieSeries();
       series->append("homme",c1);
       series->append("femme",c2);
       /*series->append("Autre",c3)*/;
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->legend()->show();
       chart->setAnimationOptions(QChart::AllAnimations);
       chart->setTheme(QChart::ChartThemeQt);
       chartView = new QChartView(chart,ui->Employe_label_Stats);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(570,570);
       chartView->show();
}

void MainWindow::on_statSalaryPushButton_clicked()
{
    QChartView *chartView ;
       QSqlQuery q1,q2,q3,q4;
       qreal tot=0,c1=0,c2=0,c3=0;
       q1.prepare("SELECT * FROM EMPLOYES");
       q1.exec();
       q2.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=1000");
       q2.exec();
       q3.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=2000");
       q3.exec();
       q4.prepare("SELECT * FROM EMPLOYES WHERE SALAIRE=1500");
       q4.exec();
       while (q1.next()){tot++;}
       while (q2.next()){c1++;}
       while (q3.next()){c2++;}
       while (q4.next()){c3++;}
       c1=c1/tot; c2=c2/tot; c3=c3/tot;
       QPieSeries *series = new QPieSeries();
       series->append("1000",c1);
       series->append("2000",c2);
       series->append("1500",c3);
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->legend()->show();
       chart->setAnimationOptions(QChart::AllAnimations);
       chart->setTheme(QChart::ChartThemeQt);
       chartView = new QChartView(chart,ui->Employe_label_Stats);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->setMinimumSize(570,570);
       chartView->show();
}

void MainWindow::on_statFonctionPushButton_clicked()
{
    QChartView *chartView ;
    QSqlQuery q1,q2,q3,q4,q5,q6;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;
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
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}
    while (q6.next()){c5++;}
    c1=c1/tot; c2=c2/tot; c3=c3/tot; c4=c4/tot; c5=c5/tot;

    // Définissez les couleurs que vous souhaitez utiliser
    QStringList colors;
    colors << "#ff0000" << "#00ff00" << "#ffff00" << "#ff00ff" << "#0000ff"; // Rouge, Vert, Jaune, Violet, Bleu

    QPieSeries *series = new QPieSeries();
    series->append("employes",c1);
    series->append("clients",c2);
    series->append("abonnements",c3);
    series->append("evenements",c4);
    series->append("equipements",c5);

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


