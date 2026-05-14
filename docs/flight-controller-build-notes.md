# Flight Controller Build Notes

## Purpose

Working notes for custom flight-controller assembly, bring-up, and subsystem planning.

This document is derived from the active ChatGPT project thread and is intended to evolve into structured hardware documentation.

---

# Current Hardware Direction

## MCU Practice Assembly

Current plan:

- Assemble 1 practice board before building the first 5-board batch.
- Use hot-air / reflow heat gun workflow.
- Validate solder quality under magnification.
- Confirm rail integrity before powering sensitive ICs.

## Main MCUs Mentioned

### GD32F405

Used as the primary flight-controller MCU candidate.

Bring-up focus:

- identify pin 1 orientation
- verify boot pins
- verify SWD access
- validate crystal oscillator operation
- validate USB connectivity

### NXP K66 (MK66FN2M0VMD18)

Inventory includes multiple K66 MCUs including an engineering sample.

Potential uses:

- advanced controller experiments
- high-speed peripheral testing
- alternate flight-controller architecture
- diagnostics subsystem

---

# Power-System Planning

## Initial Requirements

The power subsystem should support:

- USB powered bring-up
- bench supply testing
- future battery integration
- clean 3.3V rail for MCU and sensors
- isolated/noise-managed rails for RF and displays if needed

## Known Questions

- USB-C migration strategy
- ESD protection selection
- regulator thermal performance
- reverse polarity protection
- current sensing approach
- boot current measurements

---

# USB-C Migration Notes

The project thread discussed replacing micro-USB with USB-C.

Key considerations:

- CC resistors required for proper device negotiation
- preserve USB data pair routing integrity
- add ESD protection near connector
- mechanically reinforce connector pads
- maintain SWD/debug access independent of USB

---

# Displays and UI Work

Known display inventory and concepts:

- 0.96 inch OLED modules
- 2.5 inch TFT/OLED displays
- LilyGo P4 handheld platform

Current direction:

- handheld diagnostics interface
- modular UI architecture
- field-programmer concepts
- portable avionics/drone diagnostics

---

# Mechanical Concepts

Discussed mechanical ideas include:

- PTFE plate mockups
- handheld enclosure shaping
- compact button placement
- metal standoffs
- wearable/light-mounted field configurations

---

# Recommended Immediate Tasks

1. Photograph blank PCB front/back.
2. Mark all rail sections and regulators.
3. Create MCU pin-1 orientation reference images.
4. Identify required passives for first power-up.
5. Build a minimal SWD/debug harness.
6. Document first successful USB enumeration.
7. Create recovery procedure before firmware experimentation.
