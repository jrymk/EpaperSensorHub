#include "pdtvt.h"
#include "init.h"

void setup() {
    Serial.begin(115200);

    pdtvt::epd.init();
    pdtvt::gfxBuffer.allocate(4096);

    pdtvt::drawSplashScreen();

    pdtvt::co2.begin();
    pdtvt::sht31.begin();
    FastLED.addLeds<WS2811, LED_PIN, RGB>(pdtvt::leds, 1);
    FastLED.show();

    pdtvt::initSdCard();

    pdtvt::loadConfig();

    pdtvt::connectWifi();

    pdtvt::epd.powerOff();


    pdtvt::sht31.heater(false);
    Serial.print("is sht31 heater enabled: ");
    Serial.print(pdtvt::sht31.isHeaterEnabled());
    Serial.print("\n");

//    {
//        int16_t tbx, tby;
//        uint16_t tbw, tbh;
//        display.setCursor(0, 35);
//        display.print("Getting time from time.windows.com");
//        display.display(true);
//    }

    configTime(0, 0, "time.windows.com");
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        pdtvt::rtc.setTimeStruct(timeinfo);
    }
    Serial.println(pdtvt::rtc.getDateTime(true));

//    display.fillScreen(GxEPD_WHITE);
//    display.display(false);
//    delay(1000);

//    delay(1000);
//    display.powerOff();

//    Serial.printf("Test\n");
//    display.fillRect(0, 0, 100, 128, GxEPD_WHITE);
//    display.fillRect(100, 0, 100, 128, GxEPD_LIGHTGREY);
//    display.fillRect(200, 0, 100, 128, GxEPD_DARKGREY);
//    display.fillRect(300, 0, 100, 128, GxEPD_GFX_BLACK);
//    display.display(false);
//
//    display.setFont(&Aero_Matics_Bold44pt7b);
//    display.setTextColor(GxEPD_GFX_BLACK);
//    std::stringstream ss;
//    ss << std::setfill('0') << std::setw(2) << rtc.getHour(true) << ":" << std::setfill('0') << std::setw(2) << rtc.getMinute();
//    display.setCursor(5, 128);
//    display.print(ss.str().c_str());
//    display.display(true);
//
//
    Serial.printf("done\n");

    delay(1000);
}

void loop() {
}
