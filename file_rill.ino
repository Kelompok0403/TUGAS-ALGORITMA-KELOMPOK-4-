#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Pin untuk sensor PIR dan relay
const int pirPin = 2; 
const int relayPin = 3;

// Variabel untuk waktu deteksi gerakan terakhir
unsigned long lastMotionTime = 0;
// Waktu delay untuk memastikan lampu tetap menyala (10 detik)
const unsigned long motionDelay = 10000;

void setup() {
  // Setel pin PIR sebagai input
  pinMode(pirPin, INPUT);
  // Setel pin relay sebagai output
  pinMode(relayPin, OUTPUT);

  // Inisialisasi LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.print("Sistem Siap");
  delay(5000);
  lcd.clear();

  // Memastikan relay dalam keadaan padam saat pertama kali dinyalakan
  digitalWrite(relayPin, LOW);
  
}
void loop() {
  // Membaca status sensor PIR
  int pirState = digitalRead(pirPin);

  // Jika sensor PIR mendeteksi gerakan, perbarui waktu deteksi terakhir
  if (pirState == HIGH) {
    lastMotionTime = millis();
  }

  // Menggunakan if-else untuk pengendalian relay dan tampilan LCD
  if (millis() - lastMotionTime >= motionDelay) {
    digitalWrite(relayPin, LOW); // Mematikan relay (karena NO, ini akan membuka sirkuit)
    lcd.setCursor(0, 0);
    lcd.print("Ruangan ");
    lcd.setCursor(0, 1);
    lcd.print("Tidak Dipakai      ");
  } else {
    digitalWrite(relayPin, HIGH); // Menghidupkan relay (karena NO, ini akan menutup sirkuit)
    lcd.setCursor(0, 0);
    lcd.print("Ruangan ");
    lcd.setCursor(0, 1);
    lcd.print("Terpakai      ");
  }

  delay(1000); // Penundaan untuk mengurangi jitter
}
