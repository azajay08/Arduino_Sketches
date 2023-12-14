#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Wifi Name";
const char* password = "Wifi Password";

const int ledPin = D1;  // Define the pin connected to the LED

ESP8266WebServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/led", HTTP_GET, handleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleLED() {
  if (server.hasArg("command")) {
    String command = server.arg("command");
    if (command.equals("on")) {
      digitalWrite(ledPin, HIGH); // Turn the LED ON
      server.send(200, "text/plain", "LED turned on");
    } else if (command.equals("off")) {
      digitalWrite(ledPin, LOW); // Turn the LED OFF
      server.send(200, "text/plain", "LED turned off");
    } else {
      server.send(400, "text/plain", "Invalid command");
    }
  } else {
    server.send(400, "text/plain", "No command provided");
  }
}

