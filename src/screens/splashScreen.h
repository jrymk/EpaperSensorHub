#ifndef PDTVTPAPER_SPLASHSCREEN_H
#define PDTVTPAPER_SPLASHSCREEN_H

#include "../pdtvt.h"
#include <cstdarg>

namespace pdtvt {
    namespace splashScreen {
        void draw() {
            partialDisplay.clear();

            gfxBuffer.fillScreen(GFX_WHITE);
            getTextBounds(gfxBuffer, 0, 0, &FONT_TITLE, "pdtvtPaper");
            drawText(gfxBuffer, 16, gfxBuffer.height() - 96, COLOR_LOGO_pdtvt, &FONT_TITLE, "pdtvt");
            drawText(gfxBuffer, COLOR_LOGO_Paper, &FONT_TITLE, "Paper");
            greyscaleDisplay.display(&gfxBuffer, epdPlacement, EpGreyscaleDisplay::GC16);
            gfxBuffer.gfxUpdatedRegion.reset();
        }

        void showError(uint8_t lines, ...) {
            EpBitmapMono textUpdateMask(gfxBuffer.width(), gfxBuffer.height());
            textUpdateMask.setBitmapShapeBlendMode(EpBitmap::SHAPES_ONLY);

            va_list vaList;
            va_start(vaList, lines);
            for (uint8_t i = 0; i < lines; i++) {
                auto str = va_arg(vaList, const char*);
                Serial.println(str);
                drawTextStr(gfxBuffer, 16, gfxBuffer.height() - 16 - DIMEN_BODY_LINE_HEIGHT * (lines - 1 - i), HALIGN_LEFT, VALIGN_BASELINE,
                            COLOR_BODY, &FONT_BODY,
                            str);
            }
            va_end(vaList);

            textUpdateMask.clearShapes();
            textUpdateMask.pushShape(gfxBuffer.gfxUpdatedRegion.getEpShape());
            partialDisplay.display(&gfxBuffer, epdPlacement, EpPartialDisplay::GC2_PARTIAL, &textUpdateMask, nullptr, &gfxBuffer.gfxUpdatedRegion);
            EpRegion copy(gfxBuffer.gfxUpdatedRegion);
            gfxBuffer.gfxUpdatedRegion.reset();
            gfxBuffer.fillRect(copy.x, copy.y, copy.w + 1, copy.h + 1, GFX_WHITE); // no idea why I need to +1
        }
    }
}

#endif //PDTVTPAPER_SPLASHSCREEN_H
