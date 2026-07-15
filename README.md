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
#### Features:
- Scheduled feeding at programmed times
- Servo-based dispensing mechanism
- Standalone operation


## Fish Feeder

Microcontroller: ESP32-C3
<br>

### Version One

Based on internal time keeping, programmed time delay.
<br>
Fails during power outage, internal timer resetting.
<br>

### Version Two

NTP server timer request, connected as host node to home WiFi.
<br>
Does not fail during power outage, WiFi reconnection and re-request logic programmed.
<br>
Currently operational
