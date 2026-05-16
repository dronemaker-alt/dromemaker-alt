# ESP32-P4 Hardware Notes

## Board Identified

Guition JC-ESP32P4-M3 development board.

Module markings:

- JC-ESP32P4-M3
- SOC: ESP32P4NRW32
- Memory: 32M PSRAM
- Flash: 16M
- WiFi: ESP32-C6

## Notable Features

Integrated subsystems visible from documentation and board inspection:

- ESP32-P4 main processor
- ESP32-C6 wireless companion processor
- Ethernet interface
- Dual USB-C
- SD card slot
- Camera connector
- Audio support
- Expansion connectors
- LoRa support
- GPS support
- IMU support
- AMOLED display support

## Development Strategy

### Phase 1
Use inexpensive SPI TFT display for:

- LVGL learning
- Driver testing
- Menu prototyping
- Hardware experimentation

### Phase 2
Transition to AMOLED display platform:

- Capacitive touch interface
- Telemetry dashboard
- Drone diagnostics
- Portable field terminal UI
- Sensor integration

## Mechanical Notes

Current temporary structure:

- Red PTFE side plates
- Modular stacked construction
- Serviceable prototype layout

Recommended direction:

- Brass standoffs
- Threaded inserts
- Layered avionics-style construction
- Modular service access

## UI Inspiration

Design references:

- Industrial avionics
- Mobile suit maintenance terminals
- Drone field diagnostics
- Cyberdeck style interfaces
- Ruggedized field equipment

## Future Ideas

Potential integrated functions:

- Drone telemetry
- Mission planning
- Portable diagnostics
- Sensor fusion display
- OTA firmware tools
- ESP32 fleet programming
- Portable RF analysis
- MAVLink interface
