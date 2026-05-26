# DroneMaker Lab Documentation Index

This repository now includes a centralized documentation structure for:

- ESP32 development
- Drone systems
- Vehicle systems
- Power systems
- RF and telemetry
- Displays and UI hardware
- Composite and fabrication notes
- Datasheets and translated documentation

## Recommended Structure

```text
DOCS/
├── DATASHEETS/
│   ├── ESP32/
│   ├── Displays/
│   ├── Sensors/
│   ├── RF/
│   ├── Power/
│   ├── Motors_ESC/
│   ├── Drone_Frames/
│   └── Vehicle/
│
├── PROJECTS/
│   ├── P4/
│   ├── 5in_Test_Mule/
│   ├── Cali_Spider/
│   ├── CubeBond/
│   └── Cyberpunk_Skull/
│
├── REFERENCE/
│   ├── GitHub_Mirrors/
│   ├── Chinese_Docs_Translated/
│   ├── Pinouts/
│   ├── Wiring/
│   └── Firmware_Notes/
│
├── INVENTORY/
├── LOGS/
└── TEMPLATES/
```

## Documentation Standards

Each active project should eventually contain:

```text
README.md
STATUS.md
TODO.md
PINOUT.md
POWER.md
/project_logs/
```

## Workflow Philosophy

Reference material stays separate from active development.

- MIRRORS = untouched references
- ACTIVE PROJECTS = experimental development
- DOCS = institutional knowledge

This repository is evolving into a reusable engineering knowledge base and skunkworks archive.
