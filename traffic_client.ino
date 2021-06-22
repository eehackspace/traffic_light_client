/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */
#include <SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "Hackspace_2_4"; // SSID of your home WiFi
char pass[] = "xxxx_x_xxx";    // password of your home WiFi

int GREEN_PIN = D5;
int AMBER_PIN = D4;
int RED_PIN = D3;

#define USE_SERIAL Serial

IPAddress server(192, 168, 0, 80); // the fix IP address of the server
WiFiClient client;

void setup()
{
  pinMode(GREEN_PIN, INPUT);
  pinMode(AMBER_PIN, INPUT);
  pinMode(RED_PIN, INPUT);

  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(AMBER_PIN, HIGH);
  digitalWrite(RED_PIN, HIGH);

  //  WiFi.disconnect();
  Serial.begin(115200); // only for debug
  USE_SERIAL.printf("Hello\n");
  delay(500)
  // for (uint8_t t = 4; t > 0; t--)
  // {
  //   USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
  //   USE_SERIAL.flush();
  //   delay(1000);
  //}
  // WiFi.begin(ssid, pass); // connects to the WiFi router
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   Serial.print(".");
  //   delay(500);
  // }
  // Serial.println("Connected to wifi");
  // Serial.print("Status: ");
  // Serial.println(WiFi.status()); // Network parameters
  // Serial.print("IP: ");
  // Serial.println(WiFi.localIP());
  // Serial.print("Subnet: ");
  // Serial.println(WiFi.subnetMask());
  // Serial.print("Gateway: %s");
  // Serial.println(WiFi.gatewayIP());
  // Serial.print("SSID: ");
  // Serial.println(WiFi.SSID());
  // Serial.print("Signal: ");
  // Serial.println(WiFi.RSSI());
}

/*
1. Wait for button press
2. When a button press is detected, arm the `current` variable with detected button
3. When a button is released (each loop iteration that doesn't have a button detected, but has a prior button recorded)
  3a. Send the state to traffic lights
  3b. Clear the state (it'll be populated again on next button press)
4. Each loop that hd no press and no armed button, just do nothing
*/

char current = 'x'; // x means nothing pending to set

void loop()
{
  Serial.println(current);

  if (pressed(GREEN_PIN))
  {
    current = 'g';
  }
  else if (pressed(AMBER_PIN))
  {
    current = 'a';
  }
  // else if (pressed(RED_PIN))
  // {
  //   current = 'r';
  // }
  else
  { // nothing pressed, lets see if we should send anything
    if (current != 'x')
    { // we have a button queued to be sent
      send(current);
      current = 'x'; // reset - nothing queued to be sent
    }
  }

  delay(50);
}

bool pressed(int button)
{
  return !digitalRead(button);
}

void send(char colour)
{
  Serial.print("Queued item:");
  Serial.println(colour);
}