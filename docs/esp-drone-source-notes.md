# ESP-Drone Source Notes

This note tracks the ESP32 drone reference design found through the DigiKey / CircuitDigest article.

## Primary source

- Upstream repository: https://github.com/Circuit-Digest/ESP-Drone
- Project article: https://www.digikey.com/en/maker/projects/a-step-by-step-guide-to-build-a-low-cost-drone-using-esp32/8afccd0690574bcebfa0d2ad6fd0a391
- CircuitDigest project page: https://circuitdigest.com/microcontroller-projects/DIY-wifi-controlled-drone
- Related official base project: https://github.com/espressif/esp-drone

## Why this matters for Drone Libre / Drone Companion

The project is useful as an open ESP32 flight-controller reference:

- ESP32 based Wi-Fi control
- MPU6050 stabilization
- USB programming
- LiPo charging/power management
- Motor driver circuits
- ESP-IDF firmware structure
- Expandable design suitable for sensors such as ToF, optical flow, barometer, GPS, or companion telemetry

## Mirror location

The GitHub Actions workflow `.github/workflows/mirror-esp-drone.yml` mirrors the upstream repository into:

`mirrors/ESP-Drone/`

Run the workflow manually from the repository Actions tab, or let the weekly schedule update it.

## Caution notes

This is a brushed-motor micro drone design. Treat it as a learning and reference platform, not the final architecture for a brushless Drone Libre aircraft. For future work, compare the Circuit-Digest fork against Espressif's official ESP-Drone project before making design decisions.
