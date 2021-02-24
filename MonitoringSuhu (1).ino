#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
WidgetLCD lcd(V6);

#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 8
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "MW_kgI1A6oyT1e5kNGrJkymegMax4a4J";
char ssid[] = "isnask8"; // nama wifi kamu
char pass[] = "oke00000"; // password wifi kamu

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

BlynkTimer timer;

const int fanPin = 6;
int led = 3;

void setup() {
  Serial.begin(9600);  //komunikasi Serial dengan komputer
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);
  
  pinMode(led, OUTPUT);
  pinMode(fanPin, OUTPUT);

  lcd.clear();
  dht.begin(); //Komunikasi DHT dengan Arduino
}

void loop() {
  Blynk.run();
  
  float kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  float suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu

  if (isnan(kelembaban) || isnan(suhu) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } else {

    Blynk.virtualWrite(V0, suhu);
    Blynk.virtualWrite(V1, kelembaban);
    
    Blynk.virtualWrite(V6, suhu);
    lcd.print(0, 0, "Suhu: ");
    lcd.print(6, 0, suhu);
    lcd.print(10, 0, " °C");
    Blynk.virtualWrite(V6, kelembaban);
    lcd.print(0, 1, "Lembab: ");
    lcd.print(8, 1, kelembaban);
    lcd.print(12, 1, " %");

 Serial.print("kelembaban: ");
 Serial.print(kelembaban);
 Serial.print(" ");
 Serial.print("suhu: ");
 Serial.println(suhu);
  
    if ( suhu >= 28) {
      digitalWrite(led, HIGH);
      digitalWrite(fanPin, 0);
      }
    else {
       digitalWrite(led, LOW);
       digitalWrite(fanPin, 255);
      }
    delay(2000); //memberi jeda waktu baca selama 2 detik
    timer.run();
  }
}
