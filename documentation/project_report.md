# Project Report — Wireless RC Car Using ESP32

## 1. Introduction

This project is a self-initiated wireless RC car developed to gain practical experience with embedded systems, motor control, power electronics, and hardware troubleshooting.

The system uses an ESP32 as the main controller, a FlySky FS-iA6B receiver for wireless control, BTS7960 motor-driver modules for driving the DC motors, and a 3S LiPo battery as the primary power source.

An LM2596 buck converter is used to reduce the battery voltage for the low-voltage electronics.

---

## 2. Project Objectives

The main objectives of the project were:

- Build a wireless RC-controlled vehicle.
- Interface an RC receiver with a microcontroller.
- Control DC motors using PWM.
- Interface the ESP32 with high-current motor drivers.
- Understand DC-DC voltage regulation.
- Learn practical power distribution.
- Gain experience with LiPo-powered systems.
- Develop hardware debugging and troubleshooting skills.

---

## 3. System Architecture

The overall control system can be represented as:

```text
RC Transmitter
      |
      | Wireless Communication
      v
FS-iA6B Receiver
      |
      | CH1 / CH2
      v
ESP32
      |
      | PWM Control
      v
BTS7960 Motor Drivers
      |
      v
DC Motors

The transmitter provides the user's throttle and steering commands.

The receiver passes the corresponding channel signals to the ESP32.

The ESP32 processes these signals and generates PWM outputs for the BTS7960 motor drivers.

4. Power System

The vehicle uses a 3S LiPo battery.

Battery
Nominal voltage: 11.1 V
Fully charged voltage: 12.6 V

The battery provides the main power for the motor-drive system.

An LM2596 buck converter is used to reduce the battery voltage for the low-voltage electronics.

The general power flow is:
3S LiPo Battery
       |
       +--------------------> Motor Drivers
       |
       v
LM2596 Buck Converter
       |
       v
Low-Voltage Electronics
Proper grounding and power distribution are important because the motor system can produce electrical noise and voltage fluctuations.

5. Motor Control

BTS7960 motor-driver modules are used between the ESP32 and the DC motors.

The ESP32 generates PWM signals that control the motor drivers.

The basic control principle is:

RC Input
   ↓
ESP32
   ↓
PWM
   ↓
BTS7960
   ↓
DC Motor

Changing the PWM duty cycle changes the average power delivered to the motor and therefore affects its operating speed under a given load.

The motor direction is controlled using the appropriate RPWM and LPWM inputs of the BTS7960.

6. Receiver Interface

The FlySky FS-iA6B receiver receives commands from the RC transmitter.

The project uses two receiver channels for control:

Channel	Function	ESP32
CH1	Throttle	GPIO 34
CH2	Steering	GPIO 35

The ESP32 reads the receiver signals and converts them into motor-control commands.


7. ESP32 Control

The ESP32 acts as the central control unit.

The planned GPIO allocation is:
| Function       | ESP32 GPIO |
| -------------- | ---------: |
| Throttle input |    GPIO 34 |
| Steering input |    GPIO 35 |
| Motor 1 RPWM   |    GPIO 25 |
| Motor 1 LPWM   |    GPIO 26 |
| Motor 2 RPWM   |    GPIO 27 |
| Motor 2 LPWM   |    GPIO 14 |

8. Differential Drive

The vehicle uses differential motor control for steering.

The general concept is:

Forward:
Left Motor  → Forward
Right Motor → Forward

Reverse:
Left Motor  → Reverse
Right Motor → Reverse

Turn:
Left and Right motor speeds
are changed relative to each other.

This allows steering without requiring a separate steering servo.

9. Hardware Debugging

An important part of the project was dealing with real hardware problems rather than only assembling the circuit.

Several issues were encountered during development.

9.1 Unexpected Motor Movement

At one stage, the motors moved when the LiPo battery was connected even when the receiver was not providing the expected control input.

This required investigation of:

Motor-driver input states
PWM signals
Enable pins
Ground connections
Power connections
Floating control inputs

This demonstrated the importance of defining safe startup states for motor-control systems.

9.2 ESP32 Power Problems

The ESP32 was tested using both USB power and regulated power from an LM2596 buck converter.

The board exhibited abnormal heating during testing.

Voltage measurements and isolation tests were used while investigating the problem.

This highlighted the importance of:

Correct supply voltage
Proper power distribution
Checking polarity
Measuring voltages before connecting sensitive electronics
Avoiding repeated powering of potentially damaged hardware
9.3 LM2596 Buck Converter Failure

An LM2596 module was damaged during the development process.

This provided practical experience with the risks involved when working with battery-powered circuits and DC-DC converters.

The incident reinforced the importance of:

Checking input and output voltage
Checking polarity
Avoiding accidental shorts
Using appropriate wiring
Testing power supplies before connecting expensive components
9.4 Receiver Binding and Signal Testing

The FS-iA6B receiver was tested for wireless communication with the transmitter.

Receiver power, binding, and channel signals were investigated during development.

This helped build an understanding of the difference between:

Powering the receiver
        ≠
Receiving valid control signals

A receiver can have its power LED on while the transmitter-receiver communication is still not correctly established.

10. Thermal Management

BTS7960 motor drivers can generate heat when supplying current to motors, particularly under high load.

Heatsinks were added to the motor-driver modules as part of the thermal-management approach.

Thermal management was considered because motor-driver efficiency, load current, operating time, and mechanical load all affect heat generation.

11. Power Filtering

Capacitors were included as part of the power-filtering considerations.

The project included:

100 µF capacitor
22 µF capacitor

These capacitors can help reduce supply fluctuations and provide local energy storage for transient changes in current demand.

12. Testing Approach

The project was developed incrementally rather than connecting and testing the entire system at once.

The general testing sequence was:

Check Battery Voltage
        ↓
Check Buck Converter Output
        ↓
Check Receiver Power
        ↓
Check Receiver Communication
        ↓
Check ESP32 Power
        ↓
Check Receiver Signals
        ↓
Test Motor Driver
        ↓
Test Motor
        ↓
Integrate Complete System

This approach reduces the chance of damaging multiple components while debugging.

13. Engineering Concepts Learned

The project provided practical exposure to:

Power Electronics
DC-DC buck conversion
Voltage regulation
Power distribution
Supply filtering
Battery-powered systems
Thermal management
Embedded Systems
ESP32
GPIO
PWM
RC receiver interfacing
Embedded C/C++
Motor Control
DC motor driving
BTS7960 motor drivers
Direction control
PWM speed control
Differential drive
Troubleshooting
Multimeter-based testing
Voltage measurements
Grounding problems
Power-supply debugging
Hardware fault isolation
Thermal issues
14. Challenges

The main challenges during development included:

Establishing a reliable power-distribution system.
Understanding the interaction between the ESP32, receiver, and motor drivers.
Preventing unintended motor activation.
Troubleshooting receiver communication.
Dealing with abnormal ESP32 heating.
Handling failure of a buck-converter module.
Managing motor-driver heat.
Ensuring reliable grounding and signal connections.
15. Future Improvements

Possible future improvements include:

Battery voltage monitoring
Motor current sensing
Improved power filtering
Dedicated PCB design
Better thermal management
Motor feedback
Closed-loop speed control
Wireless telemetry
Battery protection and monitoring
Emergency motor shutdown
Improved mechanical design
16. Conclusion

This project provided hands-on experience in combining embedded control with power electronics.

Instead of only working with individual circuits, the project required integrating:

Wireless Communication
        +
Microcontroller
        +
PWM Control
        +
Motor Drivers
        +
DC Motors
        +
DC-DC Conversion
        +
LiPo Battery

The debugging process was an important part of the project and provided practical experience in identifying electrical, power, signal, and thermal problems.

The project forms a foundation for further work in embedded systems, power electronics, motor control, and electric-vehicle-related systems.

17. Project Classification

Project Type: Individual / Self-Initiated

Primary Areas:

Power Electronics
Embedded Systems
Motor Control
Electric Vehicle Systems
Hardware Prototyping
      |
      v
Wheels
