#include "mainwindow.h"
#include "abonement.h"
#include "client.h"
#include "employes.h"
#include "equipement.h"
#include "ui_mainwindow.h"
#include <QAbstractItemModel>
#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTableView>
#include <QUrl>
#include <QImage>
#include <QPageSize>
#include <QSqlRecord>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  Employes e(0, "", "", "", 0, "", "", "", 0);
  Client c;
  ui->listEmployetableView->setModel(e.afficher());
  ui->table_abonnement->setModel(display.afficher_abonnement());
  ui->table_abonnement_2->setModel(display.afficher_abonnement());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_3_clicked() {
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

  Employes e(CIN, nom, prenom, genre, telephone, email, adresse, fonction,
             salaire);
  // e.ajouter();
  bool test = e.ajouter();
  if (test) {
    QMessageBox::information(this, "Succès",
                             "L'employé a été ajouté avec succès.");
    ui->listEmployetableView->setModel(e.afficher());

  } else {
    QMessageBox::critical(this, "Erreur",
                          "employé existant. Veuillez réessayer.");
  }
}

void MainWindow::on_refreshTableV_clicked() {
  Employes e(0, "", "", "", 0, "", "", "", 0);

  ui->listEmployetableView->setModel(e.afficher());
}

void MainWindow::on_deletePushButton_clicked() {
  Employes e;
  e.setCin(ui->cinDlineEdit->text().toInt());
  bool test = e.supprimer(e.getcin());
  if (test) {
    ui->listEmployetableView->setModel(e.afficher());
  }
}

void MainWindow::on_updatePushButton_clicked() {
  int CIN = ui->updateCin_LE->text().toInt();
  QString nom = ui->updateNom_LE->text();
  QString prenom = ui->updatePrenom_LE->text();
  QString adresse = ui->updateAdresse_LE->text();
  QString genre = ui->updateGenre_LE->text();
  QString email = ui->updateEmail_LE->text();
  QString fonction = ui->updateFonction_LE->text();
  int telephone = ui->updateTelephone_LE->text().toInt();
  int salaire = ui->updateSalaire_LE->text().toInt();
  Employes e(CIN, nom, prenom, genre, telephone, email, adresse, fonction,
             salaire);
  e.modifier();
  bool test = e.modifier();
  if (test) {
    ui->listEmployetableView->setModel(e.afficher());
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
}

void MainWindow::on_triCinPushButton_clicked() {
  Employes e;
  ui->listEmployetableView->setModel(e.triCin());
}

void MainWindow::on_triNomPushButton_clicked() {
  Employes e;
  ui->listEmployetableView->setModel(e.triNom());
}

void MainWindow::on_loginPushButton_clicked() {
  QString EMAIL = ui->loginEmailLineEdit->text();
  QString CIN = ui->passwordLineEdit->text();
  qDebug() << "email récupéré :" << EMAIL;
  qDebug() << "cin récupéré :" << CIN;
  QSqlQuery query;
  QString titre;
  query.prepare("SELECT * FROM EMPLOYES WHERE EMAIL = :EMAIL AND CIN = :CIN");
  query.bindValue(":EMAIL", EMAIL);
  query.bindValue(":CIN", CIN);
  if (query.exec()) {
    if (query.next()) {
      ui->stackedWidget->setCurrentIndex(1);
      titre = query.value(7).toString();
      qDebug() << "fonction récupéré :" << titre;

      if (titre.compare("admin") == 0) {
        ui->employesPushButton->setEnabled(true);
        ui->equipementsPushButton->setEnabled(true);
        ui->clientPushButton->setEnabled(true);
        ui->abonnementPushButton->setEnabled(true);
        ui->evenementsPushButton->setEnabled(true);
      }
      if (titre.compare("employes") == 0) {
        ui->employesPushButton->setEnabled(true);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);
      }
      if (titre.compare("clients") == 0) {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(true);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);
      }
      if (titre.compare("equipements") == 0) {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(true);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(false);
      }
      if (titre.compare("abonnements") == 0) {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(true);
        ui->evenementsPushButton->setEnabled(false);
      }
      if (titre.compare("evenements") == 0) {
        ui->employesPushButton->setEnabled(false);
        ui->equipementsPushButton->setEnabled(false);
        ui->clientPushButton->setEnabled(false);
        ui->abonnementPushButton->setEnabled(false);
        ui->evenementsPushButton->setEnabled(true);
      }
      QString NOM = query.value(1).toString();
      QString PRENOM = query.value(2).toString();
      // Vérification des valeurs récupérées
      qDebug() << "Nom récupéré :" << NOM;
      qDebug() << "Prénom récupéré :" << PRENOM;
      ui->userStatusLabel->setText("utilisateur: " + NOM + " " + PRENOM + "");

    } else {
      ui->loginInfoLabel->setText("iditenfiants incorrectes!");
    }
  } else {
    qDebug() << "Erreur lors de l'exécution de la requête SQL:"
             << query.lastError().text();
    // Traitez ici l'erreur de requête, par exemple, affichez un message
    // d'erreur ou enregistrez la journalisation.
  }
}

void MainWindow::on_employesPushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_clientPushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_equipementsPushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_evenementsPushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_abonnementPushButton_clicked() {
  ui->stackedWidget->setCurrentIndex(6);
}

int modes = 0;
void MainWindow::on_showHidepushButton_clicked() {
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

void MainWindow::on_pushButton_clicked() {
  int CIN = ui->updateCin_LE->text().toInt();
  Employes e;
  if (e.rechercher(CIN)) {
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

void MainWindow::on_lineEdit_textChanged(const QString &arg1) {
  Employes e;
  if (ui->nomRadioButton->isChecked() == true) {
    e.chercherEmpCin(ui->listEmployetableView, arg1);
  }
  if (ui->CinRadioButton_2->isChecked() == true) {
    e.chercherEmpNom(ui->listEmployetableView, arg1);
  }
}

void MainWindow::on_PDFpushButton_clicked() {
  // Création d'un objet QPrinter + configuration pour avoir un fichier PDF
  QPrinter printer;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName("C:/Users/chihe/Desktop/deuxieme annee "
                            "esprit/s2/projet nautique/listeEmployes.pdf");

  // Créatoin d'un objet QPainter pour l'objet QPrinter
  QPainter painter;
  if (!painter.begin(&printer)) {
    qWarning("failed to open file, is it writable?");
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

  // Inserer les noms des colonnes
  for (int col = 0; col < columns; ++col) {
    QString headerData = model->headerData(col, Qt::Horizontal).toString();
    painter.drawText(col * cellWidth, 0, cellWidth, cellHeight, Qt::AlignCenter,
                     headerData);
  }
  // Inserer les données de la table sur le périphérique de sortie PDF
  for (int row = 1; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      // Obtenir les données de la cellule
      QModelIndex index = model->index(row, col);
      QString data = model->data(index).toString();

      // insertion des données de la cellule
      painter.drawText(col * cellWidth, row * cellHeight, cellWidth, cellHeight,
                       Qt::AlignLeft, data);
    }
  }

  // Terminez avec QPainter
  painter.end();
}

void MainWindow::on_statGenderPushButton_clicked() {
  QChartView *chartView;
  QSqlQuery q1, q2, q3;
  qreal tot = 0, c1 = 0, c2 = 0;
  q1.prepare("SELECT * FROM EMPLOYES");
  q1.exec();
  q2.prepare("SELECT * FROM EMPLOYES WHERE GENRE='homme'");
  q2.exec();
  q3.prepare("SELECT * FROM EMPLOYES WHERE GENRE='femme'");
  q3.exec();

  while (q1.next()) {
    tot++;
  }
  while (q2.next()) {
    c1++;
  }
  while (q3.next()) {
    c2++;
  }

  c1 = c1 / tot;
  c2 = c2 / tot;
  QPieSeries *series = new QPieSeries(); // morceau mta camembere
  series->append("homme", c1);
  series->append("femme", c2);

  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->legend()->show();
  chart->setAnimationOptions(QChart::AllAnimations);
  chart->setTheme(QChart::ChartThemeQt);
  chartView = new QChartView(chart, ui->Employe_label_Stats);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setMinimumSize(570, 570);
  chartView->show();
}

void MainWindow::on_statSalaryPushButton_clicked() {
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
  while (q1.next()) {
    tot++;
  }
  while (q2.next()) {
    c1++;
  }
  while (q3.next()) {
    c2++;
  }
  while (q4.next()) {
    c3++;
  }
  c1 = c1 / tot;
  c2 = c2 / tot;
  c3 = c3 / tot;
  QPieSeries *series = new QPieSeries();
  series->append("1000", c1);
  series->append("2000", c2);
  series->append("1500", c3);
  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->legend()->show();
  chart->setAnimationOptions(QChart::AllAnimations);
  chart->setTheme(QChart::ChartThemeQt);
  chartView = new QChartView(chart, ui->Employe_label_Stats);
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setMinimumSize(570, 570);
  chartView->show();
}

void MainWindow::on_statFonctionPushButton_clicked() {
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
  while (q1.next()) {
    tot++;
  }
  while (q2.next()) {
    c1++;
  }
  while (q3.next()) {
    c2++;
  }
  while (q4.next()) {
    c3++;
  }
  while (q5.next()) {
    c4++;
  }
  while (q6.next()) {
    c5++;
  }
  c1 = c1 / tot;
  c2 = c2 / tot;
  c3 = c3 / tot;
  c4 = c4 / tot;
  c5 = c5 / tot;

  // meilleure choix des couleurs
  QStringList colors;
  colors << "#ff0000"
         << "#00ff00"
         << "#ffff00"
         << "#ff00ff"
         << "#0000ff"; // Rouge, Vert, Jaune, Violet, Bleu

  QPieSeries *series = new QPieSeries();
  series->append("employes", c1);
  series->append("clients", c2);
  series->append("abonnements", c3);
  series->append("evenements", c4);
  series->append("equipements", c5);

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
  ui->AllClientsModel->setModel(C.Afficher());
}

void MainWindow::on_AjouterButton_2_clicked() {
  QString reference = ui->reference->text();
  int prix = ui->prix->text().toInt();
  int nombre = ui->nombre->text().toInt();
  QString fonctionalite = ui->fonctionalite->text();
  QString type = ui->type_2->text();
  QString etat = ui->etat->text();
  Equipements E(reference, prix, nombre, fonctionalite, type, etat);

  if (E.ajouter()) {
    qDebug() << "Ajout reussi";
  }
}

void MainWindow::on_AjouterButton_3_clicked() {
  QString reference = ui->REFtoDelete->text();
  Equipements E;
  E.setReference(reference);
  E.supprimer();
  ui->REFtoDelete->clear();
  E.afficher();
}

void MainWindow::on_AjouterButton_4_clicked() {
  Equipements E;
  QSqlQueryModel *EquipementModel = E.afficher();
  qDebug() << EquipementModel;
  if (EquipementModel == nullptr) {
    qDebug() << "nullptr" << endl;
  }
  ui->tableView_3->setModel(EquipementModel);
}

void MainWindow::on_ShowAllClients_clicked() {
  Client C;
  ui->AllClientsModel->setModel(C.Afficher());
}

void MainWindow::on_SearchCIN_textChanged(const QString &searchedText) {
  Client C;
  QAbstractItemModel *ClientModel = C.RechercherEtAfficher(searchedText);
  if (ClientModel == nullptr) {
    qDebug() << "nullptr" << endl;
  }
  ui->OneClientModel->setModel(ClientModel);
}

void MainWindow::on_UpdateClientBtn_clicked() {
  int CIN = ui->UCIN->text().toInt();
  QString nom = ui->UNom->text();
  QString prenom = ui->UPrenom->text();
  QDate date_naissance = ui->UDateEdit->date();
  qDebug() << date_naissance;
  int genre = ui->UFradioButton->isChecked()
                  ? 1
                  : (ui->UMradioButton->isChecked() ? 0 : -1);
  int tel = ui->UTel->text().toInt();
  QString email = ui->UEmail->text();
  //(int CIN, QString nom, QString prenom, QDate date_naissance,
  // int genre, int tel, QString email)
  Client NC(CIN, nom, prenom, date_naissance, genre, tel, email);
  if (NC.Modifier()) {
    // ui->listClientsView->setModel(NC.afficher());
    ui->UCIN->clear();
    ui->UNom->clear();
    ui->UPrenom->clear();
    ui->UDateEdit->clear();
    ui->UFradioButton->setChecked(false);
    ui->UMradioButton->setChecked(false);
    ui->UTel->clear();
    ui->UEmail->clear();
    qDebug() << "Ajout reussi";
    // Write message to label
  }
}

void MainWindow::on_TrierParButton_clicked() {
  Client C;
  QString critere = ui->CINradioButton->isChecked()      ? "CIN"
                    : ui->NOMradioButton->isChecked()    ? "NOM"
                    : ui->PRENOMradioButton->isChecked() ? "PRENOM"
                    : ui->DATE_NAISSANCEradioButton->isChecked()
                        ? "DATE_NAISSANCE"
                    : ui->GENDERradioButton->isChecked() ? "GENRE"
                    : ui->PHONEradioButton->isChecked()  ? "TELEPHONE"
                    : ui->EMAILradioButton->isChecked()  ? "EMAIL"
                                                         : "";

  QAbstractItemModel *sortedModel = C.TriPar(critere);
  if (sortedModel == nullptr) {
    qDebug() << "nullptr" << endl;
  }
  ui->AllClientsModel->setModel(sortedModel);
}

void MainWindow::on_CRefStat_clicked() {
  Client C;
  vector<int> Stat = C.Statistics();
  qDebug() << Stat;
  int numClients = Stat[0];
  int numMales = Stat[1];
  int numFemales = Stat[2];
  int avgAge = Stat[3];

  const int barSpacing = 40;

  QGraphicsScene *scene = new QGraphicsScene(this);

  QGraphicsRectItem *clientsBar = scene->addRect(0, 0, numClients * 5, 20);
  QGraphicsRectItem *malesBar = scene->addRect(0, barSpacing, numMales * 5, 20);
  QGraphicsRectItem *femalesBar =
      scene->addRect(0, 2 * barSpacing, numFemales * 5, 20);
  QGraphicsRectItem *avgAgeBar =
      scene->addRect(0, 3 * barSpacing, avgAge * 2, 20);

  clientsBar->setBrush(Qt::blue);
  malesBar->setBrush(Qt::green);
  femalesBar->setBrush(Qt::red);
  avgAgeBar->setBrush(Qt::yellow);

  QGraphicsTextItem *clientsLabel =
      scene->addText(QString("Number of Clients: %1").arg(numClients));
  clientsLabel->setPos(numClients * 5 + 10, 0);

  QGraphicsTextItem *malesLabel =
      scene->addText(QString("Number of Males: %1").arg(numMales));
  malesLabel->setPos(numMales * 5 + 10, barSpacing);

  QGraphicsTextItem *femalesLabel =
      scene->addText(QString("Number of Females: %1").arg(numFemales));
  femalesLabel->setPos(numFemales * 5 + 10, 2 * barSpacing);

  QGraphicsTextItem *avgAgeLabel =
      scene->addText(QString("Average Age: %1").arg(avgAge));
  avgAgeLabel->setPos(avgAge * 2 + 10, 3 * barSpacing);

  QGraphicsView *view = new QGraphicsView(scene);

  QVBoxLayout *layout = new QVBoxLayout(ui->CStatFrame);
  layout->addWidget(view);
}

void MainWindow::on_CPDFExport_clicked() {
  Client C;
  QSqlQueryModel *ClientModel = C.Afficher();

  QString defaultFileName = "ClientsList.pdf";
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save PDF", defaultFileName, "PDF Files (*.pdf)");

  if (fileName.isEmpty() || !ClientModel)
    return;

  QPrinter printer;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName(fileName);

  QTextDocument doc;
  QTextCursor cursor(&doc);

  int rowCount = ClientModel->rowCount();
  int colCount = ClientModel->columnCount();

  QTextTable *table = cursor.insertTable(rowCount + 1, colCount);

  for (int col = 0; col < colCount; ++col) {
    QString columnName =
        ClientModel->headerData(col, Qt::Horizontal).toString();
    QTextTableCell cell = table->cellAt(0, col);
    QTextCursor cellCursor = cell.firstCursorPosition();
    cellCursor.insertText(columnName);
  }

  for (int row = 0; row < rowCount; ++row) {
    for (int col = 0; col < colCount; ++col) {
      QModelIndex index = ClientModel->index(row, col);
      QString data;
      if (col == 4) {
        int genderValue = ClientModel->data(index).toInt();
        data = (genderValue == 0) ? "M" : "F";
      } else {
        data = ClientModel->data(index).toString();
      }
      QTextTableCell cell = table->cellAt(row + 1, col);
      QTextCursor cellCursor = cell.firstCursorPosition();
      cellCursor.insertText(data);
    }
  }

  QTextTableFormat tableFormat = table->format();
  tableFormat.setBorder(1);
  table->setFormat(tableFormat);

  doc.print(&printer);
}
bool valid_id(QString id) {
  for (int i = 0; i < id.length(); i++) {
    if ((id[i] >= '0' && id[i] <= '9')) {

    } else {
      return false;
    }
  }
  return true;
}

void MainWindow::on_add_abonnement_push_clicked() {
  QString id_abnt = ui->ref_abonnement->text();
  QString activity = ui->activity_abonnement->currentText();
  QString membre = ui->number_abonnement->text();
  QString cin = ui->cin_abonnement->text();
  QString price = ui->price_abonnement->text();
  QString duration = ui->duration_abonnement->currentText();
  Abonement abonnement(id_abnt, activity, membre, cin, price, duration);

  if (!price.isEmpty() && !cin.isEmpty()) {
    if (cin.size() == 8 && valid_id(cin) && id_abnt.size() == 8 &&
        valid_id(id_abnt)) {
      if (valid_id(membre) && valid_id(price)) {
        bool ajoutReussi = abonnement.ajouter();
        if (ajoutReussi) {
          QMessageBox::information(this, "Ajout réussi",
                                   "Le Abonement a été ajouté avec succès.");
          ui->table_abonnement->setModel(abonnement.afficher_abonnement());
          ui->table_abonnement_2->setModel(abonnement.afficher_abonnement());
        } else {
          QMessageBox::critical(
              this, "Erreur d'ajout",
              "Une erreur est survenue lors de l'ajout du Abonement.");
        }
      } else {
        QMessageBox::warning(this, "price or number invalide",
                             "Le price et number doit contenir exactement des "
                             "caractères numériques.");
      }
    } else {
      QMessageBox::warning(this, "CIN or id_abnt invalide",
                           "Le CIN et id_abnt doit contenir exactement 8 "
                           "caractères numériques.");
    }
  } else {
    QMessageBox::warning(this, "Données manquantes",
                         "Veuillez entrer le prix et le CIN.");
  }
}

void MainWindow::on_delete_abonnement_button_clicked() {
  QString id = ui->delete_abonnement_field->text();
  Abonement Abonement;
  bool test = supp.supprimer_abonnement(id);
  if (test) {
    QMessageBox::information(
        nullptr, QObject::tr("Supprimer ABONEMENT"),
        QObject::tr("Le ABONEMENT HAS BEEN DELETED SUCCESSFULLY.\n"
                    "CLICK OK TO EXIST."),
        QMessageBox::Ok);
  } else {
    QMessageBox::information(nullptr, QObject::tr("DELETE ABONEMENTs"),
                             QObject::tr("Le ABONEMENT HASN'T BEEN DELETED.\n"
                                         "CLICK OK TO EXIST."),
                             QMessageBox::Ok);
  }
  ui->table_abonnement->setModel(Abonement.afficher_abonnement());
  ui->table_abonnement_2->setModel(Abonement.afficher_abonnement());
}

void MainWindow::on_aupdate_abnt_clicked() {
  QString id_abnt = ui->ref_update_abnt->text();
  QString activity = ui->activity_update_abnt->currentText();
  QString membre = ui->number_update_abnt->text();
  QString cin = ui->idclient_update_abnt->text();
  QString price = ui->price_update_abnt->text();
  QString duration = ui->comboBox_3->currentText();
  Abonement Abonement(id_abnt, activity, membre, cin, price, duration);
  bool test = Abonement.modifier(id_abnt);
  if (test) {
    QMessageBox::information(
        this, "Modification réussie",
        "Les informations du Abonement ont été modifiées avec succès.");
    ui->table_abonnement->setModel(Abonement.afficher_abonnement());
    ui->table_abonnement_2->setModel(Abonement.afficher_abonnement());

  } else {
    QMessageBox::critical(
        this, "Erreur de modification",
        "Une erreur est survenue lors de la modification du Abonement.");
  }
}

void MainWindow::on_refreshTableV_3_clicked() {
  ui->table_abonnement->setModel(display.afficher_abonnement());
  ui->table_abonnement_2->setModel(display.afficher_abonnement());
}

void MainWindow::on_SearchClientUpdateButton_clicked() {
  Client CTU;
  if (!ui->UCIN->text().isEmpty()) {
    int CIN = ui->UCIN->text().toInt();
    CTU = CTU.RechercheClient(CIN);
  }
  ui->UCIN->setText(QString::number(CTU.getCIN(), 'f', 0));
  ui->UNom->setText(CTU.getNom());
  ui->UPrenom->setText(CTU.getPrenom());

  QDate birthDate = CTU.getDateNaissance();
  ui->UDateEdit->setDate(birthDate);

  if (CTU.getGenre() == 1) {
    ui->UFradioButton->setChecked(true);
  } else if (CTU.getGenre() == 0) {
    ui->UMradioButton->setChecked(true);
  }

  ui->UTel->setText(QString::number(CTU.getTel(), 'f', 0));
  ui->UEmail->setText(CTU.getEmail());
}

void MainWindow::on_AjouterButton_5_clicked()
{
    QString reference = ui->updateCin_LE_2->text();
    QString fonctionalite = ui->reference_7->text();
    int prix = ui->reference_9->text().toInt();
    QString type = ui->reference_4->text();
    int nombre = ui->reference_8->text().toInt();
    QString etat = ui->reference_2->text();
    Equipements E(reference, prix, nombre, fonctionalite, type, etat);
    E.modifier();
    bool test = E.modifier();
    if (test) {
      ui->tableView_3->setModel(E.afficher());
      ui->updateCin_LE_2->clear();
      ui->reference_7->clear();
      ui->reference_9->clear();
      ui->reference_4->clear();
      ui->reference_8->clear();
      ui->reference_2->clear();
    }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    Equipements E;
     if (ui->nomRadioButton_2->isChecked() == true) {
       E.chercherEquipRef(ui->tableView_3, arg1);
     }
     if (ui->nomRadioButton_3->isChecked() == true) {
       E.chercherEquipType(ui->tableView_3, arg1);
     }
     if (ui->nomRadioButton_4->isChecked() == true) {
       E.chercherEquipEtat(ui->tableView_3, arg1);
     }
}

void MainWindow::on_triCinPushButton_2_clicked()
{
    Equipements E;
      ui->tableView_3->setModel(E.triRef());
}

void MainWindow::on_triCinPushButton_3_clicked()
{
    Equipements E;
      ui->tableView_3->setModel(E.triType());
}

void MainWindow::on_triCinPushButton_4_clicked()
{
    Equipements E;
      ui->tableView_3->setModel(E.triEtat());
}

void MainWindow::on_PDFpushButton_2_clicked()
{
    Equipements E;
     QSqlQueryModel *model = E.afficher();
    // Création d'un objet QPrinter + configuration pour avoir un fichier PDF
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString defaultFileName = "EquipmentList.pdf";
    QString fileName = QFileDialog::getSaveFileName(
          this, "Save PDF", defaultFileName, "PDF Files (*.pdf)");

    // Création d'un objet QPainter pour l'objet QPrinter
    if (fileName.isEmpty() || !model)
        return;
    QPainter painter;
    printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setOutputFileName(fileName);
      if (!painter.begin(&printer))
        {
          qWarning("failed to open file, is it writable?");
          return;
        }

    // Obtenir les dimensions de la table
    int rows = model->rowCount();
    int columns = model->columnCount();

    // Définir la taille de la cellule pour le dessin
    int cellWidth = 100;
    int cellHeight = 30;

    // Calculer les dimensions de la page
    int pageWidth = printer.pageRect().width();
    int pageHeight = printer.pageRect().height();

    // Dessiner les lignes de la table
    painter.drawRect(0, 0, columns * cellWidth, (rows + 1) * cellHeight);
    for (int row = 1; row < rows + 1; ++row) {
        painter.drawLine(0, row * cellHeight, columns * cellWidth, row * cellHeight);
    }
    for (int col = 1; col < columns; ++col) {
        painter.drawLine(col * cellWidth, 0, col * cellWidth, (rows + 1) * cellHeight);
    }

    // Dessiner les en-têtes de colonnes
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    for (int col = 0; col < columns; ++col) {
        QModelIndex index = model->index(0, col);
        QString headerData = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(col * cellWidth, 0, cellWidth, cellHeight,
                         Qt::AlignCenter, headerData);
    }

    // Dessiner les données de la table sur le périphérique de sortie PDF
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            // Obtenir les données de la cellule
            QModelIndex index = model->index(row, col);
            QString data = model->data(index).toString();

            // Dessiner les données de la cellule
            painter.drawText(col * cellWidth, (row + 1) * cellHeight, cellWidth, cellHeight,
                             Qt::AlignLeft | Qt::AlignVCenter, data);
        }
    }

    // Dessiner l'image au centre de la page
    QImage image("C:/youssef/NauticaLogo.png");
    if (!image.isNull()) {
        int imageWidth = image.width();
        int imageHeight = image.height();
        int x = (pageWidth - imageWidth) / 2;
        int y = (pageHeight - imageHeight) / 2;
        painter.drawImage(x, y, image);
    } else {
        qWarning("Failed to load image");
    }

    // Terminer avec QPainter
    painter.end();
}

void MainWindow::on_statTypePushButton_2_clicked()
{
    QChartView *chartView = new QChartView(ui->Equipement_label_Stats); // Chart view created with parent
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);

    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0;

    // Execute queries
    q1.exec("SELECT COUNT(*) FROM EQUIPEMENT");
    q2.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE TYPE='sport'");
    q3.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE TYPE='help'");

    // Fetch total count
    if (q1.next())
        tot = q1.value(0).toInt();

    // Fetch counts for each type
    if (q2.next())
        c1 = q2.value(0).toInt();

    if (q3.next())
        c2 = q3.value(0).toInt();

    // Calculate proportions
    if (tot != 0) {
        c1 = c1 / tot;
        c2 = c2 / tot;
    }

    // Create pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("sport", c1);
    QPieSlice *slice2 = series->append("help", c2);
    series->setHoleSize(0.5); // Set hole size for doughnut chart (0.5 means half size of the chart)

    // Set labels as slice name and percentage
    slice1->setLabel(QString("%1: %2%").arg(slice1->label()).arg(c1 * 100));
    slice2->setLabel(QString("%1: %2%").arg(slice2->label()).arg(c2 * 100));

    // Set colors for slices
    slice1->setBrush(QColor("#7D3C98")); // Red color
    slice2->setBrush(QColor("#239B56")); // Blue color

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeLight); // Disable the theme

    // Set chart for chart view
    chartView->setChart(chart);
    chartView->show();
}

void MainWindow::on_StatEtatPushButton_clicked()
{
    QChartView *chartView = new QChartView(ui->Equipement_label_Stats); // Chart view created with parent
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);

    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0;

    // Execute queries
    q1.exec("SELECT COUNT(*) FROM EQUIPEMENT");
    q2.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE ETAT='bien'");
    q3.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE ETAT='mauvais'");

    // Fetch total count
    if (q1.next())
        tot = q1.value(0).toInt();

    // Fetch counts for each type
    if (q2.next())
        c1 = q2.value(0).toInt();

    if (q3.next())
        c2 = q3.value(0).toInt();

    // Calculate proportions
    if (tot != 0) {
        c1 = c1 / tot;
        c2 = c2 / tot;
    }

    // Create pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("bien", c1);
    QPieSlice *slice2 = series->append("mauvais", c2);
    series->setHoleSize(0.5); // Set hole size for doughnut chart (0.5 means half size of the chart)

    // Set labels as slice name and percentage
    slice1->setLabel(QString("%1: %2%").arg(slice1->label()).arg(c1 * 100));
    slice2->setLabel(QString("%1: %2%").arg(slice2->label()).arg(c2 * 100));

    // Set colors for slices
    slice1->setBrush(QColor("#F44336")); // Red color
    slice2->setBrush(QColor("#2196F3")); // Blue color

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeLight); // Disable the theme

    // Set chart for chart view
    chartView->setChart(chart);
    chartView->show();
}

void MainWindow::on_statPrixPushButton_clicked()
{
    QChartView *chartView = new QChartView(ui->Equipement_label_Stats); // Chart view created with parent
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570, 570);

    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0;

    // Execute queries
    q1.exec("SELECT COUNT(*) FROM EQUIPEMENT");
    q2.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE PRIX < 200");
    q3.exec("SELECT COUNT(*) FROM EQUIPEMENT WHERE PRIX BETWEEN 200 AND 500");

    // Fetch total count
    if (q1.next())
        tot = q1.value(0).toInt();

    // Fetch counts for each category
    if (q2.next())
        c1 = q2.value(0).toInt();

    if (q3.next())
        c2 = q3.value(0).toInt();

    c3 = tot - c1 - c2; // Calculate count for "Over 500" slice

    // Calculate proportions
    if (tot != 0) {
        c1 = c1 / tot;
        c2 = c2 / tot;
        c3 = c3 / tot;
    }

    // Create pie series
    QPieSeries *series = new QPieSeries();
    QPieSlice *slice1 = series->append("Under 200", c1);
    QPieSlice *slice2 = series->append("Between 200 and 500", c2);
    QPieSlice *slice3 = series->append("Over 500", c3);
    series->setHoleSize(0.5); // Set hole size for doughnut chart (0.5 means half size of the chart)

    // Set labels as slice name and percentage
    slice1->setLabel(QString("%1: %2%").arg(slice1->label()).arg(c1 * 100));
    slice2->setLabel(QString("%1: %2%").arg(slice2->label()).arg(c2 * 100));
    slice3->setLabel(QString("%1: %2%").arg(slice3->label()).arg(c3 * 100));

    // Set colors for slices
    slice1->setBrush(QColor("#F44336")); // Red color
    slice2->setBrush(QColor("#2196F3")); // Blue color
    slice3->setBrush(QColor("#4CAF50")); // Green color

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeLight); // Disable the theme

    // Set chart for chart view
    chartView->setChart(chart);
    chartView->show();
}

QList<QStringList> MainWindow::retrieveAvailableEquipment(const QString &dateString) {
    QList<QStringList> availableEquipment; // QList of QStringList to store equipment details

    // Get the existing database connection
    QSqlDatabase db = QSqlDatabase::database(); // Assuming the connection is already established

    // Check if the database connection is valid and open
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "Database connection is invalid or not open";
        return availableEquipment;
    }

    // Prepare the SQL query to retrieve available equipment details
    QSqlQuery query(db); // Pass the database connection to the query
    QString sqlQuery = "SELECT * FROM equipement WHERE etat = 'bien' "
                       "AND reference NOT IN (SELECT reference_equipement FROM maintenance WHERE :date BETWEEN date_debut AND date_fin)";
    query.prepare(sqlQuery);
    query.bindValue(":date", dateString);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return availableEquipment;
    }

    // Process the query results
    while (query.next()) {
        QStringList equipmentDetails;
        for (int i = 0; i < query.record().count(); ++i) {
            equipmentDetails << query.value(i).toString(); // Append each column value to the QStringList
        }
        availableEquipment << equipmentDetails; // Append the QStringList to the QList
    }

    // Return the list of available equipment details
    return availableEquipment;
}

void MainWindow::displayEquipmentDetails(const QList<QStringList> &availableEquipment) {
    // Clear existing content in the table widget
    ui->equipmentDetailsTableWidget->clearContents();
    ui->equipmentDetailsTableWidget->setRowCount(0); // Clear all rows

    // Set column headers
    QStringList headers = {"Reference", "Price", "Number", "State", "Functionality", "Type"};
    ui->equipmentDetailsTableWidget->setColumnCount(headers.size());
    ui->equipmentDetailsTableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table widget with available equipment details
    int row = 0;
    for (const QStringList &equipmentDetails : availableEquipment) {
        if (equipmentDetails.size() != headers.size()) {
            // Skip if the number of details doesn't match the number of columns
            continue;
        }
        ui->equipmentDetailsTableWidget->insertRow(row);
        for (int column = 0; column < headers.size(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(equipmentDetails.at(column));
            ui->equipmentDetailsTableWidget->setItem(row, column, item);
        }
        ++row;
    }
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    // Retrieve available equipment for the selected date
    QList<QStringList> availableEquipment = retrieveAvailableEquipment(date.toString("yyyy-MM-dd"));

    // Display available equipment details
    displayEquipmentDetails(availableEquipment);
}

void MainWindow::on_AjouterButton_6_clicked()
{
    float CIN_employe = ui->CIN_employe->text().toFloat();
    QString reference_equipement = ui->reference_equipement->text();
    QDate date_debut = ui->date_debut->date(); // Adjust the format according to your input
    QDate date_fin = ui->date_fin->date(); // Adjust the format according to your input
    float prix_maintenance = ui->type_2->text().toFloat(); // Assuming this should be a float
    QString etat = ui->etat->text();

    maintenance M(CIN_employe, reference_equipement, date_debut, date_fin, prix_maintenance);

    if (M.ajouter()) {
        qDebug()<< "Ajout réussi";
    }
}

