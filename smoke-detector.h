#ifndef SMOKE_DETECTOR_H
#define SMOKE_DETECTOR_H
class SmokeDetector {

public:
  bool isSmokeDetected();
  void setSmokeDetected(bool smokeDetected);
  SmokeDetector();
  ~SmokeDetector();

private:
  bool smokeDetected;
};
#endif
