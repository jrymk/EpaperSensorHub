#ifndef PDTVTPAPER_PDTVT_H
#define PDTVTPAPER_PDTVT_H

#include <Arduino.h>
#include <Wifi.h>
#include <SD.h>
#include <FastLED.h>
#include <Epepd.h>
#include <EpBuiltInFunctions.h>
#include "theme.h"
#include <ESP32Time.h>
#include <ArduinoJson.h>
#include <Adafruit_SHT31.h>
#include <SenseairS8.h>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "config.h"

namespace pdtvt {
    CRGB leds[1] = {CRGB::Black};

    SenseairS8 co2(2); // define RX2 and TX2 to change pins, by default RX2=16 TX2=17

    EpBitmap gfxBuffer(480, 280, 4);
    Epepd epd(EPAPER_CS, EPAPER_DC, EPAPER_RST, EPAPER_BUSY);
    EpPartialDisplay partialDisplay(epd);
    EpGreyscaleDisplay greyscaleDisplay(epd);
    EpPlacement epdPlacement(279, 0, 3); // display rotation

    Adafruit_SHT31 sht31;

    ESP32Time rtc(28800); // GMT+8

}

#endif //PDTVTPAPER_PDTVT_H
