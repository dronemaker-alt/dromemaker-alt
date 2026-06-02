#pragma once

#include <stdint.h>

// ============================================================================
// Display Controller Selection
// ============================================================================
// Uncomment one of these to select the display controller type.
// Default is ST7789. Change to DISPLAY_CONTROLLER_ILI9341 if testing with ILI9341.

#define DISPLAY_CONTROLLER_ST7789
//#define DISPLAY_CONTROLLER_ILI9341

// ============================================================================
// Display Geometry and Configuration
// ============================================================================

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH   240
#endif

#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT  320
#endif

#ifndef DISPLAY_ROTATION
#define DISPLAY_ROTATION 0  // 0=normal, 1=90deg, 2=180deg, 3=270deg
#endif

#ifndef DISPLAY_SPI_FREQ_HZ
#define DISPLAY_SPI_FREQ_HZ  (40 * 1000 * 1000)  // 40 MHz
#endif

// ============================================================================
// GPIO Pin Assignments
// ============================================================================
// Adjust these for your ESP32-P4 / T-Display P4 handheld prototype.
// Defaults are based on the LilyGO T-Display reference wiring.

#ifndef LCD_SPI_HOST
#define LCD_SPI_HOST    SPI2_HOST
#endif

#ifndef PIN_LCD_MOSI
#define PIN_LCD_MOSI    19
#endif

#ifndef PIN_LCD_SCLK
#define PIN_LCD_SCLK    18
#endif

#ifndef PIN_LCD_MISO
#define PIN_LCD_MISO    -1  // Not used; set to -1 if disconnected
#endif

#ifndef PIN_LCD_CS
#define PIN_LCD_CS      5
#endif

#ifndef PIN_LCD_DC
#define PIN_LCD_DC      16
#endif

#ifndef PIN_LCD_RST
#define PIN_LCD_RST     23
#endif

#ifndef PIN_LCD_BL
#define PIN_LCD_BL      4
#endif

// ============================================================================
// Display Driver Names and Properties
// ============================================================================

#if defined(DISPLAY_CONTROLLER_ST7789)
#define DISPLAY_DRIVER_NAME "ST7789"
#define DISPLAY_INIT_CMD_BYTE 0x01  // SWRESET
#elif defined(DISPLAY_CONTROLLER_ILI9341)
#define DISPLAY_DRIVER_NAME "ILI9341"
#define DISPLAY_INIT_CMD_BYTE 0xCF  // Power Control A (ILI9341)
#else
#define DISPLAY_DRIVER_NAME "UNKNOWN"
#define DISPLAY_INIT_CMD_BYTE 0x01  // Fallback to SWRESET
#endif

// ============================================================================
// API
// ============================================================================

// Call this from app_main() to initialize the LCD and enable backlight.
void display_init(void);
