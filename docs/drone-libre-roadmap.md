# Drone Libre Roadmap

Drone Libre is the working name for the effort to repair, document, reuse, and eventually augment older drone hardware without depending entirely on closed vendor ecosystems.

## Mission

Build a lawful, repair-focused, technician-first drone reuse and documentation project.

The project is about:

- recovering damaged drones
- documenting internal hardware
- preserving useful knowledge
- creating companion electronics
- building repair procedures
- exploring open interfaces
- reducing e-waste
- supporting responsible FAA-compliant drone use

It is not about stealing drones, bypassing ownership, or defeating legitimate safety systems.

## Current Focus Areas

### 1. DJI Mini Repair and Documentation

Known units:

- Gift DJI Mini: powers up, gimbal moves, amber blink; later found with two rear motor issues
- Purchased Mini 2: arrived with battery and controller; gimbal yaw fracture; button jam freed; gimbal calibration succeeded; likely CFIT event
- Davey Jones Mini: ocean/saltwater recovery; teardown and study platform

Current goals:

- Build a Mini / Mini 2 teardown database
- Compare damage patterns across multiple units
- Record gimbal, motor, sensor, and board differences
- Identify what parts are reusable
- Develop repeatable repair inspection procedures

### 2. Drone Companion System

The companion system is intended to add external capability without immediately replacing a flight controller.

Candidate functions:

- remote ID experiments
- telemetry display
- battery and sensor monitoring
- external GPS monitoring
- companion UI
- drone-to-drone coordination experiments
- gesture control research
- secure optical or laser communication experiments
- service/diagnostic interface

Preferred approach:

- Use non-invasive external interfaces first
- Use UART, I2C, USB, or monitored power/sensor lines where accessible
- Avoid modifying flight-critical systems until architecture is understood
- Keep companion software separate from flight controller replacement work

### 3. Controller Reuse / RM-01 Concept

Idea:

Reuse a desirable DJI-style controller form factor by replacing or bypassing internal electronics and adding a modular bay for add-ons.

Reasons:

- Comfortable industrial design
- Existing sticks, switches, enclosure, and ergonomics
- Good candidate shell for a custom open controller
- Multiple donor units available for experimentation

Possible add-ons:

- ELRS module
- ESP32/P4 control board
- display module
- battery system
- removable RF bay
- USB service port
- telemetry receiver

### 4. Open Flight Controller / Replacement Path

Long-term idea:

Study whether older drone hardware can eventually be given domestic/open replacement electronics.

Available related inventory:

- APM 2.5 / 2.6 controllers
- NAZA v2
- H743 flight controller
- ESP32 family boards
- Raspberry Pi Zero 2W / Pi 4
- NXP K66 chips
- blank flight-controller PCBs

Guiding principle:

Start with companion systems and bench testing before attempting one-for-one flight controller replacement.

### 5. Ground Station and Situational Awareness

Potential ground-station functions:

- MAVLink monitoring
- ADS-B SDR monitoring
- multi-antenna SDR experiments
- radar reference research
- telemetry display
- drone maintenance logs
- field checklist display

Related references:

- AERIS-10 / PLFM radar research
- SDR / ADS-B projects
- 7-inch HDMI display ground station
- joystick/controller interfaces

## Project Phases

### Phase 0: Preservation and Organization

- Mirror critical repositories
- Save documentation and repair references
- Capture current GitHub traffic baseline
- Create local backups
- Create repo documentation spine

### Phase 1: Repair Knowledge Base

- Tear down Davey Jones
- Photograph and document Mini internals
- Compare donor units
- Create salvage/study/scrap classifications
- Record gimbal and motor repair notes

### Phase 2: Companion Electronics

- Build ESP32 / LilyGo / P4 companion prototypes
- Start with display, logging, and sensor monitoring
- Avoid flight-critical modification early
- Build field-tool UI screens

### Phase 3: Controller and Ground Station

- Evaluate RM-01/controller shell reuse
- Design modular controller bay
- Integrate telemetry and service functions
- Prototype portable ground station layout

### Phase 4: Open Replacement Research

- Study flight controller interfaces
- Bench-test candidate FCs
- Map connector pinouts where lawful and safe
- Compare open stack requirements with DJI hardware constraints

### Phase 5: Public Engineering Reference

- Publish repair-oriented documentation
- Add clear legal/ethical boundaries
- Make the project useful to responsible hobbyists, repairers, and educators
- Keep the tone professional enough for portfolio, capstone, or consultation use

## Near-Term Win Condition

A successful near-term result is not a flying Frankenstein drone.

A successful near-term result is:

- documented mirrors
- organized project notes
- Davey Jones teardown completed
- Mini hardware database started
- companion-system direction written down
- repair procedures becoming repeatable

Flying comes later. Documentation first, because future-you is a brilliant guy but also a known tool scatter hazard.
