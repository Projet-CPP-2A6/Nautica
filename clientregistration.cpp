#include "clientregistration.h"
#include "ui_clientregistration.h"

clientRegistration::clientRegistration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientRegistration)
{
    ui->setupUi(this);
}

clientRegistration::~clientRegistration()
{
    delete ui;
}
