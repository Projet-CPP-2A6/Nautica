#include "smoke-detector.h"

SmokeDetector::SmokeDetector() {
  smokeDetected = false;
}

bool SmokeDetector::isSmokeDetected() {
  return smokeDetected;
}

void SmokeDetector::setSmokeDetected(bool smokeDetected) {
  this->smokeDetected = smokeDetected;
}

SmokeDetector::~SmokeDetector() {}
