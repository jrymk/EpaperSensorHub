#ifndef PDTVTPAPER_UTILS_H
#define PDTVTPAPER_UTILS_H

#include <Epepd.h>

enum TextAlignmentHorizontal {
    HALIGN_LEFT,
    HALIGN_CENTER,
    HALIGN_RIGHT
};

enum TextAlignmentVertical {
    VALIGN_TOP,
    VALIGN_CENTER,
    VALIGN_BASELINE,
    VALIGN_BOTTOM
};

// tired of declaring tons these and have to worry about scopes
int16_t boundsLeft, boundsTop;
uint16_t boundsWidth, boundsHeight;
uint16_t boundsAboveBaseline, boundsBelowBaseline;

void getTextBounds(Adafruit_GFX &gfx, int16_t x, int16_t y, const GFXfont* font, const char* str) {
    if (font)
        gfx.setFont(font);
    gfx.getTextBounds(str, x, y, &boundsLeft, &boundsTop, &boundsWidth, &boundsHeight);
    boundsAboveBaseline = boundsTop - x;
    boundsBelowBaseline = x - (boundsTop + boundsHeight);
}

void debugBounds(Adafruit_GFX &gfx, uint16_t color) {
    gfx.drawRect(boundsLeft, boundsTop, boundsWidth, boundsHeight, color);
}

void drawText(Adafruit_GFX &gfx, uint16_t color, const GFXfont* font, const char* str) {
    if (font)
        gfx.setFont(font);
    gfx.setTextColor(color);
    gfx.print(str);
}

void drawText(Adafruit_GFX &gfx, int16_t x, int16_t y, uint16_t color, const GFXfont* font, const char* str) {
    if (font)
        gfx.setFont(font);
    gfx.setCursor(x, y);
    gfx.setTextColor(color);
    gfx.print(str);
}

template<typename... Args>
void drawTextStr(Adafruit_GFX &gfx, int16_t x, int16_t y, TextAlignmentHorizontal halign, TextAlignmentVertical valign,
                 uint16_t color, const GFXfont* font,
                 const char* str) {
    if (font)
        gfx.setFont(font);
    gfx.getTextBounds(str, x, y, &boundsLeft, &boundsTop, &boundsWidth, &boundsHeight);
    gfx.setCursor(
            halign == HALIGN_CENTER ? x - boundsWidth / 2 : halign == HALIGN_RIGHT ? x - boundsWidth : x,
            valign == VALIGN_TOP ? 2 * y - boundsTop : valign == VALIGN_BOTTOM ? 2 * y - boundsTop - boundsHeight
                                                                               : valign == VALIGN_CENTER ? 2 * y - boundsTop - boundsHeight / 2 : y
    );
    gfx.setTextColor(color);
    gfx.print(str);
}

template<typename... Args>
void drawText(Adafruit_GFX &gfx, int16_t x, int16_t y, TextAlignmentHorizontal halign, TextAlignmentVertical valign,
              uint16_t color, const GFXfont* font,
              const char* format, Args... args) {
    if (font)
        gfx.setFont(font);
    char buffer[1024];
    sscanf(buffer, format, args...);
    gfx.getTextBounds(buffer, x, y, &boundsLeft, &boundsTop, &boundsWidth, &boundsHeight);
    gfx.setCursor(
            halign == HALIGN_CENTER ? x - boundsWidth / 2 : halign == HALIGN_RIGHT ? x - boundsWidth : x,
            valign == VALIGN_TOP ? 2 * y - boundsTop : valign == VALIGN_BOTTOM ? 2 * y - boundsTop - boundsHeight
                                                                               : valign == VALIGN_CENTER ? 2 * y - boundsTop - boundsHeight / 2 : y
    );
    gfx.setTextColor(color);
    gfx.print(buffer);
}


template<typename... Args>
std::string format(const char* format, Args... args) {
    char formatBuffer[1024];
    sprintf(formatBuffer, format, args...);
    return formatBuffer;
}

#endif //PDTVTPAPER_UTILS_H
