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

## Reference Material Archive

### ESC Fundamentals Reference

Reference video identified by Philip as worth preserving for future Drone Libre controller and flight-control work:

Title:
"How Drone ESCs Work (so I built my own...)"

Creator:
JustFPV

Topics observed:
- Brushless motor commutation
- Three-phase motor operation
- Back-EMF sensing
- Zero-crossing detection
- Sensorless ESC operation
- Custom ESC PCB design
- Motor timing concepts

Reason for retention:
Understanding ESC operation is foundational knowledge for future Drone Libre flight-controller, ESC, motor-control, and propulsion development. The discussion of back-EMF and zero-crossing detection may be especially valuable if custom control hardware is developed later.

Status:
Archived as Ratatoskr engineering reference.

## Current Concept

The LilyGo T-Display P4 physically fits well in the DJI RC-N1 phone holder area. This suggests a removable external backpack/display module can be made without cutting or permanently modifying the controller.

[Existing document continues unchanged below...]