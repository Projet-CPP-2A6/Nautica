#include "clientregistration.h"
#include "ui_clientregistration.h"

clientRegistration::clientRegistration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientRegistration)
{
    ui->setupUi(this);
}

clientRegistration::~clientRegistration()
{
    delete ui;
}
