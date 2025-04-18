#include <NewPing.h>
#include <elapsedMillis.h>

elapsedMillis timer1;
elapsedMillis timer2;


// Motor control pins
#define kiriMaju    7
#define kiriMundur  4
#define kananMaju   3
#define kananMundur 2

#define speedKanan 5
#define speedKiri  6

#define TRIGGER_PINF  11 
#define ECHO_PINF     10  
#define TRIGGER_PINL  13 
#define ECHO_PINL     12  
#define TRIGGER_PINR  9 
#define ECHO_PINR     8  

#define MAX_DISTANCE 200 

NewPing sonarF(TRIGGER_PINF, ECHO_PINF, MAX_DISTANCE);
NewPing sonarL(TRIGGER_PINL, ECHO_PINL, MAX_DISTANCE);
NewPing sonarR(TRIGGER_PINR, ECHO_PINR, MAX_DISTANCE);

int distanceF, distanceR, distanceL, currentOrient;

void setup() {
  pinMode(kiriMaju,    OUTPUT);
  pinMode(kiriMundur,  OUTPUT);
  pinMode(kananMaju,   OUTPUT);
  pinMode(kananMundur, OUTPUT);
  pinMode(speedKanan,  OUTPUT);
  pinMode(speedKiri,   OUTPUT);
  Serial.begin(115200);
}


void loop() {
  distanceF = sonarF.ping_cm();
  distanceL = sonarL.ping_cm();
  distanceR = sonarR.ping_cm();

  if (distanceF >=5) {
    // Maju lurus kalau gak ada halangan
    Serial.println("MAJU");
    motorControl(1, 0, 1, 0, 80, 80);
  } else {
    // Terlalu dekat, mundur dulu
    Serial.println("Halangan di depan, mundur sebentar");
    motorControl(0, 1, 0, 1, 80, 80);
    delay(300);

    // Stop sebentar
    motorControl(0, 0, 0, 0, 0, 0);
    delay(2500);

    // Bandingkan kiri dan kanan
    if (distanceL < distanceR) {
      Serial.println("Belok kanan");
      motorControl(0,1, 1, 0, 80, 80); // Belok kiri
      delay(400);
      motorControl(0, 0, 0, 0, 0, 0);
      delay(500);
    } else {
      Serial.println("Belok kanan");
      motorControl(1, 0, 0, 1, 80, 80); // Belok kanan
      delay(400);
      motorControl(0, 0, 0, 0, 0, 0);
      delay(500);
    }

    // Stop sebentar setelah belok
    motorControl(0, 0, 0, 0, 0, 0);
      delay(500);
  }
}



void motorControl(int in1Value, int in2Value, int in3Value, int in4Value, int leftSpeed, int rightSpeed) {
  digitalWrite(kiriMaju,    in1Value);
  digitalWrite(kiriMundur,  in2Value);
  digitalWrite(kananMaju,   in3Value);
  digitalWrite(kananMundur, in4Value);
  analogWrite(speedKanan,   rightSpeed);
  analogWrite(speedKiri,    leftSpeed);
}
