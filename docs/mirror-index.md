# Mirror Index

This index tracks external repositories, documentation sources, and references that should be preserved for project continuity.

## Status Labels

- `TO FIND`: source mentioned but repository not yet located
- `TO MIRROR`: source located, not yet cloned or archived
- `MIRRORED`: local copy exists
- `DOCUMENTED`: mirror has notes explaining why it matters
- `TESTED`: build, install, or procedure has been tried
- `STALE`: source may be outdated
- `REPLACED`: better reference found

## Mirror Entries

### AERIS-10 / Open Source PLFM Radar

Status: `TO FIND`

Source:
- Hackaday project: Open Source PLFM Radar, up to 20 km range

Related project:
- Ground station
- Drone detection / situational awareness
- SDR and radar research

Why saved:
- Potentially useful reference for open radar concepts and long-range field sensing

Next action:
- Locate GitHub repository
- Capture cost estimate and hardware list
- Record build dependencies

---

### DJI Firmware Tools

Status: `TO MIRROR`

Source:
- https://github.com/o-gs/dji-firmware-tools

Related project:
- Drone Libre
- DJI repair and firmware research

Why saved:
- Public reference for DJI firmware extraction and analysis
- Useful for preservation and repair research

Boundary:
- Use for lawful repair, documentation, and education only

Next action:
- Clone locally
- Check license
- Record supported DJI platforms

---

### ESP32 Low-Cost Drone / Companion References

Status: `TO MIRROR`

Source:
- Digi-Key Maker ESP32 drone article and any associated code references

Related project:
- ESP32 Drone Companion
- Low-cost drone experimentation
- Handheld field tool

Why saved:
- Useful for understanding simple ESP32-controlled drone architecture and companion-system possibilities

Next action:
- Locate source code repository if available
- Separate tutorial-only content from reusable code

---

### Hexapod / Walking Drone Reference

Status: `TO FIND`

Source:
- Instagram/GitHub hexapod build reference discussed previously

Related project:
- Cali-Spider
- Transformable walking drone
- Robotics platform research

Why saved:
- Potential mechanical and software reference for walking robotics and drone hybrid concepts

Next action:
- Locate GitHub repository
- Mirror frame/STL files and gait/controller code if license allows

---

### Ground Station / ADS-B / SDR Tools

Status: `TO FIND`

Source:
- Various SDR, ADS-B, MAVLink, and ground-station references

Related project:
- Portable ground station
- AERIS-10 integration study
- Multi-antenna SDR experiments

Why saved:
- Supports field situational awareness and drone operations support

Next action:
- Identify current preferred repositories
- Document hardware compatibility

## Mirror Documentation Template

For every mirrored source, create a note using this structure:

```text
Name:
Source URL:
Date captured:
License:
Related project:
Why this matters:
Hardware required:
Software required:
Build status:
Test status:
Risks / limitations:
Next action:
```

## Storage Rule

Do not blindly dump large external projects into this repository unless they are small, license-compatible, and directly useful.

Preferred methods:

1. Clone locally into a `mirrors/` folder outside this repo.
2. Add the source and notes here.
3. Use submodules only when it makes long-term sense.
4. Keep screenshots, PDFs, and notes organized by project.
