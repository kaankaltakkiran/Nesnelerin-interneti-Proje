// Blynk ile calisan akilli priz

#define BLYNK_AUTH_TOKEN "My secret auth token"
#define BLYNK_TEMPLATE_ID "TMPL4oyM1lEz4"
#define BLYNK_TEMPLATE_NAME "Kaan Akıllı Priz"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi bilgileri
char ssid[] = "Kaan";
char pass[] = "123456789123123123123123123123123123123123";

// Röle pini
int relayPin = D5;

void setup() {
  // Seri iletişim başlat
  Serial.begin(115200);
  delay(100);

  // Bilgi mesajı
  Serial.println(">>> Cihaz başlatılıyor...");
  Serial.println(">>> Wi-Fi bağlantısı başlatılıyor...");
  
  // Röleyi kapalı tutarak çıkış pini ayarla
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Blynk bağlantısı başlat
  Serial.print(">>> Wi-Fi ağına bağlanılıyor: ");
  Serial.println(ssid);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  // Wi-Fi bağlantısı kontrolü
  Serial.println(">>> Bağlantı durumu kontrol ediliyor...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n>>> Wi-Fi bağlantısı başarılı!");
  Serial.print(">>> IP Adresi: ");
  Serial.println(WiFi.localIP());
  
  // Blynk bağlantısı kontrolü
  Serial.println(">>> Blynk sunucusuna bağlanılıyor...");
}

void loop() {
  // Blynk çalıştırma
  Blynk.run();
}

// Blynk butonunu işleyen fonksiyon
BLYNK_WRITE(V5) {
  int pinValue = param.asInt();  // Buton durumu (0 veya 1)
  Serial.print(">>> Buton durumu: ");
  Serial.println(pinValue);

  // Röleyi aç/kapa
  if (pinValue) {
    Serial.println(">>> Röle: ON");
    digitalWrite(relayPin, LOW);
  } else {
    Serial.println(">>> Röle: OFF");
    digitalWrite(relayPin, HIGH);
  }
}