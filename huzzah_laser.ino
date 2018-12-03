#include <ESP8266WiFi.h>
#include <WifiLocation.h>
#include "keys.h"

//SLACK CONFIG
char *slack_message[] = { "Donation received!", "Make it rain!",  "The pizza gods thank you!", "The money tree doth shake!", "InfraCoders stock on the rise!"};

// GOOGLE API CONFIG
WifiLocation location(googleApiKey);

// VARs
long randNumber;
int sensorPin = A0;
int rainbowPin = 14;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  randomSeed(analogRead(1));
  pinMode(rainbowPin, OUTPUT);
  digitalWrite(rainbowPin, LOW);

  // Connect to our wifi
  WiFi.begin(SSID, pwd);
  connectToWifi();

  // Determine location from Google API
  location_t loc = location.getGeoFromWiFi();

  // Location details
  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  Serial.println("Latitude: " + String(loc.lat, 7));
  Serial.println("Longitude: " + String(loc.lon, 7));
  Serial.println("Accuracy: " + String(loc.accuracy));

  // We are alive and accepting!
  bool ok = postMessageToSlack("I'm alive and accepting donations from: " + String(loc.lat, 7) + "," + String(loc.lon, 7));
  if (ok) {
    // Indicate we are online
    digitalWrite(rainbowPin, HIGH);
    delay(1000);
    digitalWrite(rainbowPin, LOW);
  }
}

void loop()
{
  // Recover from a network drop
  if (WiFi.status() != WL_CONNECTED)
  {
    connectToWifi();
  }
  
  // Loop and check if something swoops down
  int laser = analogRead(sensorPin);
  if (laser < 900)
  {
    // We detected movement!
    Serial.print("CA-CHING: ");
    Serial.println(laser);
    // Call out a donation
    bool ok = postMessageToSlack(slack_message[random(0,4)]);
    if (ok) {
      // In future, this will rainbow dance the LEDs
      digitalWrite(rainbowPin, HIGH);
    }
    delay(3000);
  }

  // Turn off rainbows!
  digitalWrite(rainbowPin, LOW);

  delay(50);
}

bool connectToWifi()
{
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    // wait 5 seconds for connection:
    Serial.print("Status = ");
    Serial.println(WiFi.status());
    delay(500);
  }

  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

bool postMessageToSlack(String msg)
{
  const char* host = "hooks.slack.com";
  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpsPort = 443;
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed :-(");
    return false;
  }

  // We now create a URI for the request

  Serial.print("Posting to URL: ");
  Serial.println(slack_hook_url);

  String postData="payload={\"link_names\": 1, \"text\": \"" + msg + "\"}";

  // This will send the request to the server
  client.print(String("POST ") + slack_hook_url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Connection: close" + "\r\n" +
               "Content-Length:" + postData.length() + "\r\n" +
               "\r\n" + postData);
  Serial.println("Request sent");
  String line = client.readStringUntil('\n');
  Serial.printf("Response code was: ");
  Serial.println(line);
  if (line.startsWith("HTTP/1.1 200 OK")) {
    return true;
  } else {
    return false;
  }
}
