#include <ESP8266WiFi.h>          
#include <BlynkSimpleEsp8266.h>
#include "ThingSpeak.h"
#include <WiFiClient.h>

char auth[] = "trSvQO_1-VG2eCbikntpQI2lBIfAX2Ln";

char ssid[] = "Kaan";//  bağlanılacak olan kablosuz ağın SSID si
char pass[] = "123456789"; // bağlanılacak olan kablosuz ağın şifresi

unsigned long channel_ID = 1607506;           
const char * myWriteAPIKey = "AAXN1BHMJV7BAEX7";  

const char *sunucu_IP = "maker.ifttt.com";          
String yol = "/trigger/priz_acik/with/key/dYDUjJf492PQhniGMtLC7K";

WiFiClient wifi_istemci;

WiFiClient istemci;
 
BLYNK_WRITE(D5)
  {  
    int pinValue = param.asInt(); 
   }
   
 void setup()
  { 

Serial.begin(9600);                       //Seri iletişim hızı 9600 bps olarak ayarlanarak başlatılıyor.
  delay(1000);
  
  WiFi.mode(WIFI_STA);                        //istasyon modu wifi ağına bağlanmak
  WiFi.begin(ssid,pass);                 //SSID ve şifre girilierek wifi başlatılıyor.

  //------- Wifi ağına bağlanıncaya kadar beklenilen kısım ------------
  Serial.print("Bağlantı kuruluyor");
  while (WiFi.status() != WL_CONNECTED) 
  { // Wifi bağlantısı sağlanana kadar bekleniyor.
    delay(500);                               // Bu arada her 500 ms de bir seri ekrana yan yana noktalar yazdırılarak
    Serial.print(".");                        //görsellik sağlanıyor.
  }
  //-------------------------------------------------------------------
  
  Serial.println("");                         //Bir alt satıra geçiliyor.
  Serial.println("Bağlantı sağlandı...");      //seri ekrana bağlantının kurulduğu bilgisi gönderiliyor.

  Serial.print("Alınan IP addresi: ");        // kablosuz ağdan alınan IP adresi
  Serial.println(WiFi.localIP());             // kablosuz ağdan alınan IP adresi

  ThingSpeak.begin(wifi_istemci);             
    
    digitalWrite (D5,HIGH );  

    Blynk.begin(auth, ssid, pass);
  }
void loop()
  { 
     if(digitalRead(D5)==LOW){
      Blynk.notify("Açık");
       delay(1000);

   if (!istemci.connect(sunucu_IP, 80))           
  {
    Serial.println("Baglanti kurulamadi!!!");   
    return;
  }
  
  istemci.print(String("GET ") + yol + " HTTP/1.1\r\n" + "Host: " + sunucu_IP + "\r\n" + "Connection: close\r\n\r\n");
  delay(15000);

  int x = ThingSpeak.writeField(channel_ID, 1, 0, myWriteAPIKey); 
  
     /* if(x == 200)        
      Serial.println("veri yazildi");
     else
       Serial.println("Hata var. HTTP hata kodu: " + String(x));
       */
      delay(17000);          
       }     
      else if(digitalRead(D5)==HIGH) { 
        Blynk.notify("Kapalı");
       delay(1000);
       
        int x = ThingSpeak.writeField(channel_ID, 1, 1, myWriteAPIKey);   
  
      if(x == 200)          
      Serial.println("veri yazildi");
     else
       Serial.println("Hata var. HTTP hata kodu: " + String(x));
       
      delay(17000);          
      }  
   Blynk.run();
  } 
