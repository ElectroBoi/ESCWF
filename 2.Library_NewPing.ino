//Menambahkan Library NewPing untuk membaca sensor ultrasonic
#include <NewPing.h>

// pin arduino yang terhubung dengan pin Trigger & Echo sensor ultrasonik 
#define TRIGGER_PIN  5
#define ECHO_PIN     4  

// jarak maksimum sensor (di sesuaikan dengan spesifikasi sensor yang digunakan, distance maksimum sensor WallFollower Lab adalah 200cm atau 2 Meter)
#define MAX_DISTANCE 200 

// inisialisasi Library NewPing dengan setting diatas
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {

  //inisialisasi komunikasi Serial agar dapat debugging
  Serial.begin(115200); 

}

void loop() {
                
  /*
  Menulis hasil pembacaan sensor ke komunikasi Serial dengan memanggil object newping yang terinisialisasi diatas, 
  lalu memanggil fungsi "ping_cm()" untuk membaca data yang telah dihitung menjadi cm
  */
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");

  //Menunggu 50ms setiap pembacaan sensor, waktu delay terendah untuk jarak 200cm 29ms
  delay(50);      
  
}
