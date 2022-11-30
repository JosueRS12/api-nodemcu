#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#ifndef STASSID
#define STASSID "Josue"
#define STAPSK  "quememira"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;
const int led = LED_BUILTIN;
const int close = 0;
const int open = 180;
bool isOpen = false;
const int statePulse = 0;
const int PORT = 80;


ESP8266WebServer server(PORT);

Servo SERVO;

void handleRoot() {
  digitalWrite(led, 1);
  String message = "NodeMCU api";
  server.send(200, "text/plain", message);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void openDoor(){
  SERVO.write(open);
  delay(1000);
  isOpen = true;
  Serial.print("abriendo");
  server.send(200, "text/json", "{\"data\": \"Compuerta abierta\"}");
}

void closeDoor(){
  SERVO.write(close);
  delay(1000);
  isOpen = false;
  Serial.print("cerrando");
  server.send(200, "text/json", "{\"data\": \"Compuerta cerrada\"}");
}

void restServerRouting(){
  server.on("/nodemcu-api",HTTP_GET, handleRoot);
  server.on("/nodemcu-api/open",HTTP_POST, openDoor);
  server.on("/nodemcu-api/close",HTTP_POST, closeDoor);
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  SERVO.attach(2);
  SERVO.write(close);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  restServerRouting();
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  // pinMode(PULSADOR, INPUT);
  // For alarms
  //setTime(hr,min,sec,day,month,yr); 
  ///////////////////////////////
  // setTime(8,10,0,8,10,2022);
  // Alarm.alarmRepeat(8,10,30,triggerAlarm);
  // Alarm.alarmRepeat(8,11,0,triggerAlarm);
  // Alarm.alarmRepeat(8,11,30,triggerAlarm);
  // Alarm.alarmRepeat(8,12,0,triggerAlarm);
  // Alarm.alarmRepeat(8,12,30,triggerAlarm);
  ///////////////////
  // Alarm.alarmRepeat(8,3,0,triggerAlarm);
}

// void openManually(){
//   statePulse = digitalRead(PULSADOR);
//   if (statePulse){
//     if (!isOpen){
//       openDoor();
//       delay(1000);
//     }
//     else if (isOpen){
//       closeDoor();
//       delay(1000);
//     } 
//   }
// }

void triggerAlarm(){
  openDoor();
  delay(5000);
  closeDoor();
}

void loop() {
  // char buffer[100];
  // char buffer2[100];
  //setTime(hr,min,sec,day,month,yr); 
  
  // sprintf(buffer, "%d %d %d %d", hour(), minute(), day(), second());
  //sprintf(buffer2, "%d %d %d ", hourAlarm, minuteAlarm, dayAlarm);
  // Serial.print(buffer);
  // Serial.print("\n");
  //Serial.print(buffer2);
  server.handleClient();
  // triggerAlarm();
  // Serial.println("hola");
  // delay(1000);
  // openManually();
  
  // Alarm.delay(1000);
}
