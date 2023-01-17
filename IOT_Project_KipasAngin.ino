#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT22 
#define FAN_PIN D2

WidgetLED FAN(V0);

char auth[] = "q_URao70sxi2Z3B6Y5H0lnzE7RWgCBcD";
char ssid[] = "The_IoT_Projects";
char pass[] = "Qwertyuiop";
float humDHT = 0;
float tempDHT = 0;
int Val=0;

DHT dht ( DHTPIN, DHTTYPE ) ;
void setup() {
Serial.begin(115200);
pinMode(FAN_PIN, OUTPUT);
digitalWrite(FAN_PIN, LOW);
Serial.println(F("DHTxx test!"));
dht.begin();
Blynk.begin( auth, ssid , pass );
}
BLYNK_WRITE(V3)
{
Val = param.asInt();
Serial.print(" Nilai Ambang : ");
Serial.println(Val);
Serial.println();
}
void loop() {
 Blynk.run();
 delay(2000);
 humDHT = dht.readHumidity();
 tempDHT = dht.readTemperature();

 if (isnan(humDHT) || isnan(tempDHT))
 {
 Serial.println("Gagal membaca sensor DHT!");
 return;
 }
 Serial.print(F("Temperature: "));
 Serial.print(tempDHT);
 Serial.print(F("°C "));
 Serial.println();
 Serial.print(F("Humidity: "));
 Serial.print(humDHT);
 Serial.print(F("%"));
 Serial.println();

 Serial.println("***********************");
 Serial.println();

 if (Val > tempDHT)
 {
 digitalWrite(FAN_PIN, HIGH);
 FAN.off();
}
 else {
 digitalWrite(FAN_PIN, LOW);
 FAN.on();
 }
 Blynk.virtualWrite(V1, tempDHT);
 Blynk.virtualWrite(V2, humDHT);
}
