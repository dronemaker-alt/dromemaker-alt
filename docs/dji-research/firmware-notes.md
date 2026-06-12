# DJI Firmware Notes

## Purpose

Collect notes related to DJI firmware packages, update behavior, recovery procedures, and public research resources.

## Key External Reference

- dji-firmware-tools: https://github.com/o-gs/dji-firmware-tools

This repository is treated as a public research reference for understanding DJI firmware package handling, extraction, and analysis workflows.

## Research Areas

- Firmware package structure
- Update file naming and version tracking
- Recovery workflows for older DJI aircraft
- Bootloader and filesystem references
- Firmware backup strategy before experimentation
- Separation of aircraft firmware, controller firmware, gimbal firmware, and battery firmware notes

## Local Documentation Rules

- Record exact aircraft model and firmware version when known.
- Preserve original filenames and checksums when possible.
- Do not overwrite original backup files.
- Keep experimental notes separate from confirmed recovery procedures.
- Document the tool version or commit used for any analysis.

## Open Questions

- [ ] Which firmware package families apply to Mini / Mini SE / Mini 2 hardware?
- [ ] What can be safely backed up from a donor aircraft before repair?
- [ ] Which modules have independent firmware or calibration data?
- [ ] What recovery methods exist for crashed or partially functional aircraft?
- [ ] What data must be preserved before replacing or adapting hardware?

## Safety of Documentation

This file is for preservation, diagnostics, and engineering study. The repository should document lawful repair and research practices, not operational bypass procedures.
