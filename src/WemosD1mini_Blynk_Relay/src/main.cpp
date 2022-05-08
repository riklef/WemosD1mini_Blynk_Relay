#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <BlynkSimpleEsp8266.h>
#include <Credentials.h>

#define RELAY D2
#define BLYNK_PRINT Serial
WidgetTerminal terminal(V3);

const char* ssid = WIFI_SSID;
const char* password = WIFI_PW;

char auth[] = AUTH;

AsyncWebServer server(80);

BLYNK_WRITE(V2) {
  int virtual_pin_value = param.asInt();
  
  if (virtual_pin_value == 0)
  {
    digitalWrite(RELAY, LOW);
  }
  else if (virtual_pin_value == 1)
  {
    digitalWrite(RELAY, HIGH);
  }
  
  
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Blynk.begin(auth, ssid, password);
  terminal.clear();

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  terminal.print("Connected to ");
  terminal.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  terminal.print("IP address: ");
  terminal.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am LED Moon.");
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
  terminal.print("HTTP server started\n");
  terminal.println(" ");

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop(void) {
  Blynk.run();
  

}