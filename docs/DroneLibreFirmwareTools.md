# DroneLibre Firmware Tools Milestone

Date: 2026-05-31

## Summary

DroneLibreFirmwareTools has reached a useful diagnostic milestone. The tool can now interrogate known APM-style boards, attempt unknown serial board scans, perform multi-baud probing, attempt DFU discovery, and fail cleanly when the Windows USB backend is not available.

This milestone was validated on an APM2/ArduCopter board and on an unknown STM-based board from the Nazgul acquisition.

## Implemented capabilities

- `analyze-all` scans an input folder recursively and generates reports.
- `scan-apm` reads APM/ArduCopter startup banner information from a selected COM port.
- `backup-board` captures APM board information and writes board-specific output.
- `scan-unknown` probes unknown serial boards for common protocols.
- `scan-unknown --all-bauds` checks common baud rates: 115200, 57600, 38400, and 19200.
- `scan-dfu` attempts DFU discovery through PyUSB/libusb.
- `scan-dfu --debug-backend` prints backend diagnostics before scanning.
- DFU backend failures are now handled cleanly instead of throwing raw Python tracebacks.

## APM2 validation result

Known APM2 board scan produced useful identification output:

- Port: COM14
- Board: APM
- Firmware: ArduCopter
- Version: 3.1.5
- Firmware version value: 120
- Banner included `Init ArduCopter V3.1.5`

This validates that the APM serial parser path is functional.

## Nazgul unknown STM board test case

Unknown board source: Nazgul acquisition.

Windows Device Manager showed two related USB interfaces:

- `STMmicroelectronics Virtual COM Port (COM15)` under Ports (COM & LPT)
- `Camera DFU Device` under Universal Serial Bus devices

Passive serial scan results:

- COM15 at 115200: unknown
- COM15 at 57600: unknown
- COM15 at 38400: unknown
- COM15 at 19200: unknown
- Raw bytes received: 0
- MAVLink detected: false
- MSP detected: false
- INAV detected: false
- Final status: unknown

Interpretation: Windows sees the board, and the serial interface exists, but the board does not passively emit MAVLink, MSP, or INAV data at the tested baud rates. It may require a command request, a different firmware protocol, or it may currently be in a bootloader/debug state.

## DFU scan status

The DFU side is visible to Windows as `Camera DFU Device`, but PyUSB/libusb backend initialization is not yet working on the laptop.

Observed clean tool output:

```text
usb.backend.libusb1.get_backend(...) returned: None
DFU scan unavailable: libusb backend could not be initialized.
No DFU devices found.
```

This is a successful negative test for the software path: `scan-dfu` now reports the backend problem cleanly rather than crashing with a raw traceback.

## Current limitation

The Windows USB stack can see the DFU interface, but Python cannot yet access it through PyUSB/libusb. This is likely a Windows driver/backend binding issue, not a failure of the board or the CLI command.

Future work should include either:

- resolving the Windows libusb backend path/driver binding, or
- adding a Windows-native USB discovery fallback that uses PowerShell/WMI.

## Recommended next features

### `doctor`

Add a preflight diagnostic command:

```powershell
python -m src.cli doctor
```

It should check:

- Python executable path
- Python version
- `pyserial` import
- `pymavlink` import
- `pyusb` import
- `libusb_package` import
- `libusb_package.find_library("libusb-1.0")`
- `usb.backend.libusb1.get_backend(...)`
- available serial ports from `serial.tools.list_ports`

It should print PASS/WARN/FAIL lines and never throw a raw traceback.

### `scan-usb`

Add a Windows-visible USB scan command:

```powershell
python -m src.cli scan-usb
```

On Windows, it should use PowerShell/WMI fallback, such as:

```powershell
Get-PnpDevice -PresentOnly
```

It should filter device names containing:

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

It should print a human-readable table and save a JSON report to:

```text
reports/usb/usb_devices.json
```

Recommended diagnostic chain:

```text
doctor -> scan-usb -> scan-unknown -> scan-dfu
```

## Project note

This milestone turns DroneLibreFirmwareTools into a practical board triage workflow. The tool can now distinguish between:

- a known APM/ArduCopter serial board,
- a silent unknown serial board,
- a Windows-visible DFU-capable board,
- and a host-side PyUSB/libusb backend problem.

That distinction matters. It prevents chasing firmware ghosts when the real problem is the host USB plumbing.