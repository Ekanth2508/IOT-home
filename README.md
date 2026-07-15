# Electronics Projects
A collection of electronics and embedded systems projects
<br>
built using the ESP32 platform.

## IoT Home Automation

Microcontroller: ESP32-C3
<br>

### Version One
A smart home automation system built around an existing timer-
<br>
switch circuit.
<br>
#### Features
- Control of two relay channels
- ESP32-C3 based control system
- Blynk mobile application integration
- Wi-Fi connectivity
- Low-side relay switching interface
- Compact integration inside the original timer switch enclosure
<br>

#### Status
Currently under development

## Automatic Fish Feeder

Microcontroller: ESP32-C3
<br>

### Version 1
An automated fish feeder using internal timekeeping.
<br>

#### Features
- Scheduled feeding at programmed times
- Servo-based dispensing mechanism
- Standalone operation
<br>

#### Limitations
- Dependent on internal timer
- Feeding schedule resets after a power outage
<br>


### Version 2
Improved design using network time synchronization.
<br>

#### Features
- NTP (Network Time Protocol) synchronization
- Wi-Fi connectivity
- Automatic time recovery after power restoration
- Wi-Fi reconnection logic
- Reliable scheduled feeding
<br>

#### Impronements Over Version 1
- No loss of schedule after power outages
- Automatic recovery without user intervention
- Accurate timekeeping through NTP servers
- Better servo optimisation
<br>

#### Status
Currently operational and running successfully.
