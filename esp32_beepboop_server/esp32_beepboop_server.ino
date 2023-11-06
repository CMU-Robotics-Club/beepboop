#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define PIN 14
#define BTN 12

#define BOOP_DURATION 250

AsyncWebServer server(80);

volatile static uint32_t button_off_millis = 0;

void setup()
{
  pinMode(PIN, INPUT);
  pinMode(BTN, INPUT_PULLUP);

  // Setup stuff
  Serial.begin(115200);

  // Print MAC Address
  Serial.print("\n\nMAC Address (Add me to CMU-DEVICE): ");
  Serial.println(WiFi.macAddress());


  // Connect to WiFi
  WiFi.begin("CMU-DEVICE");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }


  // Main route
  server.on("/", [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", "bEeP boOP!!");
  });

  // API routes
  server.on("/boop", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    button_off_millis = millis() + BOOP_DURATION;

    request->send(200, "text/plain", "booping");
  });

  // Start server
  server.begin();

  // Print IP Address
  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to control the beep boop!");
}

void loop()
{
  static bool booped = false;

  if(digitalRead(BTN) == LOW) {
    button_off_millis = millis() + BOOP_DURATION;
  }

  if (button_off_millis > millis()) {
    if (!booped) {
      booped = true;
      pinMode(PIN, OUTPUT);
      digitalWrite(PIN, LOW);
      Serial.println("boop");
    }
  } else {
    if (booped) {
      booped = false;
      pinMode(PIN, INPUT);
      Serial.println("boop off");
    }
  }
}
