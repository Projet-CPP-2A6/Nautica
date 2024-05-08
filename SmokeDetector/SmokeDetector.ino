#include <Arduino.h>
#include <Wire.h> // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Address 0x27, 16 columns, 2 rows

const int SMOKE_SENSOR_PIN = A1;
const int BUZZER_PIN = 3;
const float SMOKE_THRESHOLD = 10.0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float smokeLevel = readSmokeLevel();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smoke Level: ");
  lcd.print(smokeLevel);
  lcd.println("%");

  bool smokeDetected = smokeLevel > SMOKE_THRESHOLD;

  if (smokeDetected) {
    Serial.println(1,DEC);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Smoke Detected");
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    Serial.println(0,DEC);
    /*digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(600);*/
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("No Smoke Detected");
  }

  delay(1000);
}

float readSmokeLevel() {
  int sensorValue = analogRead(SMOKE_SENSOR_PIN);
  float level = (sensorValue / 1023.0) * 100.0;
  return level;
}
