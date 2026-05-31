# APM 2.8 Bench Test

Date: 2026-05-31

## Hardware
- APM 2.8 Flight Controller
- USB connection to laptop
- Mission Planner 1.3.83

## Connection Results
- COM Port: COM13
- Baud Rate: 115200
- Firmware Reported: ArduCopter V3.1.5
- IMU data received successfully
- Artificial horizon active
- Full parameter tree downloaded successfully

## Notes
- Initial Mission Planner startup appeared frozen.
- Hidden popup windows were blocking progress.
- Mission Planner eventually completed initialization.
- Compass warning observed during bench testing.
- No GPS connected during test.

## Outcome
PASS

Mission Planner communication with APM 2.8 verified. Board responsive and parameters accessible.

## Next Steps
1. Save parameter backup.
2. Identify attached sensors and GPS hardware.
3. Test RC receiver input.
4. Verify compass operation.
5. Evaluate firmware version and upgrade options.

Project: Drone Libre Toolchain Validation
