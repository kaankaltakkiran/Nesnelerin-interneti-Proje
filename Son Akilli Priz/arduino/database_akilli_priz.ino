#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Wi-Fi bilgileri
const char* ssid = "wifi adi";  // Wi-Fi ağ adı
const char* password = "wifi sifresi";  // Wi-Fi şifresi

// MySQL bilgileri
IPAddress server_addr("sunucu ip");  // MySQL sunucusunun IP adresi
char user[] = "mysql kullanıcı adı";  // MySQL kullanıcı adı
char pass[] = "mysql sifresi";  // MySQL şifresi

WiFiClient client;
MySQL_Connection conn((Client *)&client);

const int relayPin = D5;  // Röleyi kontrol etmek için kullanılan pin
int lastRelayStatus = -1;  // Başlangıçta herhangi bir değeri olmayan bir değişken

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Röleyi başlangıçta kapalı tut

  // Wi-Fi bağlantısı
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ya bağlanıyor...");
  }
  Serial.println("WiFi'ya bağlı.");

  // Veritabanı bağlantısı
  if (conn.connect(server_addr, 3306, user, pass)) {
    Serial.println("Veritabanına bağlanıldı.");
  } else {
    Serial.println("Veritabanına bağlanılamadı.");
  }
}

void loop() {
  if (conn.connected()) {
    // SQL sorgusu: nodemcu tablosundan relay_status durumunu çek
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute("SELECT relay_status FROM priz.nodemcu WHERE id = 1;");
    
    column_names *cols = cur_mem->get_columns();
    row_values *row = cur_mem->get_next_row();

    // Eğer satır varsa
    if (row != NULL) {
      int relayStatus = atoi(row->values[0]);  // relay_status sütunundan değer al
      Serial.print("Röle Durumu: ");
      Serial.println(relayStatus);

      // Durum değiştiyse, röleyi kontrol et
      if (relayStatus != lastRelayStatus) {
        if (relayStatus == 1) {
          digitalWrite(relayPin, LOW);  // Röleyi aç
        } else {
          digitalWrite(relayPin, HIGH);   // Röleyi kapat
        }
        lastRelayStatus = relayStatus;  // Yeni durumu kaydet
      }
    }
    delete cur_mem;  // Bellek yönetimi
    delay(1000);     // Bir sonraki sorgu için bekleme
  } else {
    Serial.println("Veritabanı bağlantısı koptu, tekrar bağlanmayı deniyor...");
    conn.connect(server_addr, 3306, user, pass);
  }
}