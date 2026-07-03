# GitHub Maintenance and Mirror Plan

This document captures the current maintenance plan for organizing drone, robotics, radar, and field-tool research.

## Purpose

The goal is to preserve useful open-source references before links disappear, organize research into durable project folders, and make the repository easier to use as a working engineering log.

This is not just link hoarding. The intent is to keep a traceable record of why each source matters, what hardware or software it relates to, and what experiment it supports.

## Priority Mirrors

### 1. AERIS-10 / PLFM Radar Research

Source reference:
- Hackaday project: Open Source PLFM Radar, up to 20 km range

Why it matters:
- Candidate reference for a future ground-station radar experiment
- Relevant to drone detection, tracking, and local situational awareness
- Useful background for RF, SDR, signal processing, and field-deployable sensing

Planned action:
- Locate the associated GitHub repository
- Mirror it locally
- Record dependencies, build instructions, RF hardware requirements, and estimated cost
- Add notes on possible integration with a ground station

### 2. ESP32 Drone Companion Stack

Why it matters:
- Supports the low-cost drone companion concept
- Useful for telemetry, remote ID experiments, sensor fusion, UI, and drone-adjacent service tools
- Can bridge hobby drone work and avionics-style field diagnostics

Planned action:
- Save relevant tutorials, repositories, and code references
- Separate flight-critical ideas from companion-only ideas
- Track what can be done through external interfaces versus modifying an OEM flight controller

### 3. DJI Research and Repair References

Why it matters:
- Supports Drone Libre repair, recovery, and reuse work
- Helps document older DJI hardware in a way that is useful for legitimate repair and education
- Preserves knowledge for Mini, Mini 2, Mavic Air, controllers, gimbals, sensors, and firmware tooling

Planned action:
- Mirror public repair notes, teardown references, and firmware-analysis tools where licenses allow
- Keep notes focused on repair, diagnostics, preservation, and lawful reuse
- Avoid turning the repository into a bypass or theft-enablement playbook

### 4. Hexapod / Walking Drone / Cali-Spider References

Why it matters:
- Supports the walking drone and two-foot hexapod ideas
- Useful mechanical and software reference for a future voice/AI-enabled robotics platform
- Candidate inspiration for a whoop-deploying spider platform

Planned action:
- Locate and mirror GitHub files from the referenced Instagram/GitHub build
- Record servo layout, gait approach, frame files, controller requirements, and power budget

### 5. Ground Station / ADS-B / SDR Tools

Why it matters:
- Supports a portable drone ground station
- Connects to radar, ADS-B monitoring, local airspace awareness, and multi-antenna SDR experiments

Planned action:
- Mirror useful SDR, ADS-B, MAVLink, and ground-station UI references
- Track hardware requirements against existing inventory

## Repository Organization Target

Suggested top-level documentation structure:

```text
docs/
  github-maintenance-plan.md
  mirror-index.md
  dji-mini-davey-jones-teardown.md
  drone-libre-roadmap.md
  hardware-inventory.md
  research-notes.md
```

Suggested external/local mirror folders:

```text
mirrors/
  aeris-10-radar/
  esp32-drone-companion/
  dji-repair-and-firmware/
  hexapod-walking-drone/
  ground-station-sdr/
```

Large mirrored repositories should usually stay as separate clones or submodules rather than being dumped blindly into this repository.

## Maintenance Day Checklist

1. Check GitHub traffic before updates and save screenshots.
2. Pull or clone all existing local project repos.
3. Confirm which repos are public, private, archived, or stale.
4. Mirror high-risk references first.
5. Add a short `WHY_THIS_MATTERS.md` note to every mirror folder.
6. Update this repository with current project status.
7. Back up local clones to external storage.
8. Record what still needs deeper research.

## Baseline Traffic Note

As of the last connector check, this repository was public, on branch `main`, not archived, and accessible with admin-level permissions. GitHub traffic stats must still be checked manually from:

`Repository -> Insights -> Traffic`

GitHub normally shows the last 14 days of views, unique visitors, clones, unique cloners, referring sites, and popular content.

## Working Rule

A mirror is not complete until it has:

- source URL
- license note if visible
- date captured
- reason for saving
- related project
- build/run status if tested
- hardware requirements
- next action
