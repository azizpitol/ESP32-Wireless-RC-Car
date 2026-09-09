# Hardware Pinout

## ESP32 → FS-iA6B Receiver

| Receiver | ESP32 | Function |
|---|---|---|
| CH1 | GPIO 34 | Throttle |
| CH2 | GPIO 35 | Steering |

---

## ESP32 → BTS7960 Motor Drivers

### BTS7960 #1

| BTS7960 | ESP32 | Function |
|---|---|---|
| RPWM | GPIO 25 | Motor PWM |
| LPWM | GPIO 26 | Motor PWM |

### BTS7960 #2

| BTS7960 | ESP32 | Function |
|---|---|---|
| RPWM | GPIO 27 | Motor PWM |
| LPWM | GPIO 14 | Motor PWM |

---

## Power Connections

### Main Power

The 3S LiPo battery provides the primary power for the vehicle.

```text
3S LiPo Battery
      |
      +---- BTS7960 #1
      |
      +---- BTS7960 #2
      |
      +---- LM2596 Buck Converter


Low-Voltage Electronics

The LM2596 buck converter is used to regulate the battery voltage for the low-voltage electronics.

The ESP32 should receive an appropriate regulated supply through its designated power input.

Important Notes
The ESP32 operates using 3.3V logic.
Do not apply 5V directly to ESP32 GPIO pins.
Motor power should not be routed through a breadboard.
Motor and battery wiring should be appropriately rated for the current.
The motor-driver and control-system grounds need a common reference.
Verify all connections with a multimeter before powering the system.
