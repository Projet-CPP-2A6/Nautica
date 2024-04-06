
#include "pdf.h"
#include "mainwindow.h"
#include "pdf.h"
#include "ui_pdf.h"
#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QUrl>

pdf::pdf(QWidget *parent) : QDialog(parent), ui(new Ui::pdf) {
  ui->setupUi(this);
}

pdf::~pdf() { delete ui; }

void pdf::on_pushButton_clicked() // pdf //
{
  QPdfWriter pdf("C:/Users/zidio/Desktop/DETAILS.pdf");
  QPainter painter(&pdf);
  QString id = ui->line_pdf->text();
  QSqlQuery test;
  test.prepare("SELECT COUNT(*) from ABONNEMENT where ID_ABNT = :id");
  test.bindValue(":id", id);
  test.exec();
  if (test.next()) {
    if (test.value(0).toInt() == 1) {
      QSqlQuery query;
      query.prepare("select CIN , DURATION , MEMBRE , ACTIVITY , PRICE , "
                    "ID_ABNT from ABONNEMENT where ID_ABNT= :id");
      query.bindValue(":id", id);
      query.exec();
      if (query.next()) {
        QString ident = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString status = query.value(3).toString();
        QString phone = query.value(4).toString();
        QString mail = query.value(5).toString();

        painter.setPen(Qt::red);
        painter.drawText(600, 500, "CIN : ");
        painter.drawText(600, 700, "DURATION : ");
        painter.drawText(600, 900, "MEMBRE : ");
        painter.drawText(600, 1100, "ACTIVITY : ");
        painter.drawText(600, 1300, "PRICE: ");
        painter.drawText(600, 1500, "ID_ABNT : ");

        painter.setPen(Qt::black);
        painter.drawText(1500, 500, ident);
        painter.drawText(1500, 700, nom);
        painter.drawText(1500, 900, prenom);
        painter.drawText(1500, 1100, status);
        painter.drawText(1700, 1300, phone);
        painter.drawText(1500, 1500, mail);
        painter.end();
      }
      qDebug() << "PDF DONE";
    } else {
      qDebug() << "PDF NOT DONE";
    }
  }
}
