# ESP32-Wireless-RC-Car
Wireless joystick-controlled RC vehicle using ESP32, FlySky receiver, BTS7960 motor drivers and PWM-based motor control.
# Wireless Dual-Motor RC Car Using ESP32

A self-initiated hardware project developed to explore embedded systems, wireless RC control, PWM-based motor control, power electronics, and practical circuit debugging.

---

## 📌 Project Overview

This project is a wireless RC car controlled using an ESP32 and a FlySky FS-iA6B receiver.

The RC transmitter sends control commands wirelessly to the FS-iA6B receiver. The receiver passes the control signals to the ESP32, which processes the inputs and generates PWM signals for two BTS7960 high-current motor drivers.

The BTS7960 drivers control the DC motors, while a 3S LiPo battery provides the main power source. LM2596 buck converters are used to regulate the battery voltage for the low-voltage electronics.

The project was developed independently to gain practical experience with embedded hardware, motor control, power distribution, voltage regulation, and hardware troubleshooting.

---

## 🎯 Objectives

- Build a functional wireless RC vehicle from individual electronic components
- Learn how to interface an RC receiver with a microcontroller
- Implement PWM-based DC motor control
- Interface high-current motor drivers with an ESP32
- Understand DC-DC voltage regulation using buck converters
- Work with LiPo battery power systems
- Develop practical circuit debugging and troubleshooting skills
- Understand power distribution, grounding, and thermal considerations

---

## ⚙️ Features

- Wireless RC control
- ESP32-based control system
- FlySky FS-iA6B receiver interface
- Dual DC motor control
- PWM-based motor speed control
- BTS7960 high-current motor drivers
- 3S LiPo battery power system
- LM2596 buck-converter-based voltage regulation
- Independent control of left and right motors
- Practical hardware debugging and testing

---

## 🔌 System Architecture

```text
                    RC TRANSMITTER
                          |
                    Wireless Signal
                          |
                          v
                   FS-iA6B RECEIVER
                          |
                    CH1 / CH2 Signals
                          |
                          v
                       ESP32
                          |
                 PWM Motor Control
                    /           \
                   /             \
                  v               v
          BTS7960 Driver 1   BTS7960 Driver 2
                  |               |
                  v               v
               Motor 1          Motor 2
````

---

## 🔋 Power Architecture

The vehicle is powered by a 3S LiPo battery.

```text
                    3S LiPo Battery
                    11.1V nominal
                    12.6V fully charged
                           |
          +----------------+----------------+
          |                |                |
          v                v                v
    BTS7960 #1       BTS7960 #2        LM2596 Buck
          |                |                |
          v                v                v
       Motor 1          Motor 2          Regulated
                                            Supply
                                             |
                                    +--------+--------+
                                    |                 |
                                    v                 v
                                  ESP32           FS-iA6B
```

### Power considerations

* The 3S LiPo battery is the primary power source.
* The motor drivers receive the required motor supply directly from the battery.
* LM2596 buck converters step down the battery voltage for low-voltage electronics.
* The ESP32 is supplied with regulated approximately 5V through its VIN/5V power input.
* Receiver and logic supplies are regulated separately according to the final wiring configuration.
* Common grounding is maintained between the control electronics and motor-driver control signals.

---

## 🧰 Hardware Components

| Component               | Quantity    | Purpose                           |
| ----------------------- | ----------- | --------------------------------- |
| ESP32                   | 1           | Main microcontroller              |
| FlySky FS-iA6B Receiver | 1           | Wireless RC signal receiver       |
| RC Transmitter          | 1           | Wireless control                  |
| BTS7960 Motor Driver    | 2           | High-current DC motor control     |
| DC Motors               | 2*          | Vehicle propulsion                |
| LM2596 Buck Converter   | 2           | DC voltage regulation             |
| 3S LiPo Battery         | 1           | Main power source                 |
| 100 µF Capacitor        | 1           | Power-supply filtering            |
| 22 µF Capacitor         | 1           | Additional power-supply filtering |
| Motor Driver Heatsinks  | 2           | Thermal management                |
| Jumper/Connecting Wires | As required | Electrical connections            |
| RC Chassis and Wheels   | 1 set       | Mechanical structure              |

*The listed configuration uses two motor channels. If multiple motors are mechanically connected to each side, the final motor arrangement should be documented separately.

---

## 🧠 Control System

The control process is:

```text
RC Transmitter
      ↓
FS-iA6B Receiver
      ↓
ESP32
      ↓
Input Processing
      ↓
PWM Generation
      ↓
BTS7960 Motor Drivers
      ↓
DC Motors
```

The receiver provides the control signals to the ESP32.

The ESP32 reads the receiver inputs and converts the commands into PWM outputs for the motor drivers.

The PWM duty cycle is used to control motor speed.

---

## ⚡ Motor Control

Each BTS7960 motor driver is used to control a DC motor.

The BTS7960 provides a high-current interface between the low-power ESP32 control signals and the motors.

The ESP32 generates PWM control signals that determine the motor operation.

Basic control concept:

```text
Higher PWM Duty Cycle
        ↓
Higher Motor Drive
        ↓
Higher Motor Speed*
```

*Actual motor speed depends on motor characteristics, battery voltage, mechanical load, gearing, and other factors.

---

## 🔧 Main Electronic Connections

### ESP32 → BTS7960

The ESP32 provides the control signals to the BTS7960 drivers.

Example GPIO allocation:

```text
BTS7960 #1
RPWM → ESP32 GPIO 25
LPWM → ESP32 GPIO 26

BTS7960 #2
RPWM → ESP32 GPIO 27
LPWM → ESP32 GPIO 14
```

> These GPIO numbers should match the final version of the code and actual hardware wiring.

### FS-iA6B → ESP32

The receiver provides control signals to the ESP32 through the required receiver channels.

Example:

```text
FS-iA6B CH1 → ESP32 input
FS-iA6B CH2 → ESP32 input
```

The exact GPIO assignment should match the final code.

---

## 💻 Software

### Microcontroller

* ESP32
* Arduino-compatible development environment

### Programming

* C/C++
* Embedded programming
* PWM motor control
* RC receiver signal processing

### Development Tools

* Arduino IDE
* Serial Monitor
* Multimeter for hardware debugging

---

## 🧪 Testing and Debugging

One of the major learning outcomes of this project was troubleshooting real hardware problems.

During development, several issues were encountered and investigated, including:

### Motor activation without control input

The motors initially activated unexpectedly when the battery was connected.

This led to investigation of:

* PWM input states
* Enable pins
* Ground connections
* Motor-driver wiring
* Floating control inputs

### Receiver communication

The FS-iA6B receiver was tested for:

* Correct power supply
* Receiver binding
* Channel signal output
* Ground connection

### ESP32 power problems

The ESP32 was tested using:

* USB power
* Regulated buck-converter power

Voltage measurements were performed using a multimeter to identify power-related problems.

### Thermal management

Heat generation in the motor-driver system was considered during testing.

Heatsinks were added to the motor drivers to improve thermal management.

---

## 📊 Power Electronics Concepts Explored

This project provided practical exposure to:

* DC-DC buck conversion
* Voltage regulation
* PWM
* DC motor control
* High-current motor drivers
* LiPo battery systems
* Power distribution
* Common-ground configuration
* Supply filtering
* Capacitors
* Thermal management
* Electrical troubleshooting

---

## 🧪 Future Improvements

The current project can be extended with:

* Battery voltage monitoring
* Motor current sensing
* Improved power filtering
* PCB-based circuit design
* Dedicated power distribution board
* Improved motor-driver cooling
* Fail-safe motor shutdown
* Motor feedback
* Closed-loop motor control
* Wireless telemetry
* Improved mechanical chassis
* Battery protection and monitoring

---

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

* Embedded systems
* Microcontroller programming
* RC receiver interfacing
* PWM generation
* DC motor control
* Motor-driver interfacing
* DC-DC voltage regulation
* LiPo battery-powered systems
* Circuit prototyping
* Multimeter-based debugging
* Power distribution
* Thermal management
* Troubleshooting real-world hardware

---



## 🚀 Project Status

**Status:** Hardware prototype / development

The project is being developed and tested incrementally, with improvements being made to the power system, motor control, receiver interface, and overall reliability.

---

## 👤 Project Type

**Individual / Self-Initiated Project**

This project was independently conceived, assembled, tested, and debugged to gain practical experience in embedded systems and power electronics.

---

## 📌 Key Skills Demonstrated

```text
ESP32
Embedded C/C++
PWM Motor Control
RC Receiver Interfacing
BTS7960 Motor Drivers
LM2596 Buck Converters
LiPo Battery Systems
DC Motor Control
Voltage Regulation
Power Distribution
Circuit Debugging
Multimeter Testing
Thermal Management
Hardware Prototyping
```

---

## 📄 License

This project is available under the MIT License.

````

### One thing I want you to change

Don't blindly upload that README **before the car is actually working**. Your GitHub should document the real state of the project.

For example, you currently have had issues with the ESP32 and receiver. So don't write *"functional wireless RC car"* if it isn't currently functional. Once you get it working, change the status to:

```text
Status: Completed Prototype
````

