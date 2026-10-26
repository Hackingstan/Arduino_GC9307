# Arduino_GC9307 (by HACKINGSTAN)

A highly optimized and precise hardware driver library for the **1.8-inch Bare GC9307 TFT Display (240x296 resolution)**. 

Initially engineered for a custom ESP32 DIY smartwatch project, this library solves common rendering issues found in bare (bezel-less) GC9307 panels. It acts as an extension to the popular `Arduino_GFX` library.

## 🔥 Key Features & Fixes
- **True Resolution Mapping:** Perfectly calibrated for `240x296` physical pixels with a strict `0` Y-offset.
- **Hardware Color Inversion Fix:** Overrides default initialization with `0x21` (Inversion ON) to fix RGB/BGR color swapping and negative colors.
- **Mirroring & Staircase Fix:** Forces MADCTL configuration to `0x48` for correct text alignment and rendering on rounded-corner bare panels.
- **Safe Area Calibration:** Recommends a standard 6-pixel safety margin (`drawRoundRect` with 40px radius) for UI development to avoid clipped pixels on the physical edges.

## 🛠️ Hardware Requirements
- **Microcontroller:** ESP32 (Recommended), ESP8266, Raspberry Pi Pico, or standard Arduino.
- **Display:** 1.8" Bare GC9307 TFT LCD (4-Wire SPI).
- **Dependencies:** You must have [moononournation's Arduino_GFX](https://github.com/moononournation/Arduino_GFX) installed.

## 📥 Installation
1. Download this repository as a `.ZIP` file.
2. Open the Arduino IDE.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Select the downloaded `.ZIP` file.

## 🚀 Basic Usage

```cpp
#include <Arduino_GFX_Library.h>
#include <Arduino_GC9307.h>

#define TFT_CS    5
#define TFT_DC    2
#define TFT_RST   4
#define TFT_SCK   18
#define TFT_MOSI  23

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_GC9307(bus, TFT_RST);

void setup() {
  gfx->begin();
  gfx->fillScreen(0x0000); 

  // Draw a 6-pixel safe margin for bare displays
  gfx->drawRoundRect(6, 6, 228, 284, 40, 0x001F); 
  
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(3);
  gfx->setCursor(80, 140);
  gfx->print("READY");
}

void loop() {}
