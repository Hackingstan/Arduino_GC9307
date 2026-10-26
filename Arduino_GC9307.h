#ifndef _ARDUINO_GC9307_H_
#define _ARDUINO_GC9307_H_

#include <Arduino_GFX_Library.h>

class Arduino_GC9307 : public Arduino_ST7789 {
  public:
    // row_offset1 और row_offset2 को 12 से बदलकर 0 कर दिया गया है
    Arduino_GC9307(
      Arduino_DataBus *bus, int8_t rst = GFX_NOT_DEFINED, uint8_t r = 0, 
      bool ips = false, int16_t w = 240, int16_t h = 296, 
      int16_t col_offset1 = 0, int16_t row_offset1 = 0, 
      int16_t col_offset2 = 0, int16_t row_offset2 = 0);

    void tftInit() override;
    void setRotation(uint8_t r) override;
};

#endif
