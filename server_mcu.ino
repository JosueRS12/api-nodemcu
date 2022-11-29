// #include <TimeLib.h>

// #include <TimeAlarms.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

// #define PULSADOR 3
Servo SERVO;

int close = 0;
int open = 270;
bool isOpen = false;
int statePulse = 0;
int hourAlarm;
int dayAlarm;
int minuteAlarm;


void setup() {
  Serial.begin(9600);
  SERVO.attach(2);
  SERVO.write(close);
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

void openDoor(){
  
  SERVO.write(open);
  isOpen = true;
  Serial.print("abriendo");
}

void closeDoor(){

  SERVO.write(close);
  isOpen = false;
  Serial.print("cerrando");
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

  triggerAlarm();
  Serial.println("hola");
  delay(1000);
  // openManually();
  
  // Alarm.delay(1000);
}
