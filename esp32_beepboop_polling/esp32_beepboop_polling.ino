#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define PIN 14
#define BTN 12

#define BOOP_DURATION 800

WiFiClient wifiClient;

volatile static bool beeptheboop = false;

void beepboopISR() {
  beeptheboop = true;
}

void setup()
{
  pinMode(PIN, INPUT);
  pinMode(BTN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BTN), beepboopISR, FALLING);

  // Setup stuff
  Serial.begin(115200);

  // Print MAC Address
  Serial.print("\n\nMAC Address (Add me to CMU-DEVICE): ");
  Serial.println(WiFi.macAddress());

  // Try the fallback WiFi first
  Serial.println("Trying fallback...");
  WiFi.begin("BeepNetBoopNet", "BeepBoopPass6666");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {

    // Connect to CMU
    Serial.println("Trying CMU...");
    WiFi.begin("CMU-DEVICE");
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      Serial.println("WiFi Failed! Rebooting...");
      delay(1000);
      ESP.restart();
    }
  }
}

void loop()
{
  if (beeptheboop) {
    beeptheboop = false;
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
    Serial.println("boop");
    delay(BOOP_DURATION);
    pinMode(PIN, INPUT);
  } else {
    HTTPClient http;
    http.setTimeout(2500);
    String s = "https://beepboop.andrew.cmu.edu/api/state";
    http.begin(wifiClient, s.c_str());

    int httpResponseCode = http.GET();
    
    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.print("HTTP success ");
      Serial.println(payload);
      if (payload.toInt() == 1) {
        pinMode(PIN, OUTPUT);
        digitalWrite(PIN, LOW);
        Serial.println("boop");
        delay(BOOP_DURATION);
        pinMode(PIN, INPUT);
      }
    }
    else {
      Serial.print("Error with HTTP: ");
      Serial.println(httpResponseCode);
    }
  }

  delay(1000);
}
