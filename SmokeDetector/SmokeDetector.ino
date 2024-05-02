#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial sim800l(10, 11); // RX, TX

const int MAX_SENSOR_VALUE = 1023;

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);
  lcd.init();
  lcd.backlight();
  sendPIN("0000");
}

void loop() {
  int rawSmokeValue = analogRead(A1);
  float smokeValue = (rawSmokeValue / (float)MAX_SENSOR_VALUE) * 100.0;

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.setCursor(0, 1);
  if (smokeValue > 10.0) {
    Serial.println("Smoke Detected");
    sendSMS("54450598", "Smoke Detected");
    lcd.print("Smoke Detected");
  } else {
    Serial.println("No Smoke Detected");
    lcd.print("No Smoke Detected");
  }

  delay(1000);
}

void sendSMS(String phoneNumber, String message) {
  Serial.println("Setting SMS mode...");
  sim800l.println("AT+CMGF=1");
  delay(1000);

  char okStr[] = "OK";
  if (sim800l.find(okStr)) {
    Serial.println("SMS mode set.");
  } else {
    Serial.println("Error setting SMS mode.");
    return;
  }

  Serial.println("Sending SMS...");
  char phoneNumberArray[phoneNumber.length() + 1];
  phoneNumber.toCharArray(phoneNumberArray, phoneNumber.length() + 1);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumberArray);
  sim800l.print("\"\r");
  delay(1000);

  char greaterThanStr[] = ">";
  if (sim800l.find(greaterThanStr)) {
    Serial.println("Recipient set.");
  } else {
    Serial.println("Error setting recipient.");
    return;
  }

  char messageArray[message.length() + 1];
  message.toCharArray(messageArray, message.length() + 1);
  sim800l.print(messageArray);
  sim800l.write(26);
  delay(1000);

  Serial.println("SMS Sent!");
}

void sendPIN(String pin) {
  Serial.println("Setting PIN...");
  sim800l.print("AT+CPIN=");
  sim800l.println(pin);
  delay(1000);

  char okStr[] = "OK";
  if (sim800l.find(okStr)) {
    Serial.println("PIN set successfully.");
  } else {
    Serial.println("Error setting PIN.");
  }
}
