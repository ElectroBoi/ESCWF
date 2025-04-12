#include <NewPing.h>

// Motor control pins
#define kiriMaju    7
#define kiriMundur  4
#define kananMaju   3
#define kananMundur 2

#define speedKanan 5
#define speedKiri  6

#define TRIGGER_PIN  11 
#define ECHO_PIN     10  
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(kiriMaju,    OUTPUT);
  pinMode(kiriMundur,  OUTPUT);
  pinMode(kananMaju,   OUTPUT);
  pinMode(kananMundur, OUTPUT);
  pinMode(speedKanan,  OUTPUT);
  pinMode(speedKiri,   OUTPUT);
  Serial.begin(115200);
}

void motorControl(int in1Value, int in2Value, int in3Value, int in4Value, int rightSpeed, int leftSpeed) {
  digitalWrite(kiriMaju,    in1Value);
  digitalWrite(kiriMundur,  in2Value);
  digitalWrite(kananMaju,   in3Value);
  digitalWrite(kananMundur, in4Value);
  analogWrite(speedKanan,   rightSpeed);
  analogWrite(speedKiri,    leftSpeed);
}

void loop() {
  int distance = sonar.ping_cm();

  if (distance > 0 && distance < 15) {
    // Wall ahead: turn left
    Serial.println("turn left");
    motorControl(0, 1, 1, 0, 150, 150); // turn left
    delay(150);
  } else {
    // No wall ahead: go forward, but veer slightly right
    motorControl(1, 0, 1, 0, 80, 100); // slight curve to the right
    Serial.println("FORWARD");
  }

  delay(100);
}
