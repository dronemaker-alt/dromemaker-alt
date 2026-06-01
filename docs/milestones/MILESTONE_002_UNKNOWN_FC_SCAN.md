# DroneLibre Milestone 002 – Unknown Flight Controller Scan

Date: 2026-05-31

## Objective

Validate DroneLibre against a truly unknown flight-controller board from the Nazgul acquisition parts group.

This test followed the successful APM discovery milestone and was intended to confirm that DroneLibre can handle non-APM hardware without falsely identifying it or crashing.

## Hardware Under Test

Visual board markings:

- `LISHI-T`
- `F4 V2`
- `FRONT` orientation arrow

Observed physical traits:

- STM32-class flight controller
- 30.5 x 30.5 mm mounting pattern
- USB connector present
- Side solder pads for motors, UARTs, power, and peripherals
- Red power/status LED active when connected by USB

Likely hardware class:

- STM32 F4 flight controller
- Betaflight / Cleanflight / INAV style board
- From Nazgul acquisition parts lot

## Windows USB Identification

Device Manager identified the board as:

```text
STMicroelectronics Virtual COM Port (COM15)
```

This confirms:

- USB interface is alive
- STM32 MCU is responding at the USB level
- Windows assigned a virtual COM port
- Board is not electrically dead

A separate bootloader-style observation was also made in Device Manager during exploration:

```text
STM32 BOOTLOADER
Camera DFU Device
```

This indicates the board can likely enter STM32 DFU / bootloader mode.

## DroneLibre Commands Tested

### APM Scanner Rejection Test

Command:

```powershell
python -m src.cli scan-apm COM15
```

Result:

```text
RuntimeError: No startup banner received from port COM15
```

Interpretation:

- COM15 opened successfully
- Board did not emit an ArduPilot/APM startup banner
- DroneLibre correctly did not identify the board as APM

This was a useful negative test.

### Unknown Board Scan

Command:

```powershell
python -m src.cli scan-unknown COM15
```

Observed output included:

```text
Scanning unknown port: COM15
Port: COM15
Baud: 115200
USB Device: STMicroelectronics Virtual COM Port (COM15)
Bytes Received: 0
MAVLink Detected: False
MSP (Betaflight) Detected: False
INAV Detected: False
Status: unknown
```

JSON-style result included:

```json
{
  "port": "COM15",
  "baud": 115200,
  "usb_device": "STMicroelectronics Virtual COM Port (COM15)",
  "raw_bytes_hex": "",
  "bytes_count": 0,
  "mavlink_detected": false,
  "msp_detected": false,
  "inav_detected": false,
  "status": "unknown"
}
```

### Multi-Baud Unknown Scan

Command:

```powershell
python -m src.cli scan-unknown COM15 --all-bauds --output reports
```

Observed output:

```text
Probing multiple baud rates: [115200, 57600, 38400, 19200]
Baud 115200: unknown
Baud 57600: unknown
Baud 38400: unknown
Baud 19200: unknown
Scanned 4 baud rates
```

Interpretation:

- Multi-baud sweep works
- Board remained silent across tested baud rates
- No MAVLink heartbeat detected
- No MSP / Betaflight response detected
- No INAV string response detected
- Tool did not crash
- Unknown result was recorded cleanly

## DroneLibre Capability Added

### `scan-unknown`

New behavior:

1. Accepts a serial COM port.
2. Queries the USB device name from the available serial port list.
3. Opens the port safely.
4. Reads raw bytes from the serial connection.
5. Attempts MAVLink heartbeat detection.
6. Attempts MSP / Betaflight-style detection.
7. Attempts INAV string detection.
8. Returns a structured result even when no protocol is detected.
9. Saves unknown-board results to the reports directory.
10. Does not raise an exception for silent or unidentified devices.

### `--all-bauds`

New behavior:

- Probes multiple baud rates.
- Current sweep list:
  - 115200
  - 57600
  - 38400
  - 19200
- Aggregates each attempt into a single result set.
- Prints a concise summary for bench troubleshooting.

## Test Result Summary

| Test | Port | Baud | USB Device | MAVLink | MSP | INAV | Result |
|---|---:|---:|---|---|---|---|---|
| APM scanner rejection | COM15 | 115200 | STMicroelectronics Virtual COM Port | N/A | N/A | N/A | Correctly rejected |
| Unknown scan | COM15 | 115200 | STMicroelectronics Virtual COM Port | False | False | False | Unknown |
| Unknown all-baud sweep | COM15 | 115200 | STMicroelectronics Virtual COM Port | False | False | False | Unknown |
| Unknown all-baud sweep | COM15 | 57600 | STMicroelectronics Virtual COM Port | False | False | False | Unknown |
| Unknown all-baud sweep | COM15 | 38400 | STMicroelectronics Virtual COM Port | False | False | False | Unknown |
| Unknown all-baud sweep | COM15 | 19200 | STMicroelectronics Virtual COM Port | False | False | False | Unknown |

## Engineering Significance

This milestone proves DroneLibre can handle both positive and negative hardware identification cases:

- Known APM board: correctly identified.
- Unknown STM32 board: correctly not misidentified.
- Silent board: handled without crashing.
- Multi-baud scan: completed successfully.
- USB descriptor evidence: captured.

This is the beginning of DroneLibre as a general flight-controller discovery and bench archaeology tool.

## Current Interpretation of the LISHI-T F4 V2 Board

The board is not dead.

Evidence:

- Red LED powers on.
- Windows enumerates it as an STM32 virtual COM device.
- Device Manager can show STM32 bootloader/DFU-style entries.

The board is currently quiet over normal serial probing.

Likely possibilities:

1. Firmware is present but quiet until the correct protocol handshake is sent.
2. Betaflight/MSP handshake needs refinement.
3. Firmware may be erased, corrupted, or incomplete.
4. Board may need DFU mode and firmware recovery.
5. Board may require Betaflight Configurator to confirm target and firmware state.

## Recommended Next Steps

1. Test the board in Betaflight Configurator.
2. Record whether Betaflight connects to COM15.
3. If Betaflight connects, capture target name and firmware version.
4. If Betaflight does not connect, enter DFU mode and confirm STM32 BOOTLOADER presence.
5. Add a DroneLibre `scan-dfu` command to detect STM32 bootloader devices.
6. Improve MSP handshake logic for Betaflight/Cleanflight/INAV boards.
7. Add VID/PID capture to `scan-unknown` reports.
8. Save raw USB descriptor information alongside serial scan results.
9. Add `scan-all` to enumerate all connected COM ports and run discovery automatically.

## Status

Operational unknown-board scan prototype.

DroneLibre now successfully identifies known APM hardware and safely classifies silent STM32 flight-controller hardware as unknown without crashing or false identification.
