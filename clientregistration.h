#ifndef CLIENTREGISTRATION_H
#define CLIENTREGISTRATION_H

#include <QWidget>

namespace Ui
{
    class clientRegistration;
}

class clientRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit clientRegistration(QWidget *parent = nullptr);
    ~clientRegistration();

private:
    Ui::clientRegistration *ui;
};

#endif // CLIENTREGISTRATION_H
