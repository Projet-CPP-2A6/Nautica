#include "connection.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  Connection c;
  bool test = c.createconnection();
  if (!test) {
    // Only popup and exit when there's an error
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                          QObject::tr("connection failed.\n"
                                      "Click Cancel to exit."),
                          QMessageBox::Cancel);

  } else {
    w.show();
  }

  return a.exec();
}
