// Display Library example for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: these e-papers require 3.3V supply AND data lines!
//
// Display Library based on Demo Example from Good Display: http://www.e-paper-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2_4G

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Dispay ePaper for Arduino: https://forum.arduino.cc/index.php?topic=436411.0

// mapping suggestion from Waveshare SPI e-Paper to Wemos D1 mini
// BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V
// NOTE: connect 4.7k pull-down from D8 to GND if your board or shield has level converters
// NOTE for ESP8266: using SS (GPIO15) for CS may cause boot mode problems, use different pin in case, or 4k7 pull-down

// mapping suggestion from Waveshare SPI e-Paper to generic ESP8266
// BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V
// NOTE: connect 4.7k pull-down from GPIO15 to GND if your board or shield has level converters
// NOTE for ESP8266: using SS (GPIO15) for CS may cause boot mode problems, use different pin in case, or 4k7 pull-down

// mapping of Waveshare e-Paper ESP8266 Driver Board, new version
// BUSY -> GPIO5, RST -> GPIO2, DC -> GPIO4, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V
// NOTE for ESP8266: using SS (GPIO15) for CS may cause boot mode problems, add a 3.3k pull-down in case
//      the e-Paper ESP8266 Driver Board should have no boot mode issue, as it doesn't use level converters

// mapping of Waveshare e-Paper ESP8266 Driver Board, old version
// BUSY -> GPIO16, RST -> GPIO5, DC -> GPIO4, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V
// NOTE for ESP8266: using SS (GPIO15) for CS may cause boot mode problems, use different pin in case

// mapping suggestion for ESP32, e.g. LOLIN32, see .../variants/.../pins_arduino.h for your board
// NOTE: there are variants with different pins for SPI ! CHECK SPI PINS OF YOUR BOARD
// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V

// new mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
// BUSY -> A1, RST -> A2, DC -> A3, CS-> A4, CLK -> A5, DIN -> A7

// mapping suggestion for AVR, UNO, NANO etc.
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 10, CLK -> 13, DIN -> 11

// mapping of Waveshare Universal e-Paper Raw Panel Driver Shield for Arduino / NUCLEO
// BUSY -> 7, RST -> 8, DC -> 9, CS-> 10, CLK -> 13, DIN -> 11

// mapping suggestion for Arduino MEGA
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 53, CLK -> 52, DIN -> 51

// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 1

#include <GxEPD2_4G_4G.h>
#include <GxEPD2_4G_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#if defined (ESP8266)
// select one and adapt to your mapping, can use full buffer size (full HEIGHT)
//GxEPD2_4G_4G<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT> display(GxEPD2_290_T5(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> display(GxEPD2_290_T5D(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, GxEPD2_290_I6FD::HEIGHT> display(GxEPD2_290_I6FD(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display(GxEPD2_290_T94(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
//GxEPD2_4G_4G<GxEPD2_371, GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
//GxEPD2_4G_4G<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));
//GxEPD2_4G_4G<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2> display(GxEPD2_750_T7(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));

// ***** for mapping of Waveshare e-Paper ESP8266 Driver Board, new version *****
// select one , can use full buffer size (full HEIGHT)
//GxEPD2_4G_4G<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT> display(GxEPD2_290_T5(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> display(GxEPD2_290_T5D(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, GxEPD2_290_I6FD::HEIGHT> display(GxEPD2_290_I6FD(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display(GxEPD2_290_T94(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
//GxEPD2_4G_4G<GxEPD2_371, GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
//GxEPD2_4G_4G<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));
//GxEPD2_4G_4G<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2> display(GxEPD2_750_T7(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=2*/ 2, /*BUSY=5*/ 5));

// ***** for mapping of Waveshare e-Paper ESP8266 Driver Board, old version *****
// select one , can use full buffer size (full HEIGHT)
//GxEPD2_4G_4G<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT> display(GxEPD2_290_T5(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> display(GxEPD2_290_T5D(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, GxEPD2_290_I6FD::HEIGHT> display(GxEPD2_290_I6FD(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display(GxEPD2_290_T94(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));
//GxEPD2_4G_4G<GxEPD2_371, GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));
//GxEPD2_4G_4G<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));
//GxEPD2_4G_4G<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2> display(GxEPD2_750_T7(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));
#endif

#if defined(ESP32)
// select one and adapt to your mapping, can use full buffer size (full HEIGHT)
//GxEPD2_4G_4G<GxEPD2_213_flex, GxEPD2_213_flex::HEIGHT> display(GxEPD2_213_flex(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, GxEPD2_290_T5::HEIGHT> display(GxEPD2_290_T5(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> display(GxEPD2_290_T5D(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, GxEPD2_290_I6FD::HEIGHT> display(GxEPD2_290_I6FD(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display(GxEPD2_290_T94(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, GxEPD2_270::HEIGHT> display(GxEPD2_270(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
GxEPD2_4G_4G<GxEPD2_370, GxEPD2_370::HEIGHT> display(GxEPD2_370(/*CS=5*/ 2, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
//GxEPD2_4G_4G<GxEPD2_371, GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
//GxEPD2_4G_4G<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
// note: need to use half height buffer, to stay < 96000 bytes of RAM, would hang on setup else
//GxEPD2_4G_4G<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT / 2> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
#endif

// can't use package "STMF1 Boards (STM32Duino.com)" (Roger Clark) anymore with Adafruit_GFX, use "STM32 Boards (selected from submenu)" (STMicroelectronics)
#if defined(ARDUINO_ARCH_STM32)
#define MAX_DISPAY_BUFFER_SIZE 15000ul // ~15k is a good compromise
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 4) ? EPD::HEIGHT : MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 4))
// select one and adapt to your mapping
//GxEPD2_4G_4G<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)> display(GxEPD2_213_flex(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)> display(GxEPD2_290_T5(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, MAX_HEIGHT(GxEPD2_290_T5D)> display(GxEPD2_290_T5D(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, MAX_HEIGHT(GxEPD2_290_I6FD)> display(GxEPD2_290_I6FD(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, MAX_HEIGHT(GxEPD2_290_T94)> display(GxEPD2_290_T94(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, MAX_HEIGHT(GxEPD2_270)> display(GxEPD2_270(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1));
//GxEPD2_4G_4G<GxEPD2_371, MAX_HEIGHT(GxEPD2_371)> display(GxEPD2_371(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1));
//GxEPD2_4G_4G<GxEPD2_420, MAX_HEIGHT(GxEPD2_420)> display(GxEPD2_420(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1));
//GxEPD2_4G_4G<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)> display(GxEPD2_750_T7(/*CS=PA4*/ SS, /*DC=*/ PA3, /*RST=*/ PA2, /*BUSY=*/ PA1));
#endif

#if defined(__AVR)
#define MAX_DISPAY_BUFFER_SIZE 800 // 
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 4) ? EPD::HEIGHT : MAX_DISPAY_BUFFER_SIZE / (EPD::WIDTH / 4))
// select one and adapt to your mapping
//GxEPD2_4G_4G<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)> display(GxEPD2_213_flex(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)> display(GxEPD2_290_T5(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, MAX_HEIGHT(GxEPD2_290_T5D)> display(GxEPD2_290_T5D(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, MAX_HEIGHT(GxEPD2_290_I6FD)> display(GxEPD2_290_I6FD(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, MAX_HEIGHT(GxEPD2_290_T94)> display(GxEPD2_290_T94(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, MAX_HEIGHT(GxEPD2_270)> display(GxEPD2_270(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_371, MAX_HEIGHT(GxEPD2_371)> display(GxEPD2_371(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_420, MAX_HEIGHT(GxEPD2_420)> display(GxEPD2_420(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)> display(GxEPD2_750_T7(/*CS=10*/ SS, /*DC=*/ 8, /*RST=*/ 9, /*BUSY=*/ 7));

// ***** for mapping of Waveshare Universal e-Paper Raw Panel Driver Shield for Arduino / NUCLEO *****
// the RST line is not connected through level converter, but has a pull up resistor and a pull down diode to the Arduino pin; this is safe for 5V Arduino
// NOTE: the 11-pinholes for pin connectors are not through level converter, and the VCC pin is ~4.2V, only FCP connector pins are through level converter
// NOTE: the VCC pin on the 11-pinholes for pin connectors shouldn't be used, it seems to get back-fed from Arduino data pins through protection diodes of the level converter
// NOTE: the VCC pin should be fed from Arduino 5V pin for use on any 5V Arduino (did they forget to add this connection or add a jumper?)
// select one and adapt to your mapping
//GxEPD2_4G_4G<GxEPD2_213_flex, MAX_HEIGHT(GxEPD2_213_flex)> display(GxEPD2_213_flex(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEW0213I5F
//GxEPD2_4G_4G<GxEPD2_290_T5, MAX_HEIGHT(GxEPD2_290_T5)> display(GxEPD2_290_T5(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEW029T5
//GxEPD2_4G_4G<GxEPD2_290_T5D, MAX_HEIGHT(GxEPD2_290_T5D)> display(GxEPD2_290_T5D(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEW029T5D
//GxEPD2_4G_4G<GxEPD2_290_I6FD, MAX_HEIGHT(GxEPD2_290_I6FD)> display(GxEPD2_290_I6FD(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEW029I6FD
//GxEPD2_4G_4G<GxEPD2_290_T94, MAX_HEIGHT(GxEPD2_290_T94)> display(GxEPD2_290_T94(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7)); // GDEW029T94
//GxEPD2_4G_4G<GxEPD2_270, MAX_HEIGHT(GxEPD2_270)> display(GxEPD2_270(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_371, MAX_HEIGHT(GxEPD2_371)> display(GxEPD2_371(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_420, MAX_HEIGHT(GxEPD2_420)> display(GxEPD2_420(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7));
//GxEPD2_4G_4G<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)> display(GxEPD2_750_T7(/*CS=10*/ SS, /*DC=*/ 9, /*RST=*/ 8, /*BUSY=*/ 7));
#endif

#include "GxEPD2_boards_added.h"
//#include "GxEPD2_more_boards_added.h" // private

#if !defined(__AVR) && !defined(_BOARD_GENERIC_STM32F103C_H_) && !defined(ARDUINO_BLUEPILL_F103C8)

// comment out unused bitmaps to reduce code space used
#include "bitmaps/Bitmaps104x212.h" // 2.13" b/w flexible GDEW0213I5F
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps176x264.h" // 2.7"  b/w
#include "bitmaps/Bitmaps240x416.h" // 3.71"  b/w
#include "bitmaps/Bitmaps400x300.h" // 4.2"  b/w
#include "bitmaps/Bitmaps4g104x212.h" // 2.13" b/w flexible GDEW0213I5F
#include "bitmaps/Bitmaps4g128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps4g176x264.h" // 2.7"  b/w
#include "bitmaps/Bitmaps4g_I6FD_128x296.h"
#include "bitmaps/Bitmaps4g400x300.h" // 4.2"  b/w
#include "bitmaps/Bitmaps4g800x480.h" // 7.5"  b/w
// tests
#include "bitmaps/Bitmaps2g104x104.h"

#else

// select only one to fit in code space
#include "bitmaps/Bitmaps104x212.h" // 2.13" b/w flexible GDEW0213I5F
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps176x264.h" // 2.7"  b/w
#include "bitmaps/Bitmaps240x416.h" // 3.71"  b/w
#include "bitmaps/Bitmaps400x300.h" // 4.2"  b/w
//#include "bitmaps/Bitmaps4g400x300.h" // 4.2"  b/w // too big

#endif

#if defined(ARDUINO_ARCH_RP2040) && defined(ARDUINO_RASPBERRY_PI_PICO)
// SPI pins used by GoodDisplay DESPI-PICO. note: steals standard I2C pins PIN_WIRE_SDA (6), PIN_WIRE_SCL (7)
// uncomment next line for use with GoodDisplay DESPI-PICO.
arduino::MbedSPI SPI0(4, 7, 6); // need be valid pins for same SPI channel, else fails blinking 4 long 4 short
#endif

// note for partial update window and setPartialWindow() method:
// partial update window size and position is on byte boundary in physical x direction
// the size is increased in setPartialWindow() if x or w are not multiple of 8 for even rotation, y or h for odd rotation
// see also comment in GxEPD2_4G_4G.h, GxEPD2_3C.h or GxEPD2_GFX.h for method setPartialWindow()

const char HelloWorld[] = "Hello World!";
const char HelloArduino[] = "Hello Arduino!";
const char HelloEpaper[] = "Hello E-Paper!";

void helloWorld()
{
  //Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  //Serial.println("helloWorld done");
}

void helloWorldForDummies()
{
  //Serial.println("helloWorld");
  const char text[] = "Hello World!";
  // most e-papers have width < height (portrait) as native orientation, especially the small ones
  // in GxEPD2 rotation 0 is used for native orientation (most TFT libraries use 0 fix for portrait orientation)
  // set rotation to 1 (rotate right 90 degrees) to have enough space on small displays (landscape)
  display.setRotation(1);
  // select a suitable font in Adafruit_GFX
  display.setFont(&FreeMonoBold9pt7b);
  // on e-papers black on white is more pleasant to read
  display.setTextColor(GxEPD_BLACK);
  // Adafruit_GFX has a handy method getTextBounds() to determine the boundary box for a text for the actual font
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  // full window mode is the initial mode, set it anyway
  display.setFullWindow();
  // here we use paged drawing, even if the processor has enough RAM for full buffer
  // so this can be used with any supported processor board.
  // the cost in code overhead and execution time penalty is marginal
  // tell the graphics class to use paged drawing mode
  display.firstPage();
  do
  {
    // this part of code is executed multiple times, as many as needed,
    // in case of full buffer it is executed once
    // IMPORTANT: each iteration needs to draw the same, to avoid strange effects
    // use a copy of values that might change, don't read e.g. from analog or pins in the loop!
    display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
    display.setCursor(x, y); // set the postition to start printing text
    display.print(text); // print some text
    // end of part executed multiple times
  }
  // tell the graphics class to transfer the buffer content (page) to the controller buffer
  // the graphics class will command the controller to refresh to the screen when the last page has been transferred
  // returns true if more pages need be drawn and transferred
  // returns false if the last page has been transferred and the screen refreshed for panels without fast partial update
  // returns false for panels with fast partial update when the controller buffer has been written once more, to make the differential buffers equal
  // (for full buffered with fast partial update the (full) buffer is just transferred again, and false returned)
  while (display.nextPage());
  //Serial.println("helloWorld done");
}

void helloFourGreyLevels()
{
  //Serial.println("helloFourGreyLevels");
  const char fourgrey[] = "four grey levels";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  // do this outside of the loop
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fourgrey, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(spm, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(hwx, hwy);
    display.print(HelloWorld);
    display.setTextColor(GxEPD_DARKGREY);
    display.setCursor(utx, uty);
    display.print(fourgrey);
    display.setTextColor(GxEPD_LIGHTGREY);
    display.setCursor(umx, umy);
    display.print(display.epd2.hasPartialUpdate ? spm : npm);
  }
  while (display.nextPage());
  //Serial.println("helloFourGreyLevels done");
}

void helloArduino()
{
  //Serial.println("helloArduino");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_DARKGREY);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // align with centered HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // height might be different
  display.getTextBounds(HelloArduino, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t y = ((display.height() / 4) - tbh / 2) - tby; // y is base line!
  // make the window big enough to cover (overwrite) descenders of previous text
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = (display.height() / 4) - wh / 2;
  display.setPartialWindow(0, wy, display.width(), wh);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    //display.drawRect(x, y - tbh, tbw, tbh, GxEPD_BLACK);
    display.setCursor(x, y);
    display.print(HelloArduino);
  }
  while (display.nextPage());
  delay(1000);
  //Serial.println("helloArduino done");
}

void helloEpaper()
{
  //Serial.println("helloEpaper");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_LIGHTGREY);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // align with centered HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // height might be different
  display.getTextBounds(HelloEpaper, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t y = (display.height() * 3 / 4) + tbh / 2; // y is base line!
  // make the window big enough to cover (overwrite) descenders of previous text
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = (display.height() * 3 / 4) - wh / 2;
  display.setPartialWindow(0, wy, display.width(), wh);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloEpaper);
  }
  while (display.nextPage());
  //Serial.println("helloEpaper done");
}

#if defined(ESP8266) || defined(ESP32)
#include <StreamString.h>
#define PrintString StreamString
#else
class PrintString : public Print, public String
{
  public:
    size_t write(uint8_t data) override
    {
      return concat(char(data));
    };
};
#endif

void helloValue(double v, int digits)
{
  //Serial.println("helloValue");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
  PrintString valueString;
  valueString.print(v, digits);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(valueString, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = (display.height() * 3 / 4) + tbh / 2; // y is base line!
  // show what happens, if we use the bounding box for partial window
  uint16_t wx = (display.width() - tbw) / 2;
  uint16_t wy = (display.height() * 3 / 4) - tbh / 2;
  display.setPartialWindow(wx, wy, tbw, tbh);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(valueString);
  }
  while (display.nextPage());
  delay(2000);
  // make the partial window big enough to cover the previous text
  uint16_t ww = tbw; // remember window width
  display.getTextBounds(HelloEpaper, 0, 0, &tbx, &tby, &tbw, &tbh);
  // adjust, because HelloEpaper was aligned, not centered (could calculate this to be precise)
  ww = max(ww, uint16_t(tbw + 12)); // 12 seems ok
  wx = (display.width() - tbw) / 2;
  // make the window big enough to cover (overwrite) descenders of previous text
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  wy = (display.height() * 3 / 4) - wh / 2;
  display.setPartialWindow(wx, wy, ww, wh);
  // alternately use the whole width for partial window
  //display.setPartialWindow(0, wy, display.width(), wh);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(valueString);
  }
  while (display.nextPage());
  //Serial.println("helloValue done");
}

void deepSleepTest()
{
  //Serial.println("deepSleepTest");
  const char hibernating[] = "hibernating ...";
  const char wokeup[] = "woke up";
  const char from[] = "from deep sleep";
  const char again[] = "again";
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center text
  display.getTextBounds(hibernating, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(hibernating);
  }
  while (display.nextPage());
  display.hibernate();
  delay(5000);
  display.getTextBounds(wokeup, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t wx = (display.width() - tbw) / 2;
  uint16_t wy = (display.height() / 3) + tbh / 2; // y is base line!
  display.getTextBounds(from, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t fx = (display.width() - tbw) / 2;
  uint16_t fy = (display.height() * 2 / 3) + tbh / 2; // y is base line!
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(wx, wy);
    display.print(wokeup);
    display.setCursor(fx, fy);
    display.print(from);
  }
  while (display.nextPage());
  delay(5000);
  display.getTextBounds(hibernating, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hx = (display.width() - tbw) / 2;
  uint16_t hy = (display.height() / 3) + tbh / 2; // y is base line!
  display.getTextBounds(again, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t ax = (display.width() - tbw) / 2;
  uint16_t ay = (display.height() * 2 / 3) + tbh / 2; // y is base line!
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hx, hy);
    display.print(hibernating);
    display.setCursor(ax, ay);
    display.print(again);
  }
  while (display.nextPage());
  display.hibernate();
  //Serial.println("deepSleepTest done");
}

void showGreyLevels()
{
  display.clearScreen();
  display.setRotation(0);
  uint16_t h = display.height() / 4;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 0, display.width(), h, GxEPD_WHITE);
    display.fillRect(0, h, display.width(), h, GxEPD_LIGHTGREY);
    display.fillRect(0, 2 * h, display.width(), h, GxEPD_DARKGREY);
    display.fillRect(0, 3 * h, display.width(), h, GxEPD_BLACK);
  }
  while (display.nextPage());
  delay(2000);
}

void showBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial)
{
  //Serial.println("showBox");
  display.setRotation(1);
  if (partial)
  {
    display.setPartialWindow(x, y, w, h);
  }
  else
  {
    display.setFullWindow();
  }
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(x, y, w, h, GxEPD_BLACK);
  }
  while (display.nextPage());
  //Serial.println("showBox done");
}

void drawCornerTest()
{
  display.setFullWindow();
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  for (uint16_t r = 0; r <= 4; r++)
  {
    display.setRotation(r);
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
      display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
      display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
      display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);
      display.setCursor(display.width() / 2, display.height() / 2);
      display.print(display.getRotation());
    }
    while (display.nextPage());
    delay(2000);
  }
}


void drawFont(const char name[], const GFXfont* f)
{
  //display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
  display.setTextColor(GxEPD_DARKGREY);
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
}


void showFont(const char name[], const GFXfont* f)
{
  display.setFullWindow();
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    drawFont(name, f);
  }
  while (display.nextPage());
}

// note for partial update window and setPartialWindow() method:
// partial update window size and position is on byte boundary in physical x direction
// the size is increased in setPartialWindow() if x or w are not multiple of 8 for even rotation, y or h for odd rotation
// see also comment in GxEPD2_4G_4G.h, GxEPD2_3C.h or GxEPD2_GFX.h for method setPartialWindow()
// showPartialUpdate() purposely uses values that are not multiples of 8 to test this

void showPartialUpdate()
{
  // some useful background
  helloWorld();
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
      //display.fillScreen(GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(1000);
  }
  //return;
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    for (uint16_t i = 1; i <= 10; i += incr)
    {
      display.firstPage();
      do
      {
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.setCursor(box_x, cursor_y);
        display.print(value * i, 2);
      }
      while (display.nextPage());
      delay(500);
    }
    delay(500);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(500);
  }
}


#ifdef _GxBitmaps104x212_H_
void drawBitmaps104x212()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3
  };
#endif
  if (display.epd2.panel == GxEPD2_4G::GDEW0213I5F)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_LIGHTGREY);
        display.drawBitmap(0, display.epd2.HEIGHT, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawBitmap(display.epd2.WIDTH, display.epd2.HEIGHT, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawBitmap(display.epd2.WIDTH, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
        display.drawBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(1000);
    }
  }
}
#endif

#ifdef _GxBitmaps128x296_H_
void drawBitmaps128x296()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296, first128x296, second128x296, third128x296
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap128x296_1, logo128x296 //, first128x296, second128x296, third128x296
  };
#endif
  if (display.epd2.panel == GxEPD2_4G::GDEH029A1)
  {
    bool m = display.mirror(true);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(500);
    }
    display.mirror(m);
  }
}
#endif

#ifdef _GxBitmaps176x264_H_
void drawBitmaps176x264()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap176x264_1, Bitmap176x264_2, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap176x264_1, Bitmap176x264_2 //, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5
  };
#endif
  if (display.epd2.panel == GxEPD2_4G::GDEW027W3)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(500);
    }
  }
}
#endif

#ifdef _GxBitmaps240x416_H_
void drawBitmaps240x416()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap240x416_1, Bitmap240x416_2, Bitmap240x416_3
  };
#else
  const unsigned char* bitmaps[] =
  {
    Bitmap240x460_1, Bitmap240x460_2, Bitmap240x460_3
  };
#endif
  if (display.epd2.panel == GxEPD2_4G::GDEW0371W7)
  {
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(500);
    }
  }
}
#endif

#ifdef _GxBitmaps400x300_H_
void drawBitmaps400x300()
{
#if !defined(__AVR)
  const unsigned char* bitmaps[] =
  {
    Bitmap400x300_1, Bitmap400x300_2
  };
#else
  const unsigned char* bitmaps[] = {}; // not enough code space
#endif
  if (display.epd2.panel == GxEPD2_4G::GDEW042T2)
  {
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawGreyPixmap(Bitmap400x300_1, 1, 0, 0, 400, 300);
    }
    while (display.nextPage());
    delay(2000);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char*); i++)
    {
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
      }
      while (display.nextPage());
      delay(500);
    }
  }
}
#endif

#ifdef _GxBitmaps4g104x212_H_
void drawBitmaps4g104x212()
{
  if ((display.epd2.panel == GxEPD2_4G::GDEW075T7) || (display.epd2.panel == GxEPD2_4G::GDEW042T2) || (display.epd2.panel == GxEPD2_4G::GDEW0371W7) ||
      (display.epd2.panel == GxEPD2_4G::GDEW029T5) || (display.epd2.panel == GxEPD2_4G::GDEW029T5D) || (display.epd2.panel == GxEPD2_4G::GDEW029I6FD) ||
      (display.epd2.panel == GxEPD2_4G::GDEM029T94) || (display.epd2.panel == GxEPD2_4G::GDEW027W3) || (display.epd2.panel == GxEPD2_4G::GDEW0213I5F))
  {
    display.setFullWindow();
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawGreyPixmap(Bitmap4g104x212_1, 4, 0, 0, 104, 212);
      display.drawGreyPixmap(Bitmap4g104x212_1, 4, 104, 0, 104, 212);
      display.drawGreyPixmap(Bitmap4g104x212_1, 4, 104, 212, 104, 212);
      display.drawGreyPixmap(Bitmap4g104x212_1, 4, 0, 212, 104, 212);
    }
    while (display.nextPage());
    delay(500);
    display.epd2.drawImage_4G(Bitmap4g104x212_1, 4, 0, 0, 208, 424, false, false, true);
    delay(500);
  }
}
#endif

#ifdef _GxBitmaps4g128x296_H_
void drawBitmaps4g128x296()
{
  if ((display.epd2.panel == GxEPD2_4G::GDEW075T7) || (display.epd2.panel == GxEPD2_4G::GDEW042T2) || (display.epd2.panel == GxEPD2_4G::GDEW0371W7) ||
      (display.epd2.panel == GxEPD2_4G::GDEW029T5) || (display.epd2.panel == GxEPD2_4G::GDEW029T5D) || (display.epd2.panel == GxEPD2_4G::GDEW029I6FD) ||
      (display.epd2.panel == GxEPD2_4G::GDEM029T94) || (display.epd2.panel == GxEPD2_4G::GDEW027W3) || (display.epd2.panel == GxEPD2_4G::GDEW0213I5F))
  {
    display.setFullWindow();
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawGreyPixmap(Bitmap4g128x296_1, 4, 0, 0, 128, 296);
    }
    while (display.nextPage());
    delay(500);
    display.epd2.drawImage_4G(Bitmap4g128x296_1, 4, 0, 0, 128, 296, false, false, true);
    delay(500);
  }
}
#endif

#ifdef _GxBitmaps4g_I6FD_128x296_H_
void drawBitmaps4g_I6FD_128x296()
{
  if ((display.epd2.WIDTH >= 128) && (display.epd2.HEIGHT >= 296))
  {
    display.epd2.writeImage_4G(Bitmap4g128x296_I6FD, 4, 0, 0, 128, 296, false, false, true); 
    display.epd2.writeImage_4G(Bitmap4g128x296_I6FD, 4, 128, 0, 128, 296, false, false, true); 
    display.epd2.writeImage_4G(Bitmap4g128x296_I6FD, 4, 128, 296, 128, 296, false, false, true); 
    display.epd2.writeImage_4G(Bitmap4g128x296_I6FD, 4, 0, 296, 128, 296, false, false, true); 
    display.epd2.writeImage_4G(Bitmap4g128x296_I6FD, 4, 256, 296, 128, 296, false, false, true); 
    display.epd2.drawImage_4G(Bitmap4g128x296_I6FD, 4, 256, 0, 128, 296, false, false, true); 
    delay(5000);
    // display.drawImage_4G(Bitmap128x296_I6FD_1, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_I6FD_2, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run6, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run5, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run1, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run2, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run3, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run4, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run5, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap128x296_run6, 0, 0, 128, 296, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x64_man1, 24, 0, 80, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x64_man2, 24, 0, 80, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x64_man3, 24, 0, 80, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x64_man4, 24, 0, 80, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x64_man5, 24, 0, 80, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap24x80_gooddisplay, 128 - 24, (296 - 80) / 2, 24, 80, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x24_gooddisplay1, 128 - 80, 296 - 24, 80, 24, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap80x24_gooddisplay2, 128 - 80, 296 - 24, 80, 24, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num1, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num2, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num3, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num4, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num5, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num6, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num7, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num8, 0, 120, 32, 64, false, false, true); delay(2000);
    // display.drawImage_4G(Bitmap32x64_num9, 0, 120, 32, 64, false, false, true); delay(2000);
  }
}
#endif

#ifdef _GxBitmaps4g176x264_H_
void drawBitmaps4g176x264()
{
  if ((display.epd2.panel == GxEPD2_4G::GDEW075T7) || (display.epd2.panel == GxEPD2_4G::GDEW042T2) || (display.epd2.panel == GxEPD2_4G::GDEW0371W7) ||
      (display.epd2.panel == GxEPD2_4G::GDEW029T5) || (display.epd2.panel == GxEPD2_4G::GDEW029T5D) || (display.epd2.panel == GxEPD2_4G::GDEW029I6FD) ||
      (display.epd2.panel == GxEPD2_4G::GDEM029T94) || (display.epd2.panel == GxEPD2_4G::GDEW027W3) || (display.epd2.panel == GxEPD2_4G::GDEW0213I5F))
  {
    display.setFullWindow();
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawGreyPixmap(Bitmap4g176x264_1, 4, 0, 0, 176, 264);
    }
    while (display.nextPage());
    delay(2000);
    display.epd2.drawImage_4G(Bitmap4g176x264_1, 4, 0, 0, 176, 264, false, false, true);
    delay(2000);
  }
}
#endif

#ifdef _GxBitmaps4g400x300_H_
void drawBitmaps4g400x300()
{
  if ((display.epd2.panel == GxEPD2_4G::GDEW075T7) || (display.epd2.panel == GxEPD2_4G::GDEW042T2) || (display.epd2.panel == GxEPD2_4G::GDEW0371W7) ||
      (display.epd2.panel == GxEPD2_4G::GDEW029T5) || (display.epd2.panel == GxEPD2_4G::GDEW029T5D) || (display.epd2.panel == GxEPD2_4G::GDEW029I6FD) ||
      (display.epd2.panel == GxEPD2_4G::GDEM029T94) || (display.epd2.panel == GxEPD2_4G::GDEW027W3) || (display.epd2.panel == GxEPD2_4G::GDEW0213I5F))
  {
    display.setFullWindow();
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    for (uint16_t r = 0; r < 4; r++)
    {
      display.setRotation(r);
      display.firstPage();
      do
      {
        display.fillScreen(GxEPD_WHITE);
        display.drawGreyPixmap(Bitmap4g400x300_1, 4, 0, 0, 400, 300);
        display.setCursor(display.width() / 2, display.height() / 2);
        display.print(r);
      }
      while (display.nextPage());
      delay(2000);
    }
    display.epd2.clearScreen();
    display.epd2.drawImage_4G(Bitmap4g400x300_1, 4, 0, 0, 400, 300, false, false, true);
    delay(2000);
    //display.epd2.clearScreen();
    //delay(1000);
    //display.epd2.drawImagePart_4G(Bitmap4g400x300_1, 4, 100, 100, 400, 300, 0, 0, 300, 200, false, false, true);
    //delay(2000);
  }
}
#endif

#ifdef _GxBitmaps4g800x480_H_
void drawBitmaps4g800x480()
{
  if (display.epd2.panel == GxEPD2_4G::GDEW075T7)

  {
    //Serial.print("sizeof(Bitmap4g800x480_1) is "); Serial.println(sizeof(Bitmap4g800x480_1));
    display.epd2.drawImage_4G(Bitmap4g800x480_1, 2, 0, 0, 800, 480, true, false, true);
    delay(2000);
    //display.epd2.clearScreen();
    //delay(1000);
    //display.epd2.drawImagePart_4G(Bitmap4g800x480_1, 2, 100, 100, 800, 480, 0, 0, 700, 380, true, false, true);
    //delay(2000);
  }
}
#endif

#ifdef _GxBitmaps2g104x104_H_
void drawBitmaps2g104x104()
{
  //Serial.print("sizeof(Bitmap2g104x104) is "); Serial.println(sizeof(Bitmap2g104x104));
  display.epd2.clearScreen();
  display.epd2.drawImage_4G(Bitmap2g104x104, 2, display.epd2.WIDTH / 2 - 52, display.epd2.HEIGHT / 2 - 52, 104, 104, false, false, true);
  delay(2000);
  for (uint16_t r = 0; r <= 4; r++)
  {
    display.setRotation(r);
    display.firstPage();
    do
    {
      display.fillScreen(GxEPD_WHITE);
      display.drawGreyPixmap(Bitmap2g104x104, 2, display.width() / 2 - 52, display.height() / 2 - 52, 104, 104);
    }
    while (display.nextPage());
    delay(2000);
  }
}
#endif


void drawBitmaps()
{
  display.setFullWindow();
#ifdef _GxBitmaps104x212_H_
  Serial.println("1016");
  drawBitmaps104x212();
#endif
#ifdef _GxBitmaps128x250_H_
  Serial.println("1020");
  drawBitmaps128x250();
#endif
#ifdef _GxBitmaps128x296_H_
  Serial.println("1024");
  drawBitmaps128x296();
#endif
#ifdef _GxBitmaps176x264_H_
  Serial.println("1028");
  drawBitmaps176x264();
#endif
#ifdef _GxBitmaps400x300_H_
  Serial.println("1032");
  drawBitmaps400x300();
#endif
#ifdef _GxBitmaps4g104x212_H_
  Serial.println("1036");
  drawBitmaps4g104x212();
#endif
#ifdef _GxBitmaps4g128x296_H_
  Serial.println("1040");
  drawBitmaps4g128x296();
#endif
#ifdef _GxBitmaps4g_I6FD_128x296_H_
  Serial.println("1044");
  drawBitmaps4g_I6FD_128x296();
#endif
#ifdef _GxBitmaps4g176x264_H_
  Serial.println("1048");
  drawBitmaps4g176x264();
#endif
#ifdef _GxBitmaps4g400x300_H_
  Serial.println("1052");
  drawBitmaps4g400x300();
#endif
#ifdef _GxBitmaps4g800x480_H_
  Serial.println("1056");
  drawBitmaps4g800x480();
#endif
#ifdef _GxBitmaps2g104x104_H_
  Serial.println("1060");
  // drawBitmaps2g104x104();
#endif
}



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
#if defined(ARDUINO_ARCH_RP2040) && defined(ARDUINO_RASPBERRY_PI_PICO)
  // uncomment next line for use with GoodDisplay DESPI-PICO, or use the extended init method
  display.epd2.selectSPI(SPI0, SPISettings(4000000, MSBFIRST, SPI_MODE0));
  // uncomment next 2 lines to allow recovery from configuration failures
  pinMode(15, INPUT_PULLUP); // safety pin
  while (!digitalRead(15)) delay(100); // check safety pin for fail recovery
#endif
  display.init(115200);
  // first update should be full refresh
  helloWorld();
  delay(1000);

  display.epd2.drawGreyLevels();
  delay(1000);
  
  //  return;
  helloFourGreyLevels();
  delay(1000);
  //return;
  helloArduino();
  delay(1000);
  helloEpaper();
  delay(1000);
  //helloValue(123.9, 1);
  //delay(1000);
  showFont("FreeMonoBold9pt7b", &FreeMonoBold9pt7b);
  delay(1000);
  drawBitmaps();
  showGreyLevels();

  // display.fillScreen(GxEPD_BLACK);
  // display.display(true);
  // delay(300);
  display.fillScreen(GxEPD_DARKGREY);
  display.display(true);
  delay(300);
  display.fillScreen(GxEPD_LIGHTGREY);
  display.display(true);
  delay(300);
  display.fillScreen(GxEPD_WHITE);
  display.display(true);
  delay(300);

  display.epd2.drawGreyLevels();
  delay(1000);

  display.fillScreen(GxEPD_WHITE);
  display.display(false);
  display.fillScreen(GxEPD_WHITE);
  display.display(false);
  display.fillScreen(GxEPD_WHITE);
  display.display(false);

  display.powerOff();
  // return;

  // if (display.epd2.hasPartialUpdate)
  // {
  //   showPartialUpdate();
  //   delay(1000);
  // } // else // on GDEW0154Z04 only full update available, doesn't look nice
  // //drawCornerTest();
  // //showBox(16, 16, 48, 32, false);
  // //showBox(16, 56, 48, 32, true);
  // display.powerOff();
  // deepSleepTest();
  // Serial.println("setup done");
}

void loop()
{
}
