# APM 2.8 Bench Test #002

Date: 2026-05-31

## Hardware
- APM 2.8 Flight Controller
- USB connection to laptop
- Mission Planner 1.3.83

## Connection Results
- COM Port: COM14
- Baud Rate: 115200
- Firmware Reported: ArduCopter V3.1.5
- Connected successfully
- IMU telemetry active
- Parameter list downloaded successfully

## Compass Investigation
- Bad Compass Health warning present.
- COMPASS_EXTERNAL = 0 (internal compass selected).
- Raw magnetometer values present.
- magfield approximately 4600.
- Similar behavior to APM #001.
- Compass appears detected but requires further calibration/testing.

## Outcome
PASS - Basic controller functions verified.

## Notes
- Second APM 2.8 board tested.
- Different COM port from board #001.
- Useful as Drone Libre development and bench-test controller.

## Next Steps
1. Compare with APM #001.
2. Perform compass calibration away from laptop and magnetic interference.
3. Test GPS/compass module.
4. Test RC receiver inputs.
5. Continue controller inventory.
