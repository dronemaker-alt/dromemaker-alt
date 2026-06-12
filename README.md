# Drone Handheld Field Tool

A portable embedded field-service and diagnostics platform for drones, robotics, and avionics-adjacent systems.

This repository documents the early development of a handheld engineering tool intended to combine:

- embedded touchscreen UI
- firmware backup and recovery procedures
- field diagnostics
- modular communication interfaces
- board evaluation and supply-chain notes
- future migration paths toward more certification-friendly hardware

## Project Intent

The goal is not simply to build a gadget. The goal is to build a well-engineered, documented system that another engineer can inspect and understand.

The design philosophy is:

> A portable technician-first engineering instrument with repeatable procedures, recoverable firmware, modular software, and documented hardware decisions.

## Current Development Approach

The project uses a two-board strategy:

1. **Development platform** — larger exposed dev board for bring-up, testing, debugging, and software architecture.
2. **Handheld target platform** — compact handheld board for eventual field-form-factor deployment.

This mirrors professional embedded development, where software and architecture are often proven on expandable hardware before being migrated into a compact product form.

## Current Known Hardware

### JC-ESP32P4-M3-DEV

Observed from board/module markings:

- Primary processor: ESP32-P4
- Companion wireless MCU: ESP32-C6
- Marked memory: 32 MB PSRAM / 16 MB flash
- Interfaces visible on board: USB-C, Ethernet, microSD, expansion headers, FFC connectors

This board is treated as the initial development and experimentation platform.

### LILYGO T-Display P4 handheld board

Treated as the portable handheld target/reference platform.

Expected role:

- compact UI platform
- handheld field tool prototype
- future enclosure and battery integration target

## DJI Research & Firmware Resources

### DJI Firmware Tools

Repository:
https://github.com/o-gs/dji-firmware-tools

Purpose:

- Firmware extraction and analysis
- Update package inspection
- Bootloader and filesystem research
- DJI platform documentation and reverse-engineering reference

Why it matters:

- Assists long-term preservation of older DJI hardware
- Supports firmware recovery and diagnostics research
- Provides insight into DJI hardware architecture
- Useful reference material for future open hardware and software development efforts

## Repository Layout

```text
.
├── docs/
│   ├── board-inventory.md
│   ├── firmware-backup.md
│   ├── software-architecture.md
│   └── capstone-notes.md
├── hardware/
│   ├── jc-esp32p4-m3-dev/
│   └── lilygo-t-display-p4/
├── firmware/
│   ├── boards/
│   ├── core/
│   ├── drivers/
│   └── apps/
├── assets/
│   ├── photos/
│   ├── diagrams/
│   └── ui-mockups/
└── tools/
    ├── backup/
    └── flash/
```

## Early Engineering Priorities

1. Back up factory firmware before experimentation.
2. Identify board hardware and document all ICs, connectors, and interfaces.
3. Establish a repeatable flashing and recovery procedure.
4. Build software with a hardware abstraction layer so code can move between boards.
5. Separate board-specific code from reusable UI, diagnostics, storage, and communications modules.
6. Track design decisions so the project can support capstone, portfolio, or future product-development use.

## Long-Term Direction

Possible future system capabilities:

- UART diagnostics
- CAN bus diagnostics
- MAVLink tools
- firmware flashing and recovery
- battery and ESC service tools
- portable wiring/reference documentation
- offline field troubleshooting procedures
- modular communications interface
- secure/professional hardware migration study

## Engineering Standard

This repository should make the project look intentional.

An engineer reviewing the system should be able to answer:

- What problem does it solve?
- What hardware is being used?
- How is firmware recovered?
- What code is board-specific?
- What code is reusable?
- What risks or tradeoffs are known?
- How could this evolve into a more professional or certifiable platform?