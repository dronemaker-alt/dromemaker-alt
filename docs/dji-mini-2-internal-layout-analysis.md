# DJI Mini 2 Internal Layout Analysis

## Source

Screenshot from a DJI Mini 2 teardown/repair video showing the upper shell removed and the main internal board stack exposed.

> Image note: the screenshot came from the chat session and is not yet committed as a binary image asset because the current GitHub connector can create UTF-8 text files but does not upload raw image binaries. Recommended image path when manually added: `assets/photos/mini2-internal-layout-screenshot.png`.

## Visible Hardware Stack

Observed top-to-bottom layout:

1. Upper shell removed.
2. Gimbal/camera assembly forward.
3. GPS patch antenna on a small daughterboard above the flight controller.
4. Main flight controller / ESC board below GPS board.
5. Arm and motor wiring routed outward from the flight controller board to the aircraft arms.

## Identified Features

### GPS Assembly

- The white ceramic square is the GPS patch antenna.
- The GPS antenna appears to be mounted on a dedicated upper daughterboard.
- The GPS board sits directly above the flight controller instead of being fully integrated into the main board.
- This suggests the GPS assembly may be physically reusable if the main FC is replaced or studied separately.

### Flight Controller Board

- The main board sits low in the body, under the GPS board.
- Dense central IC population suggests the main processor / sensor / support logic area is on this board.
- The compact stacked layout explains why the Mini 2 has very little spare internal space.
- Board mounting points appear to be tied closely to the airframe structure, so any replacement board would need accurate mechanical registration.

### Integrated ESC / Power Stage

- Large black power packages are visible around the perimeter of the lower board.
- These are consistent with integrated ESC power-stage components / MOSFET packages.
- Motor wiring appears to terminate directly at the main board, supporting the conclusion that ESC functionality is integrated into the FC/power board rather than being separate arm-mounted ESC modules.

### Arm Wiring

- Red/white paired wiring routes along both sides of the fuselage into the arms.
- Wiring paths are very compact and appear molded into the Mini 2 internal packaging strategy.
- Any service or replacement-board design should preserve original wire routing where possible.

## Drone Libre Design Implications

### Replacement Flight Controller Strategy

This screenshot supports a one-for-one replacement-board strategy more than a total airframe redesign.

Potentially reusable original components:

- Shell and midframe
- Arms
- Motors
- Motor wiring paths
- GPS daughterboard, pending protocol identification
- Gimbal physical assembly, pending interface identification

Primary engineering target:

- Replace or emulate the main FC/ESC board while preserving the Mini 2 mechanical and wiring architecture.

### Backpack / Top-Shell Expansion

The area above and around the GPS board shows why a very small external or semi-external top-shell backpack remains plausible.

Possible uses:

- ESP32 companion module
- Remote ID node
- Diagnostic logger
- USB/service bridge
- Low-power telemetry helper

The backpack concept should avoid disturbing the GPS antenna field of view and should not place noisy RF or switching-regulator hardware directly above the GPS patch.

### Reverse-Engineering Priorities

Recommended next documentation targets:

1. High-resolution top and bottom photos of the FC board.
2. Board markings and IC identification.
3. GPS board connector pin count and trace routing.
4. Motor phase connections and resistance measurements.
5. USB connector continuity to ESD protection and processor-side traces.
6. Boot LED pattern documentation.
7. Comparison between the free Mini and crashed Mini 2 startup behavior.
8. Gimbal connector pinout and damage notes.

## Current Fault-Investigation Context

Known behavior from the current Mini investigation:

- Both Mini units power on.
- Both twitch/check the gimbal at startup.
- Both perform a sensor-check-like startup behavior.
- Green light blinking has been observed.
- Windows USB enumeration remains a key troubleshooting point.

This pattern suggests the flight controller is not fully dead. Likely investigation paths include:

- USB connector damage
- USB ESD protection failure
- Data-line trace damage
- Firmware/update interruption state
- Board-level fault preventing service-mode enumeration

## Engineering Note

The Mini 2 layout is a good example of dense commercial drone packaging. DJI used a compact board stack rather than modular hobby-style separation. For Drone Libre, the useful path is not to fight that packaging, but to document it carefully and then design around the existing mechanical envelope.

In plain terms: the airframe is good. The black box is the problem. So document the box until it stops being magic.
