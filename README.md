# Force finger flexor load cell data gather

This project utilizes a load sensor, a microcontroller (ESP32) and python scripts and a one arm hangboard. Using this class the user can gather data to perform different test. The goal is to adquire data to be post-process in other scripts. It is set up to gather the following test:

- Endurance test: Using the 7:3 protocol for 24 set (4 minutes) it gather enought data to find the critical force and W'

- Max force Test: This test requires the test subject to do a max effort pull for 10 seconds. This should be enough to adquire max pull strength, rate of force development and rate of decay. 

# Set-up:

## Microcontroller - ESP32

### Hardware

- Load cell
- HX711
- ESP32

### Connection

Connect the load cell

## PC - Python script

Once the ESP32 is up and running the only thing is make sure that your ip address and port are correct and run the script


## Todo:

- [ ] Endurance test
    - [ ] Increase the rate of adquisition of HX711 by setting the pull-up resistor to high (ei. going from 10 Hz to 80 Hz)
    - [ ] Probably need increase a rate of transmition but not sure.

- [ ] Max Force test
    - [ ] Create the 

