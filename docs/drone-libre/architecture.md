# Drone Libre Architecture

## Overview

Drone Libre is organized around modular layers so aircraft research, field tools, firmware procedures, and companion electronics can grow without becoming one giant ball of heroic spaghetti.

## System Layers

```text
Drone Libre
│
├── Aircraft Layer
│   ├── donor aircraft
│   ├── repairable airframes
│   ├── propulsion systems
│   ├── sensors
│   └── payload / gimbal systems
│
├── Companion Layer
│   ├── Remote ID module
│   ├── telemetry logger
│   ├── diagnostic backpack
│   └── wireless bridge / field interface
│
├── Field Tool Layer
│   ├── handheld UI
│   ├── firmware backup workflow
│   ├── serial / CAN / MAVLink diagnostics
│   ├── storage and logs
│   └── technician procedures
│
├── Ground Support Layer
│   ├── bench harnesses
│   ├── programming fixtures
│   ├── thrust stand
│   ├── RF / SDR tools
│   └── documentation workstation
│
└── Documentation Layer
    ├── teardown notes
    ├── hardware maps
    ├── firmware notes
    ├── decision records
    └── test reports
```

## Design Principles

### 1. Keep aircraft changes reversible

Prefer external companion modules, harness adapters, and test fixtures before modifying core aircraft hardware.

### 2. Separate aircraft-specific work from reusable tools

A DJI Mini teardown note should not be buried inside generic handheld firmware code. Likewise, reusable display, storage, logging, and communication modules should not depend on one airframe.

### 3. Preserve original data

Factory firmware, calibration data, photos, connector orientation, and measurements should be stored before experimentation.

### 4. Use staged validation

Bench first, restrained test second, controlled flight last. The laws of physics remain annoyingly unwilling to accept pull requests.

## Major Interfaces

| Interface | Use | Notes |
|---|---|---|
| UART | serial diagnostics, modules | common embedded interface |
| USB | firmware backup, flashing, logging | board dependent |
| CAN | avionics-adjacent diagnostics | future expansion |
| MAVLink | flight-controller communication | ArduPilot / PX4 ecosystem |
| Wi-Fi / BLE | handheld or companion link | useful for field UI |
| OpenDroneID | Remote ID work | standards-aligned path |
| SDR | RF observation and ADS-B study | receive-focused research |

## Repository Separation

- `docs/dji-research/` contains DJI-specific teardown, hardware, and firmware notes.
- `docs/drone-libre/` contains broader program architecture, mission, and roadmap.
- `firmware/` contains code intended to run on embedded targets.
- `hardware/` contains board-specific hardware notes.
- `tools/` contains scripts or procedures for backup, flashing, and diagnostics.
