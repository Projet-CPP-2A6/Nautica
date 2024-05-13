#include "smoke-detector.h"
#include <QSqlQuery>
#include <QStringList>
#include <QVariant> // Add this line

SmokeDetector::SmokeDetector() { smokeDetected = false; }

bool SmokeDetector::isSmokeDetected() { return smokeDetected; }

void SmokeDetector::setSmokeDetected(bool smokeDetected) {
  this->smokeDetected = smokeDetected;
}

QStringList SmokeDetector::getEmployeesPhoneNumber() {
  QStringList phoneNumbers;
  QSqlQuery query;
  query.prepare("SELECT PHONE_NUMBER FROM EMPLOYEES");
  query.exec();
  while (query.next()) {
    phoneNumbers.append(query.value(0).toString());
  }
  return phoneNumbers;
}

SmokeDetector::~SmokeDetector() {}
