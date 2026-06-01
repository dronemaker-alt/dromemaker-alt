# DroneLibre Firmware Tools Milestone

Date: 2026-05-31

## Summary

DroneLibreFirmwareTools has reached a useful diagnostic milestone. The tool can now interrogate known APM-style boards, attempt unknown serial board scans, perform multi-baud probing, detect MAVLink2 headers on modern ArduPilot-class interfaces, request MAVLink parameters from a live ArduPilot telemetry port, attempt DFU discovery, and fail cleanly when the Windows USB backend is not available.

This milestone was validated on an APM2/ArduCopter board, unknown STM-based boards from the Nazgul acquisition, and an H743-class candidate exposing ArduPilot SLCAN and ArduPilot MAVLink interfaces.

## Implemented capabilities

- `analyze-all` scans an input folder recursively and generates reports.
- `scan-apm` reads APM/ArduCopter startup banner information from a selected COM port.
- `backup-board` captures APM board information and writes board-specific output.
- `scan-unknown` probes unknown serial boards for common protocols.
- `scan-unknown --all-bauds` checks common baud rates: 115200, 57600, 38400, and 19200.
- `scan-unknown` now recognizes MAVLink v1 (`0xFE`) and MAVLink v2 (`0xFD`) packet headers.
- `scan-unknown` now sets status to `detected` when MAVLink is detected.
- `dump-params` can connect to a MAVLink serial port, receive heartbeat, request parameters, and capture real ArduPilot parameter records.
- `scan-dfu` attempts DFU discovery through PyUSB/libusb.
- `scan-dfu --debug-backend` prints backend diagnostics before scanning.
- `doctor` performs a dependency and host-system preflight check.
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

## Nazgul unknown STM board test cases

Unknown board source: Nazgul acquisition.

### Unknown STM Board #1

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

### Unknown STM Board #2

Windows identified the second unknown board as:

- `STMicroelectronics Virtual COM Port (COM16)`

Single-baud scan result:

```json
{
  "port": "COM16",
  "baud": 115200,
  "usb_device": "STMicroelectronics Virtual COM Port (COM16)",
  "scanned_at": "2026-06-01T04:11:52Z",
  "raw_bytes_hex": "",
  "bytes_count": 0,
  "mavlink_detected": false,
  "msp_detected": false,
  "inav_detected": false,
  "status": "unknown"
}
```

Multi-baud scan results:

- COM16 at 115200: unknown
- COM16 at 57600: unknown
- COM16 at 38400: unknown
- COM16 at 19200: unknown

Interpretation for both unknown STM boards: Windows sees the board and a serial interface exists, but the boards do not passively emit MAVLink, MSP, INAV, or ArduPilot banner data at the tested baud rates. They may require an active command request, a different firmware protocol, Betaflight Configurator interaction, or they may currently be in bootloader/debug states.

The recurring pattern is useful: DroneLibre correctly classifies these boards as alive at USB level but unknown at passive serial protocol level, without falsely identifying them as APM or crashing.

## H743 candidate / ArduPilot dual-interface test case

A modern H743-class candidate was connected after the APM and unknown STM tests.

The `doctor` command detected two serial ports:

```text
Serial ports (2): COM18, COM19
```

### COM18 result: ArduPilot SLCAN

DroneLibre identified the USB device as:

```text
ArduPilot SLCAN (COM18)
```

Initial scan received 42 bytes beginning with `0xFD`, but the original scanner did not recognize this as MAVLink. Codex then updated MAVLink detection to recognize MAVLink v2 packet headers.

Validated scan after the fix:

```json
{
  "port": "COM18",
  "baud": 115200,
  "usb_device": "ArduPilot SLCAN (COM18)",
  "bytes_count": 42,
  "mavlink_detected": true,
  "mavlink_header_detected": true,
  "mavlink_version": 2,
  "possible_protocol": "MAVLink2",
  "msp_detected": false,
  "inav_detected": false,
  "status": "detected"
}
```

Interpretation:

- COM18 is not silent.
- COM18 is exposed as `ArduPilot SLCAN`.
- Raw data begins with `0xFD`, consistent with MAVLink v2 packet framing.
- DroneLibre now detects MAVLink2 headers correctly.
- This appears to be a modern ArduPilot-class CAN/SLCAN-related interface rather than an old APM-style ASCII startup banner.

### COM19 result: ArduPilot MAVLink and parameter backup

DroneLibre identified COM19 as:

```text
ArduPilot MAVLink (COM19)
```

After Mission Planner was closed and the port was released, `scan-unknown` detected MAVLink2 on COM19:

```json
{
  "port": "COM19",
  "baud": 115200,
  "usb_device": "ArduPilot MAVLink (COM19)",
  "bytes_count": 42,
  "mavlink_detected": true,
  "mavlink_header_detected": true,
  "mavlink_version": 2,
  "possible_protocol": "MAVLink2",
  "msp_detected": false,
  "inav_detected": false,
  "status": "detected"
}
```

`dump-params` was then updated from text-line parsing to true MAVLink parameter capture using pymavlink. The Windows COM-port handling issue was fixed by opening plain COM ports as serial connection strings instead of treating them as UDP endpoints. A PARAM_VALUE parsing issue was also fixed by handling `param_id` as either bytes or string.

Validated `dump-params` result on COM19:

```text
Port: COM19
Baud: 115200
Using MAVLink connection: COM19
MAVLink heartbeat: received
Parameters found: 1301
Status: detected
Error: null
```

The captured parameter dump includes real ArduPilot records such as:

- `SERVO2_FUNCTION = 34.0`
- `SERVO3_FUNCTION = 35.0`
- `SERVO4_FUNCTION = 36.0`
- `SERVO8_FUNCTION = 31.0`
- `SERVO_RATE = 50.0`
- `RC1_MIN = 1100.0`
- `RC1_TRIM = 1500.0`
- `RC1_MAX = 1900.0`

Board summary extracted from the parameter set:

```json
{
  "SYSID_THISMAV": "1.0",
  "SYSID_MYGCS": "255.0",
  "FRAME_TYPE": "1.0",
  "FRAME_CLASS": "6.0",
  "INS_ENABLE_MASK": "127.0",
  "CAN_P1_DRIVER": "0.0",
  "CAN_D1_PROTOCOL": "1.0",
  "CAN_D1_PROTOCOL2": "0.0",
  "CAN_SLCAN_CPORT": "0.0",
  "CAN_SLCAN_SERNUM": "-1.0",
  "CAN_SLCAN_TIMOUT": "0.0",
  "CAN_SLCAN_SDELAY": "1.0",
  "CAN_LOGLEVEL": "0.0"
}
```

Interpretation:

- COM19 is the primary MAVLink telemetry/parameter interface.
- COM19 can receive heartbeat and return a full parameter list.
- The H743-class candidate has 1301 parameters.
- DroneLibre can now back up a modern ArduPilot-class board, not merely identify it.
- COM18 appears to be the related SLCAN/CAN interface.

This is the first confirmed modern-board parameter backup milestone for DroneLibreFirmwareTools.

## Doctor validation result

The `doctor` command was implemented and validated after fixing a false `pyserial` failure. The package name is `pyserial`, but the correct Python import is `serial`.

Validated result:

```text
pyserial: PASS (version=3.5)
pymavlink: PASS (version=2.4.49)
pyusb: PASS (version=1.3.1)
libusb-package: PASS (version=1.0.26.1)
libusb backend: WARN - libusb backend returned None
Serial ports (2): COM18, COM19
```

Interpretation: the Python environment, serial stack, MAVLink dependency, PyUSB package, and libusb-package dependency are installed and visible to Python. The remaining issue is specifically the host-side libusb backend initialization path on Windows.

The `doctor` command is now useful as the first preflight check before board interrogation.

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

## Recommended next feature: Mission Planner-compatible parameter export

Add parameter export formats for modern ArduPilot board backups:

```text
reports/params/COM19_params.json
reports/params/COM19_params.csv
reports/params/COM19_params.param
```

The `.param` output should be Mission Planner-compatible so DroneLibre can restore or compare board configuration files.

Recommended diagnostic chain:

```text
doctor -> scan-usb -> scan-unknown -> dump-params -> scan-dfu
```

## Recommended next feature: `scan-usb`

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
- ArduPilot
- SLCAN

It should print a human-readable table and save a JSON report to:

```text
reports/usb/usb_devices.json
```

## Project note

This milestone turns DroneLibreFirmwareTools into a practical board triage workflow. The tool can now distinguish between:

- a known APM/ArduCopter serial board,
- silent unknown STM serial boards,
- a Windows-visible DFU-capable board,
- a modern MAVLink2 / ArduPilot SLCAN interface,
- a modern ArduPilot MAVLink telemetry interface,
- a live MAVLink heartbeat,
- a full ArduPilot parameter backup,
- and a host-side PyUSB/libusb backend problem.

That distinction matters. It prevents chasing firmware ghosts when the real problem is the host USB plumbing, prevents modern MAVLink2 traffic from being mistaken for meaningless binary noise, and turns DroneLibre into a practical backup and triage tool for modern ArduPilot-class hardware.
