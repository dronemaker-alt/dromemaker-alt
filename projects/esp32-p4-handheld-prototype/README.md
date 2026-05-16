# ESP32-P4 Handheld Prototype

Early prototype work for a portable ESP32-P4 based handheld diagnostics/control terminal.

## Current Hardware

- ESP32-P4 development board
- 2.8 inch SPI TFT display
- PTFE prototype side plates
- Future LVGL based UI
- Planned physical buttons and telemetry interface

## Prototype Notes

The current mockup uses red PTFE plates as temporary structural side panels.

The layout already supports a modular stacked construction approach:

- Front display/control plate
- Rear electronics/battery plate
- Spacer cavity for wiring and future modules

This allows rapid iteration without redesigning a full enclosure for every hardware revision.

## Display Information

Display markings:

`2.8 TFT SPI 240x320 V1.2`

Likely controller:

- ILI9341 compatible SPI TFT

Likely onboard peripherals:

- TFT controller
- SD card slot
- Touch controller

## Development Plan

1. Bring up display on ESP32-P4
2. Verify TFT driver
3. Run LVGL demo
4. Add touch input
5. Add physical controls
6. Create menu architecture
7. Add telemetry and diagnostics
8. Finalize enclosure and power system

## Design Direction

The intent is a rugged field-service style handheld device rather than a thin consumer-style product.

Construction philosophy:

- Modular
- Repairable
- Easy to revise
- Prototype friendly

Aviation and industrial equipment design principles are preferred over ultra-thin consumer electronics.
