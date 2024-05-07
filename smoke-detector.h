#ifndef SMOKE_DETECTOR_H
#define SMOKE_DETECTOR_H
#include <QStringList>
class SmokeDetector {

public:
  bool isSmokeDetected();
  void setSmokeDetected(bool smokeDetected);
  QStringList getEmployeesPhoneNumber();
  SmokeDetector();
  ~SmokeDetector();

private:
  bool smokeDetected;
};
#endif
