#include "stat1.h"
#include "abonement.h"
#include "ui_stat1.h"
#include <QString>
#include <qdebug.h>
#include <qsqlquery.h>
stat1::stat1(QWidget *parent) : QDialog(parent), ui(new Ui::stat1) {
  ui->setupUi(this);
}

stat1::~stat1() { delete ui; }
void stat1::make_duration() {
  qDebug() << "pst curva nord ";
  int total;
  int nat_tn;
  int nat_fr = 0;
  int nat_ang;
  int naaat;
  QString Nat_tn;
  QString Nat_fr;
  QString Nat_ang;
  QString Nat_naaat;
  QSqlQuery q;
  q.prepare(
      "SELECT COUNT(DURATION) FROM ABONNEMENT where DURATION ='1 mounth' ");
  q.exec();
  q.first();
  nat_tn = (q.value(0).toInt());
  q.prepare(
      "SELECT COUNT(DURATION) FROM ABONNEMENT where DURATION ='3 mounths' ");
  q.exec();
  q.first();
  nat_fr = (q.value(0).toInt());
  q.prepare(
      "SELECT COUNT(DURATION) FROM ABONNEMENT where DURATION ='9 mounths' ");
  q.exec();
  q.first();
  nat_ang = (q.value(0).toInt());
  q.prepare("SELECT COUNT(DURATION) FROM ABONNEMENT where DURATION ='1 year' ");
  q.exec();
  q.first();
  naaat = (q.value(0).toInt());
  q.prepare("SELECT COUNT(DURATION) FROM ABONNEMENT ");
  q.exec();
  q.first();
  total = (q.value(0).toInt());
  nat_fr = ((double)nat_fr / (double)total) * 100;
  nat_tn = ((double)nat_tn / (double)total) * 100;
  nat_ang = ((double)nat_ang / (double)total) * 100;
  naaat = 100 - (nat_fr + nat_tn + nat_ang);
  Nat_tn = QString::number(nat_tn);
  Nat_fr = QString::number(nat_fr);
  Nat_ang = QString::number(nat_ang);
  Nat_naaat = QString::number(naaat);
  QPieSeries *series;
  series = new QPieSeries();
  series->append("1 mounth  " + Nat_tn + "%", nat_tn);
  series->append("3 mounths  " + Nat_fr + "%", nat_fr);
  series->append("9 mounths  " + Nat_ang + "%", nat_ang);
  series->append("1 year  " + Nat_naaat + "%", naaat);
  QPieSlice *slice0 = series->slices().at(0);
  slice0->setLabelVisible();
  QPieSlice *slice1 = series->slices().at(1);
  slice1->setExploded();
  slice1->setLabelVisible();
  slice1->setPen(QPen(Qt::red, 2));
  slice1->setBrush(Qt::blue);
  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Abonnements Statistics");
  chart->legend()->show();
  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  ui->verticalLayout1->addWidget(chartView);
  qDebug() << "pst";
}
