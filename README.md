# Plant Monitoring System - Arduino

This Arduino code is part of a plant monitoring system that measures soil moisture, temperature, and humidity using sensors and communicates the data over a serial connection.

## Requirements

- Arduino board (compatible with the Arduino IDE)
- DHT11 temperature and humidity sensor
- Moisture sensor (resistive in this case)
- RGB LED or individual LEDs connected to digital pins
- Serial connection for communication

## Setup

1. Connect the DHT11 sensor to the designated pin on the Arduino board with a long set of wires and mount it near your plant
2. For the soil sensor, wrap a wire around a nail for each probe (you'll need 2) and connect one to the analog input and one to ground.
    You'll need to push the probes into the soil of your plant about an inch or two (5-8 cm) apart. Careful of the roots! 
4. Connect the RGB LED or individual LEDs to the specified digital pins on the Arduino board.
5. Ensure that the Arduino board is connected to the computer via a USB cable.

## Functionality

The Arduino code performs the following tasks:

1. Reads the moisture value from the sensor using the analogRead() function.
2. Calculates the moisture percentage based on the raw sensor value.
3. Updates the RGB LED or individual LEDs based on the moisture value and predefined thresholds.
4. Reads the temperature and humidity values from the DHT11 sensor using the DHT library.
5. Prints the collected data in JSON format over the serial connection.

## Customization

You can customize the behavior of the Arduino code by modifying the following variables:

- `TOO_DRY`: The lower threshold for soil moisture level.
- `TOO_WET`: The upper threshold for soil moisture level.
- `RED_PIN`, `GREEN_PIN`, `BLUE_PIN`: The digital pins connected to the RGB LED or individual LEDs.

## Serial Commands

The Arduino code supports the following serial commands:

- `set_min <value>`: Sets the lower threshold for soil moisture level.
- `set_max <value>`: Sets the upper threshold for soil moisture level.

## Usage

1. Connect the Arduino board to your computer and upload the code using the Arduino IDE.
2. Open the serial monitor in the Arduino IDE or any serial communication tool.
3. The Arduino will continuously read the sensor values, update the LEDs, and print the data in JSON format over the serial connection.
4. You can use a script like my plant-health project to read the JSON and (for example) publish it via MQTT

Note: Make sure to install the required libraries (e.g., DHT) in the Arduino IDE before uploading the code.

## Troubleshooting

- If the sensor values are not displayed correctly or the LEDs do not respond, check the connections and ensure the sensors are properly connected.
- If the serial communication is not functioning correctly, verify the serial port settings and the baud rate in the Arduino code.
- Because this is using a resistive soil sensor (basically a couple of nails connected to the pins with wire) its accuracy will fall off with time
- The % derived from the moisture sensor is just a guess and is not indicative of a real moisture %. YMMV

