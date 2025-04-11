//Menambahkan Library NewPing untuk membaca sensor ultrasonic
#include <NewPing.h>


//Mendefinisikan pin kontrol H-Bridge untuk arah putaran motor/dinamo
#define kiriMaju    7
#define kiriMundur  4
#define kananMaju   3
#define kananMundur 2


//Mendefinisikan pin kontrol 
#define speedKanan 5
#define speedKiri  6


// pin arduino yang terhubung dengan pin Trigger & Echo sensor ultrasonik
#define TRIGGER_PIN  4 
#define ECHO_PIN     5  

// jarak maksimum sensor (di sesuaikan dengan spesifikasi sensor yang digunakan, distance maksimum sensor WallFollower Lab adalah 200cm atau 2 Meter)
#define MAX_DISTANCE 200 

// inisialisasi Library NewPing dengan setting diatas
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 


//Inisialisasi Variable Integer untuk menyimpan data dari ultrasonik
int forwardD, rightD, leftD;


// Taruh Kode dalam fungsi setup() untuk dijalankan sekali saat microcontroller boot (menyala)
void setup() {

  // Inisialisasi Pin2 untuk menjadi output
  pinMode(kiriMaju,    OUTPUT);
  pinMode(kiriMundur,  OUTPUT);
  pinMode(kananMaju,   OUTPUT);
  pinMode(kananMundur, OUTPUT);
  pinMode(speedKanan,  OUTPUT);
  pinMode(speedKiri,   OUTPUT);

  // inisialisasi komunikasi Serial agar dapat debugging
  Serial.begin(115200);

}

// Fungsi untuk mengatur kecepatan dan rotasi pada H-Bridge
void motorControl (int in1Value, int in2Value, int in3Value, int in4Value, int rightSpeed, int leftSpeed) {
  
  digitalWrite (kiriMaju,    in1Value);
  digitalWrite (kiriMundur,  in2Value);
  digitalWrite (kananMaju,   in3Value);
  digitalWrite (kananMundur, in4Value);
  analogWrite  (speedKanan,  rightSpeed);
  analogWrite  (speedKiri,   leftSpeed);

}


//Taruh Kode dalam fungsi loop() untuk dijalankan terus-menerus hingga microcontroller mati (power off)
void loop() {

  //Bila Depan Robot terdapat tembok kurang dari 15cm maka robot akan bergerak ke kiri
  if (sonar.ping_cm() < 15){
    
    //Mengatur Motor/Dinamo Kanan dan kiri agar robot bergerak ke arah kanan
    motorControl(1,0,0,1,200,200);
    //Menunggu 500ms sampai robot berhadap ke Kanan
    delay(500);
    

    //Bila Kanan Robot terdapat tembok kurang dari 15cm maka robot akan bergerak ke kanan
    if(sonar.ping_cm() < 15){

      //Mengatur Motor/Dinamo Kanan dan kiri agar robot bergerak ke arah kanan
      motorControl();
      //Menunggu 1000ms sampai robot berhadap ke Kiri
      delay(1000);
      

      //Bila Kiri Robot terdapat tembok kurang dari 15cm maka robot akan berputar balik
      if(sonar.ping_cm() < 15){

        //Mengatur Motor/Dinamo Kanan dan kiri agar robot bergerak ke arah kanan
        motorControl();
        //Menunggu 500ms sampai robot berhadap ke Balik
        delay(500);
        
      }
    }
  }else{
    
    //Mengatur Motor/Dinamo Kanan dan kiri agar robot maju
    motorControl(1,0,1,0,200,200);
    
  }
}
