#include <WiFi.h>
#include <HTTPClient.h>
#include "score.h"

// Replace with your network credentials
const char* ssid = "moaiwlan";
const char* password = "Ossi1Paavo234";

// Replace with the server URL
const char* serverName = "https://www.hh3dlab.fi/hello/log_messages.php";

// Define the team name
String teamName = "Plonki the Digital Pet";

// Call this in your setup() to connect WiFi
void connectWiFi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

// Call this when the pet dies, passing the lifetime in seconds
void sendPetLifetime(unsigned long seconds) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "team=" + teamName + "&message1=" + String(seconds) + " seconds";
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server Response:");
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}