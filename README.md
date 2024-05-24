# Vehicle Crash Detection and Alert System

This project is a prototype of a vehicle crash detection and alert system that uses an Arduino Uno board, a GPS module, a GSM module, and an MPU6050 accelerometer and gyroscope sensor. The system can detect a sudden change in the acceleration of the vehicle and send an SMS message to a predefined number with the location of the crash.

## Hardware Requirements

- Arduino Uno board
- GPS module (SIM28ML)
- GSM module (SIM900)
- Buzzer (optional)
- Push button (optional)

## Hardware Connections

- Connect the GPS module to the Arduino pin 4 (TX) and pin 3 (RX) using SoftwareSerial.
- Connect the GSM module to the Arduino pin 7 (TX) and pin 8 (RX) using SoftwareSerial.
- Connect the MPU6050 sensor to the Arduino SDA and SCL pins using I2C.
- Connect the buzzer to the Arduino pin 13 (optional).
- Connect the push button to the Arduino pin 12 (optional).

## Software Configuration

1. Set the baud rate of the Serial monitor to 19200.
2. Set the baud rate of the GPS module to 9600.
3. Set the baud rate of the GSM module to 19200.
4. Set the phone number to receive the SMS message in the code.
5. Uncomment the `OUTPUT_READABLE_ACCELGYRO` macro if you want to see the acceleration and gyroscope values in decimal on the Serial monitor.
6. Uncomment the buzzer code snippet if you want to use the buzzer as an alarm.

## How It Works

1. The system initializes the I2C devices and tests the connection with the MPU6050 sensor.
2. The system reads the acceleration and gyroscope values from the MPU6050 sensor and prints them on the Serial monitor.
3. The system checks if the acceleration value in the x-axis is greater than 5000 or less than -5000, which indicates a possible crash.
4. If a crash is detected, the system calls the `sendsms()` function, which does the following:
   - Reads the GPS data from the GPS module and encodes it using TinyGPS++ library.
   - Checks if the GPS location is updated and prints it on the Serial monitor.
   - Sends an AT command to set the GSM module to SMS mode.
   - Sends an AT command to send an SMS message to the predefined phone number with a text that says “A CRASH of vehicle has been detected, please try to contact the driver”.
   - Appends a Google Maps link with the GPS location to the SMS message.
   - Ends the AT command with a `^Z` character, which is ASCII code 26.
   - Waits for 5 seconds to give time for the GSM module to send the SMS message.
5. If a buzzer is connected, it will sound an alarm for 15 seconds after a crash is detected. The alarm can be stopped by pressing a push button.

## Future Improvements

- Adding more sensors to detect other parameters such as airbag deployment, seat belt status, etc.
- Adding a voice call feature to communicate with the driver or emergency services.
- Adding a web server or an app to display and store the crash data.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Special thanks to the contributors and the open-source community for providing the libraries and support needed for this project.
