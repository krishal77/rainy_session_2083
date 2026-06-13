#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-LED";
const char* password = "12345678";

WebServer server(80);

const int ledPin = 2;  

// HTML page
String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; }
    button { padding: 15px 30px; font-size: 20px; margin: 10px; }
  </style>
</head>
<body>
  <h1>ESP32 LED Control</h1>
  <a href="/on"><button style="background-color:green;color:white;">ON</button></a>
  <a href="/off"><button style="background-color:red;color:white;">OFF</button></a>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", page);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", page);
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.softAP(ssid, password);

  Serial.println("WiFi AP started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); // usually 192.168.4.1

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}