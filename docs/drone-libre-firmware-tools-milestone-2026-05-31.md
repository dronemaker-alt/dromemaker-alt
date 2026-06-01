# DroneLibre Firmware Tools Milestone — 2026-05-31

## Summary

DroneLibreFirmwareTools reached a working early diagnostic milestone. The current tool can identify and record useful results from known and unknown drone/control boards through serial probing, APM banner capture, and initial DFU detection plumbing.

This milestone documents the first practical field-test session using APM2 hardware and an unknown STM-based board from the Nazgul acquisition.

## Confirmed Tool Capabilities

Current command set proven or implemented during this session:

- `analyze-all` — scans an input folder, auto-detects firmware files, runs parsers, and writes reports.
- `scan-apm` — reads an APM/ArduPilot startup banner from a serial port.
- `backup-board` — connects to an APM-style board through MAVLink and attempts parameter backup.
- `scan-unknown` — probes an unknown serial device for passive output and protocol hints.
- `scan-unknown --all-bauds` — probes an unknown serial device across common baud rates.
- `scan-dfu` — initial DFU scanner command implemented with graceful failure handling when Windows libusb/PyUSB backend is unavailable.

## Known APM2 Validation Result

A known APM2 board was used to validate the scanner.

Observed result:

```text
port: COM14
board: APM
firmware: ArduCopter
version: 3.1.5
fw_ver: 120
banner included: Init ArduCopter V3.1.5
```

This proves the serial banner reader and APM parser path are working.

## Unknown Nazgul STM Board Test

A mystery board from the Nazgul acquisition was tested as a true unknown target.

### Physical/Device Observations

- Board appears STM-based.
- Windows exposed a serial interface as:
  - `STMmicroelectronics Virtual COM Port (COM15)`
- Windows also showed a DFU-style interface:
  - `Camera DFU Device`

### Serial Scan Result

Command path:

```powershell
python -m src.cli scan-unknown COM15
python -m src.cli scan-unknown --all-bauds COM15
```

Observed result:

```text
raw_bytes_hex: ""
bytes_count: 0
mavlink_detected: false
msp_detected: false
inav_detected: false
status: unknown
```

Multi-baud probing result:

```text
COM15 @ 115200: unknown
COM15 @ 57600: unknown
COM15 @ 38400: unknown
COM15 @ 19200: unknown
```

Interpretation: the board presents a serial port but does not passively emit recognizable MAVLink, MSP, or INAV startup data at the tested baud rates. This does not mean the board is dead; it may require a protocol request, command handshake, different mode, or DFU/bootloader interaction.

### DFU Scan Result

Windows sees a DFU-like device, but Python/PyUSB currently cannot initialize the libusb backend on this machine.

Observed behavior:

```text
usb.backend.libusb1.get_backend(...) returned: None
DFU scan unavailable: libusb backend could not be initialized.
No DFU devices found.
```

Interpretation: `scan-dfu` command logic now fails cleanly instead of throwing a raw traceback. The remaining issue is Windows/PyUSB/libusb backend availability, not board detection.

## Current Findings

- Known APM2 board validates the APM/ArduPilot serial scan path.
- Unknown STM board validates the unknown serial scan path and report generation.
- Unknown board is visible to Windows through both serial and DFU-style device entries.
- Passive serial detection found no MAVLink/MSP/INAV output from the unknown STM board.
- DFU detection needs Windows libusb backend work before it can access the `Camera DFU Device` through PyUSB.

## Recommended Next Tool Additions

Add two support commands to make future board testing cleaner:

### `doctor`

Purpose: preflight check for the local software environment.

Should report:

- Python executable path
- Python version
- `pyserial` import status
- `pymavlink` import status
- `pyusb` import status
- `libusb_package` import status
- `libusb_package.find_library("libusb-1.0")` result
- `usb.backend.libusb1.get_backend(...)` result
- available serial ports

Output should use `PASS`, `WARN`, and `FAIL` status lines and never throw a raw traceback.

### `scan-usb`

Purpose: list USB devices visible to Windows even when PyUSB/libusb cannot access them.

On Windows, use a PowerShell/WMI fallback such as:

```powershell
Get-PnpDevice -PresentOnly
```

Filter likely relevant device names:

- STM
- DFU
- BOOTLOADER
- COM
- USB Serial
- Camera DFU
- CP210
- CH340
- FTDI
- Silicon Labs

Output should include:

- human-readable table
- JSON report saved to `reports/usb/usb_devices.json`
- no raw traceback on failure

## Suggested Workflow

The intended diagnostic chain is now:

```text
doctor -> scan-usb -> scan-unknown -> scan-dfu -> backup-board
```

For APM/ArduPilot boards:

```text
doctor -> scan-usb -> scan-apm -> backup-board
```

For unknown STM boards:

```text
doctor -> scan-usb -> scan-unknown --all-bauds -> scan-dfu
```

## Milestone Status

This is a successful early milestone. The tool has moved from concept to a working bench diagnostic utility with real output from known and unknown boards.

Remaining known gap: Windows DFU access through PyUSB/libusb requires further backend/driver work.
