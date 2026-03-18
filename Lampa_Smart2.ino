#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID" 
       #define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME" 
        #define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN" 
 
        #include <WiFi.h> 
#include <WiFiMulti.h> 
#include <BlynkSimpleEsp32.h> 
#include <Adafruit_NeoPixel.h> 
#include <time.h> 
#include <Adafruit_SSD1306.h> 
#include <hp_BH1750.h> 
#include <Wire.h> 
 
#define LED_PIN 13 
        #define NUM_LEDS 10 
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800); 
 
WiFiMulti wifiMulti; 
Adafruit_SSD1306 display(128, 32, &Wire, -1);hp_BH1750 lightMeter; 
BlynkTimer timer; 
 
        int stareLampa = 0, modAutomat = 0; 
        int r = 255, g = 255, b = 255, w = 255, intensitate = 150; 
float luxFiltru = 0; 
String mementoCurent = ""; 
bool mementoActiv = false; 
 
void aplicaLumina() { 
    if (stareLampa == 1) { 
        strip.setBrightness(intensitate); 
        for(int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(r, g, b, w)); 
    } else { 
        strip.setBrightness(0); 
        for(int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, 0); 
    } 
    strip.show(); 
} 
 
void flashAlerta() { 
    int r_b = r, g_b = g, b_b = b, w_b = w, i_b = intensitate; 
    for(int k = 0; k < 3; k++) { 
        strip.setBrightness(200); 
        for(int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(255, 0, 0, 0)); 
        strip.show(); delay(200); 
        for(int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, 0); 
        strip.show(); delay(200); 
    } 
    r = r_b; g = g_b; b = b_b; w = w_b; intensitate = i_b; 
    aplicaLumina(); 
} 
 
BLYNK_CONNECTED() { Blynk.syncAll(); } 
 
BLYNK_WRITE(V1) { stareLampa = param.asInt(); aplicaLumina(); } 
BLYNK_WRITE(V8) { modAutomat = param.asInt(); } 
BLYNK_WRITE(V4) { intensitate = param.asInt(); aplicaLumina(); } 
BLYNK_WRITE(V7) { r = param[0].asInt(); g = param[1].asInt(); b = param[2].asInt(); w = param[3].asInt(); aplicaLumina(); } 
 

BLYNK_WRITE(V3) { 
    String textInput = param.asString(); 
    if(textInput.length() > 0 && textInput != " ") { 
        mementoCurent = textInput; 
        mementoActiv = true; 
        flashAlerta(); 
    } 
} 
 

BLYNK_WRITE(V6) { 
    if(param.asInt() == 1) { 
        mementoActiv = false; 
        mementoCurent = ""; 
        Blynk.virtualWrite(V3, ""); 
    } 
} 
 

BLYNK_WRITE(V5)  { if(param.asInt()) { r=255; g=255; b=255; w=255; intensitate=255; aplicaLumina(); } } 
BLYNK_WRITE(V9)  { if(param.asInt()) { r=255; g=210; b=140; w=180; intensitate=255; aplicaLumina(); } } 
BLYNK_WRITE(V10) { if(param.asInt()) { r=255; g=120; b=20;  w=30;  intensitate=220; aplicaLumina(); } } 
 

void verificareSenzorSiOra() { 
    lightMeter.start(); 
    float luxCitit = lightMeter.getLux(); 
    luxFiltru = (luxFiltru * 0.95) + (luxCitit * 0.05); 
    Blynk.virtualWrite(V2, luxFiltru); 
 
    if (stareLampa == 1 && modAutomat == 1) { 
        int tinta; 
        if (luxFiltru > 250) tinta = 15; 
        else if (luxFiltru > 120) tinta = 70; 
        else if (luxFiltru < 40) tinta = 255; 
        else tinta = 140; 
 
       
        if(abs(tinta - intensitate) > 60) { 
            intensitate = tinta; 
            aplicaLumina(); 
            Blynk.virtualWrite(V4, intensitate); 
        } 
    } 
 
    struct tm timeinfo; 
    display.clearDisplay(); 
    display.setTextColor(SSD1306_WHITE); 
    if(getLocalTime(&timeinfo)) { 
        char oraAfis[10]; 
        strftime(oraAfis, 10, "%H:%M", &timeinfo); 
        display.setTextSize(2); display.setCursor(35, 0); display.print(oraAfis); 
    } 
 
    display.setTextSize(1); display.setCursor(0, 22); 
    display.print(mementoActiv ? "MSG: " + mementoCurent : "Sistem Online"); 
    display.display(); 
} 
 

void setup() { 
    strip.begin(); 
    strip.show(); 
    Wire.begin(); 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    lightMeter.begin(BH1750_TO_GROUND); 
 
    wifiMulti.addAP("wifi_address", "wifi_password"); 
     wifiMulti.addAP("hospot_address", "hospot_password");
 
    while (wifiMulti.run() != WL_CONNECTED) { delay(500); } 
   configTzTime("EET-2EEST,M3.5.0/3,M10.5.0/4", "pool.ntp.org");
    Blynk.config(BLYNK_AUTH_TOKEN); 
    timer.setInterval(2000L, verificareSenzorSiOra); 
} 
 
void loop() { 
    Blynk.run(); 
    timer.run(); 
} 
