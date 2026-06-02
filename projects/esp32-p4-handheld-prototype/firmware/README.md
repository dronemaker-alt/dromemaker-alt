# ESP32-P4 Handheld Prototype Firmware

This firmware scaffold was generated to support the ESP32-P4 handheld prototype using the LilyGO T-Display reference for display/backlight wiring.

## Goals

- Preserve diagnostic startup messages:
  - `Cali prototype systems ver.0001`
  - `ESP32-P4 serial online`
- Force the TFT backlight on at boot.
- Add serial/ESP log debug messages around display initialization.
- Print display driver and pin configuration at startup.

## Display configuration

The firmware uses the following pin assignments:

- `PIN_LCD_MOSI = 19`
- `PIN_LCD_SCLK = 18`
- `PIN_LCD_CS = 5`
- `PIN_LCD_DC = 16`
- `PIN_LCD_RST = 23`
- `PIN_LCD_BL = 4`

These values are based on the LilyGO T-Display reference repo and the handheld prototype notes.

## Build

This is an ESP-IDF project. From the `firmware` folder:

```sh
idf.py set-target esp32p4
idf.py build
```

If you want to adapt this to Arduino or PlatformIO, copy `display_init.c`/`.h` and `main.c` logic into your existing project.
