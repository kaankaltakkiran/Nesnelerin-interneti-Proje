# Kurulum Notlarım

1. tercihler kısmına şunu yapıştır: https://arduino.esp8266.com/stable/package_esp8266com_index.json
2. board managerdan esp8266 2.42 sürümü yükle
3. esp8266 dan nodemcu 1.0 (esp 12-E Module) seç
4. [Olası hata çözümleri ](https://chatgpt.com/share/674c1a6b-f728-8008-bd3b-b47075cb05d4)
5. [Nodemcu Sorun Çözme Port /dev/ttyUSB0 veya brltty 2.5.2 esp8266 ](https://github.com/esp8266/source-code-examples/issues/26)

6. [Port bulmazsa çözüm ](https://github.com/OsmanKAYI/full-stack-roadmap/tree/main/hobbies/arduino)

7. [Mysql Bağlantı Sorunu Yunohost Phpmyadmin Kullanıcı 3306 Portu ](https://chatgpt.com/share/674d5b93-f3d0-8008-9ffc-3b2d7818ef56)

```bash
sudo apt remove brltty -y
```

7. Kullanıcı izni tanımlama

```bash
sudo usermod -a -G dialout $USER
sudo chmod a+rw /dev/ttyUSB*

```
