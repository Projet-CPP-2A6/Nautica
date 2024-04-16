#include "accueil.h"
#include "ui_accueil.h"

accueil::accueil(QWidget *parent) : QDialog(parent), ui(new Ui::accueil) {
  ui->setupUi(this);
}

accueil::~accueil() { delete ui; }
