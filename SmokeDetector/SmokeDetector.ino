#include <Arduino.h>
#include <Wire.h> // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial sim800lSerial(10, 11); // RX, TX for SIM800L
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Address 0x27, 16 columns, 2 rows

const int SMOKE_SENSOR_PIN = A1;
const int BUZZER_PIN = 3;
const float SMOKE_THRESHOLD = 10.0;
const char* DEFAULT_PHONE_NUMBER = "+21654450598";

void setup() {
  Serial.begin(9600);
  sim800lSerial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("System Initialized.");
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
    Serial.println("1");
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.print("Smoke Detected");
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    waitForQtSMS();
  } else {
    Serial.println("0");
    digitalWrite(BUZZER_PIN, LOW);
    lcd.print("No Smoke Detected");
  }

  delay(1000);
}

float readSmokeLevel() {
  int sensorValue = analogRead(SMOKE_SENSOR_PIN);
  float level = (sensorValue / 1023.0) * 100.0;
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  return level;
}

void waitForQtSMS() {
  String receivedData;
  while (!receivedData.startsWith("QT_SMS:")) {
    if (sim800lSerial.available()) {
      receivedData = sim800lSerial.readStringUntil('\n');
      receivedData.trim();
    }
    delay(500);
  }

  String phoneNumberList = receivedData.substring(7); // Extract phone numbers
  sendSMS(phoneNumberList);
}

void sendSMS(const String& phoneNumberList) {
  String message = "Smoke detected!";
  Serial.println("Sending SMS to numbers from Qt...");

  int startIndex = 0;
  while (startIndex < phoneNumberList.length()) {
    int commaIndex = phoneNumberList.indexOf(',', startIndex);
    String phoneNumber;
    if (commaIndex == -1) {
      phoneNumber = phoneNumberList.substring(startIndex);
    } else {
      phoneNumber = phoneNumberList.substring(startIndex, commaIndex);
    }

    if (isValidPhoneNumber(phoneNumber)) {
      sendSMS(phoneNumber, message);
    }

    if (commaIndex == -1) {
      break;
    } else {
      startIndex = commaIndex + 1;
    }
  }
}

bool isValidPhoneNumber(const String& phoneNumber) {
  // Implement your validation logic here
  return phoneNumber.length() > 0; // Basic validation: non-empty
}

void sendSMS(const String& phoneNumber, const String& message) {
  Serial.println("Sending SMS...");
  sim800lSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  sim800lSerial.print("AT+CMGS=\"");
  sim800lSerial.print(phoneNumber);
  sim800lSerial.println("\"");
  delay(1000);
  sim800lSerial.print(message);
  sim800lSerial.println((char)26); // End AT command with Ctrl+Z
  delay(1000);

  // Clear the input buffer
  while (sim800lSerial.available()) {
    sim800lSerial.read();
  }

  // Wait for response
  delay(500);
  String response = sim800lSerial.readString();
  Serial.println(response);

  // Check if the response contains "OK"
  if(response.indexOf("OK") != -1) {
    Serial.println("SMS Sent successfully.");
  } else {
    Serial.println("Failed to send SMS.");
  }
}
