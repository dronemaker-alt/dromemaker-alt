# Lessons Learned

## Purpose

Capture repeatable engineering lessons before they disappear into chat history, dead notebooks, or sleep deprivation.

---

# Embedded Systems

## Back Up Firmware First

Before experimenting with development boards:

- dump original firmware
- label backups clearly
- document flashing procedures
- document recovery procedures

Future debugging becomes dramatically easier.

---

## Separate Reusable Logic

Board-specific code should be isolated from:

- UI logic
- communications
- storage
- diagnostics
- protocol handling

This improves portability across future hardware.

---

# Fabrication

## Rapid Prototypes Beat Perfect CAD

Simple mockups:

- cardboard
- PTFE scrap
- extrusion
- perfboard

often reveal ergonomic problems faster than over-designed CAD.

---

# Workflow

## Capture First Organize Later

Fast idea capture preserves momentum.

Organization can happen later.

Lost ideas cannot.
