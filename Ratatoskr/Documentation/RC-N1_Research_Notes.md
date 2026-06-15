# Ratatoskr - DJI RC-N1 Research Notes

## Overview

**Ratatoskr** is the DroneMaker / Drone Libre controller-companion project.

The name comes from the Norse squirrel that carries messages along Yggdrasil. That makes it a good fit for a system intended to pass messages between pilot, controller, aircraft, telemetry systems, and mission software.

Initial focus:

- DJI RC-N1 controller, model RC231
- LilyGo T-Display P4 as a removable avionics/MFD-style display
- USB-HID and simulator interface research
- Non-destructive controller augmentation
- Future telemetry and protocol translation

## Current Concept

The LilyGo T-Display P4 physically fits well in the DJI RC-N1 phone holder area. This suggests a removable external backpack/display module can be made without cutting or permanently modifying the controller.

The first mount concept is a **corner-capture cradle**:

- Captures the P4 housing at the four corners
- Leaves side buttons unobstructed
- Leaves USB, Ethernet, antenna ports, and SD card accessible
- Uses the RC-N1 phone holder as the support structure
- Allows quick removal for bench use or firmware work
- Avoids applying pressure to the P4 side controls

## Controller Architecture Observations

Based on teardown screenshots and community repair documentation, the DJI RC-N1 appears to use a modular internal layout:

- Main processor / RF board
- Separate USB-C daughterboard
- Separate left stick module
- Separate right stick module
- Separate gimbal/zoom wheel board
- Separate camera button board
- Dual internal battery packs
- Fold-out phone holder assembly

This modular construction is useful for research because it creates clear interface points.

## Known Community References

### Original Project

`Matsemann/mDjiController`

Purpose:

- DJI controller interface research
- USB controller support
- Simulator-related work

### Primary Fork / Research Reference

`IvanYaky/DJI_RC-N1_SIMULATOR_FLY_DCL`

Observed from GitHub screenshot:

- Forked from `Matsemann/mDjiController`
- 132 stars
- 33 forks
- Purpose: use DJI RC-N1 remote controller from Mavic 3 in DCL - The Game or other flight simulator software

This appears to be the best known public research fork for RC-N1 simulator use.

### Secondary Fork

`Miniontoby/DJI_RC-N1_SIMULATOR_FLY_DCL`

Observed from GitHub screenshot:

- Forked from `IvanYaky/DJI_RC-N1_SIMULATOR_FLY_DCL`
- 3 stars
- 1 fork

This is a downstream fork and should be treated as reference material unless it contains useful changes.

## Repository Lineage

```text
Matsemann/mDjiController
        ↓
IvanYaky/DJI_RC-N1_SIMULATOR_FLY_DCL
        ↓
Miniontoby/DJI_RC-N1_SIMULATOR_FLY_DCL
```

## Known Pinout Information

Community documentation indicates the RC-N1 gimbal dial and sticks expose simple 3.3V analog-style signals.

### Gimbal Dial

Pin order, top-to-bottom at main board connector:

1. GND
2. 3.3V
3. Axis

### Left Stick

Pin order, top-to-bottom at main board connector:

1. GND
2. 3.3V
3. X Axis
4. Y Axis
5. Button

### Right Stick

Pin order, top-to-bottom at main board connector:

1. Button
2. X Axis
3. Y Axis
4. 3.3V
5. GND

## Initial Technical Assessment

The stick and dial interfaces appear to be conventional low-voltage analog signal sources rather than encrypted smart modules.

This suggests several development paths:

### Passive Monitor Mode

Ratatoskr observes stick and dial signals without altering the RC-N1.

Possible functions:

- Pilot input display
- Stick calibration visualization
- Flight training analysis
- Control logging
- Input replay research

### USB Observer Mode

Ratatoskr listens to the RC-N1 through USB instead of tapping internal wiring.

Possible functions:

- USB HID decoding
- Simulator input mapping
- Stick and button monitoring
- Translation to other control protocols

This is the preferred first research path because it avoids modifying the DJI controller.

### Future Injection / Translation Mode

Later research may explore generating or translating control signals, but this should wait until passive observation is understood.

Potential targets:

- ELRS
- CRSF
- SBUS
- MAVLink RC override
- Drone Libre control layers

## Development Strategy

### Phase 1 - Document and Observe

- Collect teardown references
- Document pinouts
- Identify USB VID/PID behavior
- Test RC-N1 enumeration on PC/Linux/P4/Pi
- Review simulator projects
- Avoid destructive modification

### Phase 2 - External P4 Backpack

- Build corner-capture P4 mount
- Keep controller stock
- Run Ratatoskr software on P4
- Display controller, mission, and telemetry status
- Begin USB-HID experiments

### Phase 3 - Protocol Bridge

- Convert controller inputs into open control paths
- Explore ELRS/MAVLink integration
- Add Drone Libre aircraft profiles
- Add logging and checklist functions

### Phase 4 - Intelligence Layer

- Integrate future Huginn/Muninn software roles
- Huginn: analysis, flight assistance, advisory logic
- Muninn: memory, logs, replay, mission archive

## Relationship to Drone Libre Architecture

Ratatoskr is a ground/control-side support system in the Drone Libre ecosystem.

Related names and roles:

- **Drone Libre** - overall open drone ecosystem
- **Gungnir** - VTOL reconnaissance aircraft, formerly P1 clone concept
- **Ratatoskr** - controller companion, telemetry bridge, protocol translator
- **Huginn** - future AI analysis/advisory module
- **Muninn** - future logging/memory/mission recorder module
- **Jotun** - medium utility multirotor class
- **Sleipnir** - heavy-lift platform
- **Garm** - FPV/interceptor class
- **Disir** - micro scout/helper class

## Open Questions

- Does the RC-N1 enumerate as standard HID, vendor-specific USB, serial, or mixed device?
- Can the LilyGo P4 act as USB host for the RC-N1?
- Can a Pi Zero 2W serve as the first Ratatoskr USB analysis host?
- What data format is used by the simulator projects?
- Can the existing USB-C phone interface be reused for P4/Pi communication?
- Can telemetry be displayed without interfering with DJI Fly operation?
- What is the cleanest non-destructive mechanical mount for the P4?

## Notes

The current best engineering path is to observe first and modify later.

Initial Ratatoskr development should prioritize USB-based investigation before internal signal tapping. The RC-N1 already has a working USB path used by phones and simulators, so the first objective is to exploit documented behavior before opening the controller.

In short: let the squirrel listen before it starts chewing on wires.
