# Cable and Pinout Reference

## Purpose

Centralized location for:

- adapter pinouts
- UART references
- CAN wiring
- USB adapters
- debug headers
- field-service cable notes

---

# UART Reference

## Typical UART

```text
TX -> RX
RX -> TX
GND -> GND
```

Always verify logic voltage compatibility.

---

# ESP32 Notes

Document:

- flashing pin requirements
- serial console pins
- recovery procedures
- USB bridge details

---

# Flight Controller References

Track:

- telemetry ports
- GPS ports
- receiver connections
- ESC signal mapping
- CAN interfaces

---

# Adapter Strategy

Goal:

Build reusable labeled adapters instead of improvised cable chaos.

The future goal is a portable field kit where adapters are:

- documented
- repeatable
- labeled
- recoverable
