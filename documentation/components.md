# Components

This document lists the major hardware components used in the Wireless RC Car project and their roles in the system.

---

## 1. ESP32

**Quantity:** 1

**Role:** Main microcontroller

The ESP32 acts as the central controller of the RC car.

It receives control signals from the FlySky FS-iA6B receiver and generates PWM signals to control the BTS7960 motor drivers.

### Main functions

- Reads RC receiver signals
- Processes throttle and steering inputs
- Generates PWM signals
- Controls motor direction and speed
- Coordinates the overall control system

---

## 2. FlySky FS-iA6B Receiver

**Quantity:** 1

**Role:** Wireless RC signal receiver

The FS-iA6B receives commands from the RC transmitter and provides channel signals to the ESP32.

### Used channels

| Channel | Function |
|---|---|
| CH1 | Throttle |
| CH2 | Steering |

---

## 3. BTS7960 Motor Driver

**Quantity:** 2

**Role:** High-current DC motor driver

The BTS7960 modules provide the interface between the ESP32 and the DC motors.

The ESP32 provides low-power control signals, while the BTS7960 handles the higher current required by the motors.

### Control signals

| Driver | RPWM | LPWM |
|---|---|---|
| BTS7960 #1 | GPIO 25 | GPIO 26 |
| BTS7960 #2 | GPIO 27 | GPIO 14 |

The motor drivers are used for independent left-side and right-side motor control.

---

## 4. DC Motors

**Quantity:** As used in the vehicle

**Role:** Propulsion

The DC motors convert electrical energy from the battery into mechanical rotation to drive the wheels.

The motors are controlled through the BTS7960 motor drivers.

---

## 5. 3S LiPo Battery

**Quantity:** 1

**Role:** Main power source

The 3S LiPo battery is the primary power source for the vehicle.

### Nominal voltage

**11.1 V**

### Fully charged voltage

**12.6 V**

The battery supplies power to the motor-drive system and the voltage-regulation stage.

---

## 6. LM2596 Buck Converter

**Quantity:** 2

**Role:** DC-DC voltage regulation

The LM2596 buck converter reduces the LiPo battery voltage to a lower regulated voltage suitable for the electronics.

The project uses buck conversion to provide the low-voltage supply required by the control electronics.

### Main concept

```text
3S LiPo Battery
      |
      | 11.1V nominal
      v
LM2596 Buck Converter
      |
      | Regulated lower voltage
      v
Control Electronics

7. Capacitors
100 µF Capacitor

Quantity: 1

Used for power-supply filtering and helping reduce voltage fluctuations.

22 µF Capacitor

Quantity: 1

Used as additional supply filtering.

Capacitors were considered around the regulated electronics supply to improve power stability.

8. Motor Driver Heatsinks

Quantity: 2

Role: Thermal management

Heatsinks are attached to the BTS7960 motor-driver modules to help dissipate heat during operation.

Thermal management is important because motor drivers can dissipate significant power when driving motors under load.
9. RC Transmitter

Quantity: 1

Role: User control

The RC transmitter sends wireless commands to the FS-iA6B receiver.

The transmitter provides the operator with throttle and steering control.

10. Chassis and Wheels

Role: Mechanical structure

The chassis provides the physical structure for mounting the battery, electronics, motor drivers, motors, and other components.

The wheels transfer motor rotation into vehicle movement.


Overall Hardware System

The major components work together as follows:
RC Transmitter
       |
       | Wireless
       v
FS-iA6B Receiver
       |
       | CH1 / CH2
       v
     ESP32
       |
       | PWM
       v
BTS7960 Motor Drivers
       |
       v
    DC Motors
       |
       v
    Wheels

The power system operates separately from the control signal path:
3S LiPo Battery
       |
       +------------------> BTS7960 Motor Drivers
       |
       +------------------> LM2596 Buck Converter
                                  |
                                  v
                           Control Electronics

Key Engineering Concepts

This project provided practical exposure to:

Wireless RC communication
Microcontroller-based control
PWM motor control
DC motor driving
DC-DC buck conversion
LiPo battery power systems
Power distribution
Circuit grounding
Supply filtering
Thermal management
Hardware debugging
