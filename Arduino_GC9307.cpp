#include "Arduino_GC9307.h"

Arduino_GC9307::Arduino_GC9307(
  Arduino_DataBus *bus, int8_t rst, uint8_t r, 
  bool ips, int16_t w, int16_t h, 
  int16_t col_offset1, int16_t row_offset1, 
  int16_t col_offset2, int16_t row_offset2)
  : Arduino_ST7789(bus, rst, r, ips, w, h, col_offset1, row_offset1, col_offset2, row_offset2) {}

void Arduino_GC9307::tftInit() {
  if (_rst != GFX_NOT_DEFINED) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH); delay(50);
    digitalWrite(_rst, LOW); delay(120);
    digitalWrite(_rst, HIGH); delay(120);
  }

  _bus->beginWrite();
  _bus->writeCommand(0x01); // Software Reset
  _bus->endWrite();
  delay(120);

  _bus->beginWrite();
  _bus->writeCommand(0x11); // Sleep Out
  _bus->endWrite();
  delay(120);

  _bus->beginWrite();
  
  _bus->writeCommand(0x3A); // COLMOD
  _bus->write(0x05);        // 16-bit (RGB565)
  _bus->writeCommand(0x20); // Display Inversion OFF (True Colors)
  _bus->writeCommand(0x29); // Display ON
  
  _bus->endWrite();

  // NOISE FIX: 
  _bus->beginWrite();
  _bus->writeCommand(0x2A); 
  _bus->write16(0); _bus->write16(239);
  _bus->writeCommand(0x2B); 
  _bus->write16(0); _bus->write16(319);
  _bus->writeCommand(0x2C); 
  for(uint32_t i = 0; i < 76800; i++) {
    _bus->write16(0x0000); 
  }
  _bus->endWrite();
}

// MIRROR FIX: 
void Arduino_GC9307::setRotation(uint8_t r) {
  Arduino_ST7789::setRotation(r); 
  
  _bus->beginWrite();
  _bus->writeCommand(0x36); 
  _bus->write(0x48); // 0x48 (Mirror Fix)
  _bus->endWrite();
}
