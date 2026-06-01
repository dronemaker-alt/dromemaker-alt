# DroneLibre Milestone 001 – Live APM Discovery

Date: 2026-05-31

## Objective

Validate DroneLibre against real flight-controller hardware instead of only analyzing firmware files.

## Hardware Tested

### APM #001
- Platform: APM 2.8
- Interface: USB serial
- Result: PASS

### APM #002
- Platform: APM 2.8
- Interface: USB serial
- Result: PASS

## Mission Planner Baseline

Mission Planner was used as the known-good reference tool.

Observed results:
- Mission Planner 1.3.83 launched successfully after reinstall/path cleanup.
- APM boards connected successfully.
- IMU telemetry displayed.
- Artificial horizon responded to board motion.
- Parameter tree loaded.
- Compass health warning appeared on both boards.
- No GPS was connected during bench testing.

Known observed board data:
- COM13: APM #001
- COM14: APM #002
- Baud rate: 115200
- Firmware reported: ArduCopter V3.1.5
- FW Ver: 120

## DroneLibre Work Completed

DroneLibreFirmwareTools was expanded from a firmware-file analysis framework into a live hardware interrogation tool.

### Existing capability verified
- `analyze-all` command runs successfully.
- Input scanning works.
- Report generation works.
- Empty input folder correctly produces zero analyzed firmware files.
- Reports are written to `reports/`.

Generated report artifacts included:
- `analysis_report`
- `dronemaker.json`
- `firmware.db`
- `index.html`
- `index.md`
- `inventory.csv`
- `inventory.json`
- `parser_inventory.json`
- `README.md`

### New capability added

#### `scan-apm`

Function:
- Accepts a COM port argument.
- Opens the serial port at 115200 baud.
- Reads APM/ArduPilot startup banner output.
- Detects APM-class board behavior.
- Extracts ArduPilot firmware family.
- Extracts firmware version.
- Extracts firmware build version.

Validated output included:

```json
{
  "port": "COM14",
  "board": "APM",
  "firmware": "ArduCopter",
  "version": "3.1.5",
  "fw_ver": "120"
}
```

Detected startup banner included:

```text
Init ArduCopter V3.1.5
Free RAM: 1618
FW Ver: 120
COMPASS INIT ERROR
GROUND START
```

#### `backup-board`

Framework added for board backup operations.

Current behavior:
- Connects to the board.
- Captures board metadata.
- Captures startup banner text.
- Creates backup/report output.

Current limitation:
- MAVLink parameter backup is not yet complete.
- `pymavlink` dependency was installed successfully, but serial connection handling still needs refinement for Windows COM ports.

Observed runtime issue during MAVLink parameter work:

```text
ValueError: UDP ports must be specified as host:port
```

Likely cause:
- `pymavlink` connection string is being interpreted as UDP instead of Windows serial.
- Next fix should ensure `COM14` is opened as a serial device at 115200 baud.

## Validation Results

Both APM 2.8 boards successfully identified by DroneLibre.

| Test ID | Board | Port | Firmware | Version | FW Ver | Result |
|---|---|---:|---|---|---:|---|
| 001 | APM 2.8 | COM13 | ArduCopter | 3.1.5 | 120 | PASS |
| 002 | APM 2.8 | COM14 | ArduCopter | 3.1.5 | 120 | PASS |

## Significance

This milestone marks DroneLibre's first successful live flight-controller interrogation.

DroneLibre is no longer only a firmware-file scanner. It can now connect to real drone flight-controller hardware, read serial output, identify firmware, and produce useful board metadata.

This creates the foundation for future DroneLibre bench workflows:

1. Scan board.
2. Identify firmware.
3. Capture board metadata.
4. Dump parameters.
5. Compare boards.
6. Restore or clone board configuration.
7. Build repeatable rescue logs for unknown drone hardware.

## Next Work Items

Priority next steps:

1. Fix `backup-board` MAVLink serial connection on Windows COM ports.
2. Complete MAVLink parameter download.
3. Save parameters as JSON, CSV, and `.param` formats.
4. Add `scan-all` to enumerate COM ports automatically.
5. Add `dump-params` for explicit parameter backup.
6. Add `compare-board` for comparing two board backups.
7. Add `restore-board` / `clone-board` later, after backup is reliable.
8. Expand support beyond APM to Pixhawk, H743, INAV, Betaflight, and DJI discovery modes.

## Status

Operational prototype.

DroneLibre can successfully identify live APM 2.8 hardware running ArduCopter 3.1.5.
