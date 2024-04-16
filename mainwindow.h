#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abonement.h"
#include <QLineSeries>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_3_clicked();
  void on_refreshTableV_clicked();
  void on_deletePushButton_clicked();
  void on_updatePushButton_clicked();
  void on_triCinPushButton_clicked();
  void on_triNomPushButton_clicked();
  void on_loginPushButton_clicked();
  void on_employesPushButton_clicked();
  void on_clientPushButton_clicked();
  void on_equipementsPushButton_clicked();
  void on_evenementsPushButton_clicked();
  void on_showHidepushButton_clicked();
  void on_pushButton_clicked();
  void on_lineEdit_textChanged(const QString &arg1);
  void on_PDFpushButton_clicked();
  void on_statGenderPushButton_clicked();
  void on_statSalaryPushButton_clicked();
  void on_statFonctionPushButton_clicked();
  void on_AjouterButton_clicked();
  void on_ShowAllClients_clicked();
  void on_DeleteClientBtn_clicked();
  void on_AjouterButton_2_clicked();
  void on_AjouterButton_3_clicked();
  void on_AjouterButton_4_clicked();
  void on_UpdateClientBtn_clicked();
  void on_TrierParButton_clicked();
  void on_CPDFExport_clicked();
  void on_add_abonnement_push_clicked();
  void on_delete_abonnement_button_clicked();
  void on_aupdate_abnt_clicked();
  void on_refreshTableV_3_clicked();
  void on_SearchClientUpdateButton_clicked();
  void on_AjouterButton_5_clicked();
  void on_lineEdit_2_textChanged(const QString &arg1);
  void on_triCinPushButton_2_clicked();
  void on_triCinPushButton_3_clicked();
  void on_triCinPushButton_4_clicked();
  void on_PDFpushButton_2_clicked();
  void on_statTypePushButton_2_clicked();
  void on_StatEtatPushButton_clicked();
  void on_statPrixPushButton_clicked();
  void on_ViewLogsButton_clicked();
  void on_TodayDateButton_clicked();
  void on_abonnementPushButton_clicked();
  void on_triSalaryPushButton_clicked();
  void on_importCSV_clicked();
  QList<QStringList> retrieveAvailableEquipment(const QString &dateString);
  void displayEquipmentDetails(const QList<QStringList> &availableEquipment);
  void on_calendarWidget_clicked(const QDate &date);
  void on_MenuPage_clicked();
  void on_SubscriptionsPage_clicked();
  void on_ClientsPage_clicked();
  void on_EventsPage_clicked();

  void on_EmployeesPage_clicked();

  void on_EquipmentsPage_clicked();

  void on_LogoutButton_clicked();
  void on_checkBoxsearchabnt_stateChanged();

  void on_pushButton_12_clicked();

  void on_radioButton_clicked();

  void on_radioButton_2_clicked();

  void on_radioButton_3_clicked();

  void on_checkBoxsearchabnt_2_stateChanged();

  void on_checkBoxsearchabnt_3_stateChanged();

  void on_pushButton_13_clicked();

  void on_b_note_clicked();

  void on_envoyer_email_clicked();

  void hideLabels();

  void on_SearchClient_clicked();

  void on_TodayButton_clicked();

  void on_SessionButton_clicked();

  void on_PerformanceStatsButton_clicked();
  void on_addMaintenance_clicked();

  void on_SearchByButton_clicked();

  void on_AgeStatButton_clicked();

  void on_GenderStatButton_clicked();

  void on_AgeStatExport_clicked();

  void on_GenderStatExport_clicked();

  void on_calculatorbutton_1_clicked();

  void on_calculatorbutton_2_clicked();

  void on_calculatorbutton_3_clicked();

  void on_calculatorbutton_4_clicked();

  void on_calculatorbutton_5_clicked();

  void on_calculatorbutton_6_clicked();

  void on_calculatorbutton_7_clicked();

  void on_calculatorbutton_8_clicked();

  void on_calculatorbutton_9_clicked();

  void on_calculatorbutton_0_clicked();

  void on_calculatorbutton_plus_clicked();

  void on_calculatorbutton_minus_clicked();

  void on_calculatorbutton_multiply_clicked();

  void on_calculatorbutton_divide_clicked();

  void on_calculatorbutton_clear_clicked();

  void on_calculatorbutton_equals_clicked();

  void on_calculatorref_clicked();

private:
  Ui::MainWindow *ui;
  Abonement supp;
  Abonement display;
};
#endif // MAINWINDOW_H
