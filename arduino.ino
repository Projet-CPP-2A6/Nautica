#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED  2 // The pin the LED is connected to

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // initialise les broches
String nom1;
char data;

bool lecture=false;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

byte nuidPICC[4];

unsigned long previousMillis = 0; // variable to store the previous time
const unsigned long interval = 2000; // interval for stopping RFID card reading in milliseconds, 2000 seconds

void setup() {
  // put your setup code here, to run once:
 
  SPI.begin();
  rfid.PCD_Init();

  pinMode(5, OUTPUT);
  digitalWrite(5,LOW);
  pinMode(LED, OUTPUT); // Declare the LED as an output
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Bienvenue ");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Check if the elapsed time since the last RFID card reading is greater than the interval
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // If the elapsed time is greater than the interval, stop reading RFID card
    lecture = false;
  }

  if (lecture == false) {
    if (!rfid.PICC_IsNewCardPresent())
      return;

    // Check for the presence of a new RFID card
    if (!rfid.PICC_ReadCardSerial())
      return;

    for (byte i=0; i<4; i++){
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    for (byte i=0; i<4; i++){
      Serial.print(nuidPICC[i], HEX);
    }
 
    lecture = true;
    previousMillis = currentMillis; // Update the previousMillis variable with the current time
  }

  if (Serial.available())
  {
    data = Serial.read();
    nom1 = Serial.readString();
    if (data == '1'){  
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Bienvenue");
      lcd.setCursor(1,1);
      lcd.print(nom1);
      digitalWrite(5,HIGH); // activate the buzzer
      digitalWrite(LED, HIGH);  // turn on the LED
      delay(500);              // delay of 3000 milliseconds = 3s
      digitalWrite(5,LOW); // deactivate the buzzer
      digitalWrite(LED, LOW);   // turn off the LED
    } else if (data == '2'){
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("introuvable");
      digitalWrite(5,HIGH);
      delay(500);
      digitalWrite(5,LOW);
      delay(500);
      digitalWrite(5,HIGH);
      delay(500);
      digitalWrite(5,LOW);
      lcd.clear();
    }
  }
}
