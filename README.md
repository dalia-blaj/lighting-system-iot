# lighting-system-iot
An IoT smart lighting system with OLED display, RGBW LED control, and remote reminders via the Blynk cloud

##Overview
This project represents a prototype of a smart lighting system built using the ESP32. It integrates hardware and software components to provide remote control, automatic light adjustment, and message notifications.

##Features
* Remote control via the Blynk mobile app
* RGBW LED strip control (NeoPixel)
* Automatic brightness adjustment based on ambient light (BH1750 sensor)
* OLED display for time and messages
* Visual alert system for reminders
* Wi-Fi connectivity

##Hardware Components
* ESP32 (Lolin D32 Pro)
* OLED Display (0.96", I2C, 128x32)
* BH1750 Light Sensor
* NeoPixel RGBW LED strip (10 LEDs)
* Power supply via USB-C

##Software & Technologies
* C++ (Arduino framework)
* Blynk IoT platform
* NTP (Network Time Protocol)
  
  Libraries:
  * Adafruit_NeoPixel
  * Adafruit_SSD1306
  * BlynkSimpleEsp32
  * hp_BH1750

##System Description
The system connects to Wi-Fi and receives messages from the Blynk Cloud. Messages are displayed on the OLED screen and trigger a visual LED alert.

The system can operate in:
* Manual mode (user-controlled)
* Automatic mode (adjusts brightness based on ambient light)

##Project Images

![ESP32 conections(light sensor + OLED display](poza1.jpg)
![prototype exterior](poza2.jpg)
![hardware ](poza3.jpg)
![light sensor](poza4.jpg)

##Demo Video
[Watch demo video](https://drive.google.com/file/d/1GQG9NQAnZL4vqzHySLceoQQNIJjPDeEh/view?usp=sharing)

##Note
This project is a functional prototype developed for academic purposes. It was implemented on a breadboard with a handmade enclosure.

##Author
Blaj Dalia Mihaela





