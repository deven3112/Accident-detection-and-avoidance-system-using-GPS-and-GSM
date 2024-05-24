#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro;
//MPU6050 accelgyro default address is 0x68; // <-- default AD0 is low 
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;



// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device. arduino pin 4 to Tx of gps and arduino pin 3 to Rx of GPS
SoftwareSerial ss(RXPin, TXPin);
SoftwareSerial SIM900(7, 8);//pin 7 of arduino to tx of gsm and pin 8 nof arduino to rx of gsm
boolean activate;
void setup() {
  pinMode(13,OUTPUT); //For getting a sound from buzzer 
  pinMode(12,INPUT_PULLUP);
  Serial.begin(19200);
  ss.begin(GPSBaud);
  SIM900.begin(19200);
  Serial.print("SIM900 ready...");

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
   // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    Serial.begin(19200); //do not forget to change the baud rate to 19200 in your output screen

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.println(ax); 
        delay(10); 
  if(ax>5000 || ax< -5000){
    sendsms();
    
    /* 
    
    If you want to include the buzzer then uncomment this code snippet
    digitalWrite(13,HIGH);
    delay(15000);
    if(digitalRead(12)==LOW){
      digitalWrite(13,LOW);
      }
    else{
      digitalWrite(13,HIGH);}
    
    */
    }

}
void sendsms(){

if (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("GPS FIXED");
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
SIM900.println("AT + CMGS = \"+91**********\"");
      delay(100);
      Serial.println("Sending SMS");
      SIM900.println("A CRASH of vechicle has been detected, please try to contact the driver");
      delay(100);
       
      // Send the SMS text message
      SIM900.print("https://www.google.com/maps/?q=");
      SIM900.print(gps.location.lat(), 6);
      SIM900.print(gps.location.lng(), 6);
      delay(100);
      // End AT command with a ^Z, ASCII code 26
      SIM900.println((char)26); 
      delay(100);
      SIM900.println();
      // Give module time to send SMS
      delay(5000);  
    
  
}
