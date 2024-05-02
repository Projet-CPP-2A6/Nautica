#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// #define LED 2
// #define BUZZER 3
#define SENSOR A1

// Define maximum sensor value (corresponding to 100% gas concentration)
const int MAX_SENSOR_VALUE = 1023; // Maximum value for 10-bit ADC

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  // pinMode(LED, OUTPUT);
  // pinMode(BUZZER, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(SENSOR);
  float percentage = (sensorValue / (float)MAX_SENSOR_VALUE) * 100.0; // Calculate percentage

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.setCursor(0, 1);
  if (percentage > 10.0) { // Adjust threshold percentage based on your requirements
    Serial.println("1");
    // digitalWrite(BUZZER, HIGH);
    lcd.print("RUN BITCH RUN!!!");
  } else {
    Serial.println("0"); // Print "0" when no gas is detected
    // digitalWrite(BUZZER, LOW);
    lcd.print("we chill chief");
  }

  delay(1000); // Delay for stability and readability
}
