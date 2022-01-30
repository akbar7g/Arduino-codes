#include <LiquidCrystal_I2C.h>
//Soil Sensor
int Soil_Sensor = A3;
int Soil_Value = 0;
int percentValue = 0;
int alarm = 8;
int Led = 9;

//PH SENSOR
int PhSensorPin = A2;
float Po = 0;

//Water Level
int WlSensorPin = A0;

float panjangSensor = 15.0 ;
// Value for storing water level
int val = 0;
//TDS STUFF
#include <EEPROM.h>
#include "GravityTDS.h"

int TdsSensorPin =  A1;

GravityTDS gravityTds;
 
float temperature = 25,tdsValue = 0;

LiquidCrystal_I2C lcd(0x27 ,20,4);

void setup(){ 
  
  pinMode(WlSensorPin, INPUT);
Serial.begin(9600);
//PH

  pinMode(PhSensorPin, INPUT);
Serial.begin(9600);

//Soil
pinMode(Soil_Sensor, INPUT);

//TDS DISPLAY

   Serial.begin(9600);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    lcd.init();
}
 
void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    lcd.backlight();
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
     lcd.setCursor(0,1);
     lcd.print("Nilai TDS:");
     lcd.print(tdsValue,0);

    //PH VALUE
 int pengukuranPh = analogRead(PhSensorPin);
   lcd.backlight();
   Serial.print("Nilai ADC Ph: ");
   Serial.println(pengukuranPh);
   double TeganganPh = 5 / 1024.0 * pengukuranPh;
   Serial.print("TeganganPh: ");
   Serial.println(TeganganPh, 3);
      ///Po = 7.00 + ((teganganPh7 - TeganganPh) / PhStep);
   Po = 7.00 + ((2.6 - TeganganPh) / 0.17);
   Serial.print("Nilai PH: ");
   Serial.println(Po, 3);
   lcd.setCursor(0,2);
   lcd.print("Nilai PH:");
   lcd.print(Po, 3);
   delay(1000);

//WATER VALUE
 //get the reading from the function below and print it
 int nilai = analogRead(WlSensorPin);
  float VolumeAir = nilai * panjangSensor / 1023;
  lcd.backlight();
  Serial.print("VolumeAir: ");
  Serial.println(VolumeAir);
                                                                                                                                                                                                                                                                                                        
  lcd.setCursor(0,3);
  lcd.print("VolumeAir:");
  lcd.print(VolumeAir);
  lcd.backlight();
  lcd.print("L");
  delay(100);
  
 //Soil Value
int Soil_Value = analogRead(A3);
 Serial.print("\n\Soil Value: ");
 Serial.print(Soil_Value);
  if(Soil_Value>490) digitalWrite(alarm,HIGH);
  if(Soil_Value>490) digitalWrite(Led, HIGH);
  else if(Soil_Value<250) digitalWrite(alarm,LOW);
  if(Soil_Value<250) digitalWrite(Led,LOW);
  delay(100);
   percentValue = map(Soil_Value, 630, 270, 0, 100);
   lcd.backlight();
  Serial.print("\nPercentValue: ");
  Serial.print(percentValue);
  Serial.print("%");
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.print(percentValue);
  lcd.backlight();
  lcd.print("%");
  delay(100);
}
 
