# DJI Mini Davey Jones Teardown Plan

Davey Jones is the saltwater-recovered DJI Mini used as a forensic teardown and learning platform for Drone Libre.

## Purpose

The teardown should be treated like an aircraft incident investigation, not like casual disassembly.

Primary goals:

- Document Mini internal architecture
- Identify corrosion paths and saltwater damage
- Recover useful components if practical
- Build a repair reference for future DJI Mini work
- Support lawful repair, reuse, and education
- Create a hardware database from repeatable observations

## Teardown Rules

1. Photograph every stage before removing parts.
2. Keep screws grouped and labeled by assembly.
3. Record all board markings, cable labels, sensor markings, and connector locations.
4. Use magnification for corrosion and connector inspection.
5. Do not power unknown saltwater-exposed electronics until inspected and cleaned.
6. Separate salvageable parts from study-only parts.
7. Record anything that differs from the other Mini units.

## Initial Inspection Checklist

### Exterior

- Shell condition
- Arm hinge condition
- Motor bell condition
- Prop damage
- Battery bay corrosion
- USB port corrosion
- Vent and seam residue
- Evidence of sand, salt, or biological debris

### Motors

For each motor:

- Spin feel
- Bearing roughness
- Bell wobble
- Corrosion visible through windings
- Shaft condition
- Screw/thread condition
- Salvage decision

Motor labels:

```text
Front Left:
Front Right:
Rear Left:
Rear Right:
```

### Gimbal / Camera

- Yaw axis condition
- Roll axis condition
- Pitch axis condition
- Ribbon cable condition
- Camera lens condition
- Gimbal motor corrosion
- Mechanical travel limits
- Salvage decision

### Vision / Ultrasonic Module

- Downward optical sensors
- Ultrasonic transducers
- Connector condition
- Board markings
- Damage or corrosion

### Flight Controller / Main Board

- Board markings
- RF shielding condition
- Salt deposits under shields if visible
- Connector corrosion
- Burn marks or obvious electrical damage
- IMU/barometer area condition if visible
- Salvage decision

### ESC / Power Distribution

- Battery contacts
- Power input path
- ESC corrosion
- Motor connector/pad condition
- Current sense or power-management IC markings if visible

## Cleaning and Preservation Notes

Suggested approach:

1. Document before cleaning.
2. Remove loose debris dry first.
3. Use appropriate electronics cleaning methods only after documentation.
4. Inspect under magnification after cleaning.
5. Let parts dry thoroughly before any powered test.

Saltwater damage can look harmless while still hiding conductive residue. The goal is to learn first, resurrect second. Frankenstein can wait his turn.

## Parts Classification

Use the following status labels:

- `SALVAGE`: likely reusable after inspection/cleaning
- `TEST`: possible reuse, needs bench test
- `STUDY`: not trusted for flight, useful for reverse engineering/documentation
- `SCRAP`: mechanically/electrically destroyed
- `UNKNOWN`: needs deeper inspection

## Data to Capture Per Assembly

```text
Assembly:
Photo folder:
Board/part markings:
Connector count:
Damage observed:
Corrosion observed:
Related Mini comparison:
Status:
Next action:
```

## Expected Outcomes

By the end of teardown, the project should have:

- A complete photo sequence
- A screw and assembly map
- Board and module marking notes
- Salvage/study/scrap list
- A better understanding of DJI Mini internal architecture
- Inputs for a DJI Mini hardware database

## Related Project

This teardown supports the broader Drone Libre effort: legitimate repair, recovery, documentation, and eventual open companion/replacement systems for older drone hardware.
