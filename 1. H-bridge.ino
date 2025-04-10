//Mendefinisikan pin kontrol H-Bridge untuk arah putaran motor/dinamo
#define kiriMaju    7
#define kiriMundur  4
#define kananMaju   3
#define kananMundur 2


//Mendefinisikan pin kontrol 
#define speedKanan 5
#define speedKiri  6


//Taruh Kode dalam fungsi setup() untuk dijalankan sekali saat microcontroller boot (menyala)
void setup() {

  //Inisialisasi Pin2 untuk menjadi output
  pinMode(kiriMaju, OUTPUT);
  pinMode(kiriMundur, OUTPUT);
  pinMode(kananMaju, OUTPUT);
  pinMode(kananMundur, OUTPUT);
  pinMode(speedKanan, OUTPUT);
  pinMode(speedKiri, OUTPUT);

  //inisialisasi komunikasi Serial agar dapat debugging
  Serial.begin(115200);

}

//Taruh Kode dalam fungsi loop() untuk dijalankan terus-menerus hingga microcontroller mati (power off)
void loop() {

  //Kode Untuk Mengkontrol Arah Putaran Motor/Dinamo
  digitalWrite (kiriMaju  , true);
  digitalWrite (kiriMundur, false);
  digitalWrite (kananMaju , true);
  digitalWrite (kiriMundur, false);

  //Kode Untuk Mengkontrol Kecepatan Motor/Dinamo
  analogWrite  (speedKanan, 255); //Menghasilkan keluaran Maksimum yaitu 5V pada pin PWM
  analogWrite  (speedKiri,  255); //Menghasilkan keluaran Maksimum yaitu 5V pada pin PWM

  //menulis kata "Maju" pada komunikasi Serial, dapat dilihat pada "Serial Monitor" didalam editor Arduino IDE
  Serial.println("Maju");

  //Kode untuk menunda perjalanan program selanjutnya dalam waktu millisecond
  delay(1000);//menunda program selanjutnya selama satu detik


  //Robot akan bergerak ke kanan (output digital write dapat direpresentasikan sebagai true/false atau 1/0)
  digitalWrite (kiriMaju   , 1);
  digitalWrite (kiriMundur , 0);
  digitalWrite (kananMaju  , 0);
  digitalWrite (kananMundur, 1);

  analogWrite  (speedKanan, 153); //Menghasilkan keluaran Maksimum yaitu 3V pada pin PWM
  analogWrite  (speedKiri,  153); //Menghasilkan keluaran Maksimum yaitu 3V pada pin PWM, 
  /*keluaran pwm dapat dihitung dengan voltase yang diinginkan (3V), dibagi dengan total voltase (5v), dan dikalikan total bit PWM microcontroller (255)
  rumus : Vout / Vtotal * bitPWM

  contoh: 2.4/5 * 255 = 127.5 = 128 (dibulatkan)
  */

  Serial.println("Belok Kiri");
  
  delay(1000);
}
