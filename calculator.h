//
// Created by Bychin on 17.11.2017.
//

#ifndef calculator_H
#define calculator_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
class calculator;
}

class calculator : public QDialog {
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = 0);
    ~calculator();

    bool OnlyDigits();
    void SetDigits(bool);

private:
    Ui::calculator *ui;

    QWidget* defaultCalcWidget;
    QWidget* simpleCalcWidget;
    QWidget* complCalcWidget;
    QWidget* mainWidget;

    QGridLayout* defaultCalcLayout;
    QGridLayout* simpleCalcLayout;
    QGridLayout* complCalcLayout;
    QGridLayout* mainLayout;

    void CreateDefaultCalcWidget();
    void CreateSimpleCalcWidget();
    void CreateComplCalcWidget();

    void SpawnSimpleMode();
    void SpawnComplMode();

    bool digits_only = true;

public slots:
    void SwitchMode();

    void NumberClicked();
    void UnFnClicked();
    void BinFnClicked();
    void DotClicked();

    void ClearInput();
    void BackSpace();
    void Equals();
};

#endif // calculator_H
