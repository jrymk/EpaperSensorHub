#ifndef PDTVTPAPER_CONFIG_H
#define PDTVTPAPER_CONFIG_H

#define LED_PIN 5 // built in RGB LED on the Firebeetle 2
#define EPAPER_CS 25
#define EPAPER_DC 4
#define EPAPER_RST 13
#define EPAPER_BUSY 39
#define CO2_TX 16 // UART_TxD pin on Senseair S8
#define CO2_RX 17 // UART_RxD pin on Senseair S8
#define SD_CS 27
#define BTN_PIN 26

#define STATICJSONDOC_STACK_SIZE 256
#define WIFI_STA_TIMEOUT 20000

const char* configFilePath = "/config.json";


struct WifiCredentials {
    std::string ssid;
    std::string password;

    WifiCredentials(const char* ssid, const char* password) : ssid(ssid), password(password) {}
};

struct Config {
    std::vector<WifiCredentials> accessPoints;
} config;

#endif //PDTVTPAPER_CONFIG_H
