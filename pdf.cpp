#include "pdf.h"
#include "mainwindow.h"
#include "ui_pdf.h"
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>

pdf::pdf(QWidget *parent) : QDialog(parent), ui(new Ui::pdf) {
  ui->setupUi(this);
}

pdf::~pdf() { delete ui; }

void pdf::on_pushButton_clicked() // pdf //
{
  // Create PDF writer
  QPdfWriter pdf("C:/Users/chihe/Desktop/DETAILS.pdf");
  QPainter painter(&pdf);

  // Set up background image
  QImage backgroundImage("C:/Users/chihe/Desktop/Nautica/img/logo.png");
  if (backgroundImage.isNull()) {
    // Handle error loading background image
    qDebug() << "Failed to load background image.";
    return;
  }

  // Draw background image
  QRectF targetRect = QRectF(0, 0, pdf.width(), pdf.height());
  painter.drawImage(targetRect, backgroundImage, backgroundImage.rect());

  // Retrieve ID from line_edit
  QString id = ui->line_pdf->text();

  // Execute SQL query to check if ID exists
  QSqlQuery test;
  test.prepare("SELECT COUNT(*) from ABONNEMENT where ID_ABNT = :id");
  test.bindValue(":id", id);
  test.exec();

  // If ID exists
  if (test.next() && test.value(0).toInt() == 1) {
    // Execute SQL query to retrieve data
    QSqlQuery query;
    query.prepare("SELECT CIN, DURATION, MEMBRE, ACTIVITY, PRICE, ID_ABNT FROM "
                  "ABONNEMENT WHERE ID_ABNT = :id");
    query.bindValue(":id", id);
    query.exec();

    // If data is retrieved successfully
    if (query.next()) {
      QString ident = query.value(0).toString();
      QString nom = query.value(1).toString();
      QString prenom = query.value(2).toString();
      QString status = query.value(3).toString();
      QString phone = query.value(4).toString();
      QString mail = query.value(5).toString();

      // Set up text formatting
      painter.setPen(Qt::black);
      int yPos = 3000; // Initial Y position for text

      // Draw text content
      painter.drawText(3000, yPos, "CIN : " + ident);
      yPos += 200; // Increment Y position
      painter.drawText(3000, yPos, "DURATION : " + nom);
      yPos += 200;
      painter.drawText(3000, yPos, "MEMBRE : " + prenom);
      yPos += 200;
      painter.drawText(3000, yPos, "ACTIVITY : " + status);
      yPos += 200;
      painter.drawText(3000, yPos, "PRICE : " + phone);
      yPos += 200;
      painter.drawText(3000, yPos, "ID_ABNT : " + mail);

      // Inform user about successful PDF export
      QMessageBox::information(nullptr, QObject::tr("PDF DONE"),
                               QObject::tr("PDF exported successfully.\n"
                                           "Click Cancel to exit."),
                               QMessageBox::Cancel);
    }
  } else {
    // Inform user about failure to export PDF
    QMessageBox::critical(nullptr, QObject::tr("PDF NOT DONE"),
                          QObject::tr("Failed to export PDF.\n"
                                      "Click Cancel to exit."),
                          QMessageBox::Cancel);
  }
}
