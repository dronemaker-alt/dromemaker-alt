# DJI Hardware Mapping

## Purpose

Map DJI Mini-class hardware into understandable subsystems so repair, diagnostics, adapter design, and future open hardware concepts can be documented cleanly.

## Subsystems

### Flight Control

- Main flight controller board
- IMU / barometer / sensor package
- Connector map
- Mounting points
- Power input and regulated rails

### Propulsion

- Motors
- ESC or power distribution board
- Motor connector or solder points
- Wire routing and strain relief

### Navigation

- GPS module
- Compass module
- Antenna layout
- Shielding and placement notes

### Communications

- Aircraft antennas
- Receiver/radio module notes
- Cable routing
- Connector type and placement

### Payload / Gimbal

- Camera module
- Gimbal controller
- Ribbon cables
- Mechanical isolation
- Calibration considerations

### Power

- Battery interface
- Battery data pins
- Main power pins
- Pack physical dimensions
- Adapter or bench-power considerations

## Mapping Tables

### Connector Inventory

| Connector | Board | Pin Count | Function | Notes |
|---|---|---:|---|---|
| TBD | TBD | TBD | TBD | TBD |

### Board Inventory

| Board / Module | Markings | Function | Status | Notes |
|---|---|---|---|---|
| TBD | TBD | TBD | TBD | TBD |

### Mechanical References

| Item | Measurement | Notes |
|---|---:|---|
| Battery bay length | TBD | TBD |
| Battery bay width | TBD | TBD |
| Battery bay height | TBD | TBD |
| FC mounting pattern | TBD | TBD |
| Top-shell clearance | TBD | TBD |

## Documentation Discipline

Use three categories for every note:

- **Observed** — directly seen, measured, photographed, or tested.
- **Inferred** — likely based on context, but not yet confirmed.
- **Speculative** — design idea or hypothesis needing proof.

That separation keeps the project from turning into internet soup with propellers.
