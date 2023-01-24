#ifndef PDTVTPAPER_INIT_H
#define PDTVTPAPER_INIT_H

#include "pdtvt.h"
#include "utils.h"
#include "screens/splashScreen.h"

namespace pdtvt {
    void drawSplashScreen() {
        pdtvt::splashScreen::draw();
    }

    void initSdCard() {
        EpBitmapMono textUpdateMask(pdtvt::gfxBuffer.width(), pdtvt::gfxBuffer.height());
        textUpdateMask.setBitmapShapeBlendMode(EpBitmap::SHAPES_ONLY);
        if (!SD.begin(SD_CS)) {
            Serial.println("[E][pdtvt] SD card initialization failed");

            pdtvt::splashScreen::showError(2,
                                           "SD card initialization failed",
                                           "WiFi will be disconnected, and no data will be logged");

            textUpdateMask.clearShapes();
            textUpdateMask.pushShape(gfxBuffer.gfxUpdatedRegion.getEpShape());
            partialDisplay.display(&gfxBuffer, epdPlacement, EpPartialDisplay::A2, &textUpdateMask, &textUpdateMask, &gfxBuffer.gfxUpdatedRegion);
            gfxBuffer.gfxUpdatedRegion.reset();
        }
        else
            Serial.println("[I][pdtvt] SD card initialized");

        Serial.printf("[V][pdtvt] Card size:   %.3fMB\n", (float) SD.cardSize() / 1000000);
        Serial.printf("[V][pdtvt] Total bytes: %lldB\n", SD.totalBytes());
        Serial.printf("[V][pdtvt] Used bytes:  %lldB\n", SD.usedBytes());
    }

    void saveConfig();

    void loadConfig() {
        if (!SD.exists(configFilePath)) {
            Serial.printf("[E][pdtvt] Config file does not exist\n");

            pdtvt::splashScreen::showError(2,
                                           "Config file does not exist",
                                           format("Make sure file %s exists", configFilePath).c_str());
        }

        File file = SD.open(configFilePath, FILE_READ);
        StaticJsonDocument<STATICJSONDOC_STACK_SIZE> doc;

        DeserializationError error = deserializeJson(doc, file);
        if (error != DeserializationError::Ok) {
            Serial.printf("[E][pdtvt] Failed to read %s, using default configs", configFilePath);

            pdtvt::splashScreen::showError(1,
                                           format("Failed to read %s, using default configs", configFilePath).c_str());
        }

        JsonArray array = doc["access points"].as<JsonArray>();
        for (auto v: array) {
            config.accessPoints.emplace_back(v["ssid"] | "undefined",
                                             v["password"] | "undefined");
        }

        file.close();

        saveConfig();
    }

    void saveConfig() {
        SD.remove(configFilePath);

        File file = SD.open(configFilePath, FILE_WRITE);
        if (!file) {
            Serial.printf("Failed to create file: %s", configFilePath);
            return;
        }

        StaticJsonDocument<STATICJSONDOC_STACK_SIZE> doc;
        for (auto &ap: config.accessPoints) {
            auto obj = doc["access points"].createNestedObject();
            obj["ssid"] = ap.ssid;
            obj["password"] = ap.password;
        }

        if (!serializeJson(doc, file)) {
            Serial.printf("Failed to serialize config file: %s", configFilePath);
        }

        file.close();
    }

    bool connectWifi() {
        WiFi.mode(WIFI_STA);

        if (config.accessPoints.empty()) {
            pdtvt::splashScreen::showError(2,
                                           "No available WiFi access points saved in the config file",
                                           R"(Example: "access points":[{"ssid":"","password":""},...])");
        }

        for (auto ap: config.accessPoints) {
            auto start = esp_timer_get_time();
            WiFi.begin(ap.ssid.c_str(), ap.password.c_str());
            Serial.printf("[I][pdtvt] Connecting to WiFi access point: %s\n", ap.ssid.c_str());
            pdtvt::splashScreen::showError(2,
                                           "Connecting to WiFi access point:",
                                           ap.ssid.c_str());
            while (WiFi.status() != WL_CONNECTED) {
                Serial.printf(".");
                delay(500);
                if ((esp_timer_get_time() - start) / 1000 >= WIFI_STA_TIMEOUT) {
                    Serial.printf("\n[W][pdtvt] WiFi access point: %s timed out\n", ap.ssid.c_str());
                    pdtvt::splashScreen::showError(2,
                                                   "Timed out trying to connect to WiFi access point:",
                                                   ap.ssid.c_str());
                    break;
                }
            }
            if (WiFi.status() == WL_CONNECTED)
                break;
        }
        if (WiFi.status() != WL_CONNECTED) {
            Serial.printf("\n[W][pdtvt] No available WiFi access points\n");
            pdtvt::splashScreen::showError(1,
                                           "No available WiFi access points");
            return false;
        }
        Serial.printf("\n[I][pdtvt] Local IP: ");
        pdtvt::splashScreen::showError(2,
                                       "WiFi connected",
                                       format("Local IP: %s", WiFi.localIP().toString().c_str()).c_str());
        Serial.print(WiFi.localIP());
        Serial.printf("\n");
        return true;
    }
};

#endif //PDTVTPAPER_INIT_H
