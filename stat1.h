#ifndef STAT1_H
#define STAT1_H

#include <QChartView>
#include <QDialog>
#include <QPieSeries>
#include <QPieSlice>
#include <QtCharts>

#include <QWidget>

namespace Ui {
class stat1;
}

class stat1 : public QDialog {
  Q_OBJECT

public:
  explicit stat1(QWidget *parent = nullptr);
  void make_activity();
  void make_duration();
  ~stat1();

private:
  Ui::stat1 *ui;
};

#endif // STAT1_H
