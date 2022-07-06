#include <AntaresESP32MQTT.h>

#define ACCESSKEY "3ceab5d21b598453:47983b6e4b7a0bfb"       // Ganti dengan access key akun Antares anda
#define WIFISSID "Www"         // Ganti dengan SSID WiFi anda
#define PASSWORD "xyz123456"     // Ganti dengan password WiFi anda

#define applicationName "SmartHome101"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Temperature"     // Ganti dengan device Antares yang telah dibuat

AntaresESP32MQTT antares(ACCESSKEY);    // Buat objek antares

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antares.setMqttServer();  // Inisiasi server MQTT Antares
}

void loop() {
  /*
    Cek koneksi ke broker MQTT Antares. Jika disconnect,
    akan dicoba untuk menyambungkan lagi
   */
  antares.checkMqttConnection();

  // Inisiasi variabel
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Tambahkan variabel ke penampungan data sementara
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  antares.add("wind_speed", windsp);
  antares.add("rain_level", rainlv);
  antares.add("latitude", lat);
  antares.add("longitude", lon);

  // Publish data ke database Antares dan juga broker MQTT Antares
  antares.publish(applicationName, deviceName);
  delay(5000);
}
