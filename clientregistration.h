#ifndef CLIENTREGISTRATION_H
#define CLIENTREGISTRATION_H

#include <QDialog>

namespace Ui {
class clientRegistration;
}

class clientRegistration : public QDialog
{
    Q_OBJECT

public:
    explicit clientRegistration(QWidget *parent = nullptr);
    ~clientRegistration();

private:
    Ui::clientRegistration *ui;
};

#endif // CLIENTREGISTRATION_H
