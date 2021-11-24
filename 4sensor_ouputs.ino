//SOIL SENSOR
int SoilPin = A3;
int SensorValue = 0;
const int soil_threshold = 50; 

//PH SENSOR
const int PHpin = A2;
float Po = 0;
const int threshold = 30; 


//Water Level
const int analogPin = A0;    // pin that the sensor is attached to
const int sensorPower = 7;
const int WL_threshold = 50; 
// Value for storing water level
int WaterValue = 0;

//TDS STUFF
#include <EEPROM.h>
#include "GravityTDS.h"

const int TdsSensorPin = A1;
const int TDS_threshold = 100; 
GravityTDS gravityTds;
 
float temperature = 25,tdsValue = 0;


//BUZZER
int BuzzerPin = 7;

//PUMP
int PumpPin = 8;

void setup(){
//SOIL
 pinMode(SoilPin, INPUT);
//PH
 pinMode(PHpin, INPUT);
//Water Level
// Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
 
  
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
//TDS DISPLAY

   Serial.begin(9600);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
//BUZZER
 pinMode(BuzzerPin, OUTPUT);
//PUMP
 pinMode(PumpPin, OUTPUT);  
}
 
void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
 

    //PH VALUE
 int pengukuranPh = analogRead(PHpin);
 if (pengukuranPh > threshold) {
    digitalWrite(BuzzerPin, HIGH);
  } else {
    digitalWrite(BuzzerPin, LOW);
   Serial.print("Nilai ADC Ph: ");
   Serial.println(pengukuranPh);
   double TeganganPh = 5 / 1024.0 * pengukuranPh;
   Serial.print("TeganganPh: ");
   Serial.println(TeganganPh, 3);
      ///Po = 7.00 + ((teganganPh7 - TeganganPh) / PhStep);
   Po = 7.00 + ((2.6 - TeganganPh) / 0.17);
   Serial.print("Nilai PH cairan: ");
   Serial.println(Po, 3);
   delay(5000);

//WATER VALUE
 //get the reading from the function below and print it
 int level = WaterValue();

 if (analogValue > WL_threshold) {
    digitalWrite(BuzzerPin, HIGH);
  } else {
    digitalWrite(BuzzerPin, LOW);
  }
  
  Serial.print("Water level: ");
  Serial.println(level);
  delay(1000);


//SOIL READINGS
 if (SensorValue < soil_threshold) {
    digitalWrite(PumpPin, HIGH);
  } else {
    digitalWrite(PumpPin, LOW);
  }

SensorValue = analogRead(SoilPin);
Serial.println(SensorValue);
delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(PHpin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading

    delay(1000);
}
