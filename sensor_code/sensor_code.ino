
// include the lcd library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3,4,5,6,7,8);

//for the mq-2 sensor:
int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
// Your threshold value
int sensorThres = 400;
int potPin1 = smokeA0;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);


}

void loop() {

    MQ2();
    MQ5();
    
//to print on lcd screen:
//    lcd.clear();
//    lcd.setCursor(0,0); 
//    lcd.print("SensorVal1: "); 
//    lcd.print(ratio); 
//    lcd.setCursor(0,1); 

}

void MQ2(){
  //MQ-2 Gas Sensor Code  
  /*-Replace the value with a value from the test of c02 levels in clean area -*/
    float R0 = 0.35;
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(smokeA0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    ratio = RS_gas/R0;  // ratio = RS/R0
          

//    Serial.print("sensor_volt = ");
//    Serial.println(sensor_volt);
//    Serial.print("RS_ratio = ");
//    Serial.println(RS_gas);
//    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
//    Serial.print("\n\n");

    delay(1000);

//  Serial.print("Pin A0: ");
//  Serial.println(sensorValue);
  // Checks if it has reached the threshold value
  if (sensorValue > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(100);

//write values for this sensor
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("SensorVal1: "); 
    lcd.print(ratio); 

  
  }

void MQ5(){
    float R0 = 1;
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL

          /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/R0;  // ratio = RS/R0
          /*-----------------------------------------------------------------------*/

    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);

    Serial.print("\n\n");

    delay(1000);

    
//lcd.clear();
  lcd.setCursor(0,1); 
  lcd.print("Sensor2: ");
  lcd.print(ratio);
  
  }



//code to get the RO
//
//void setup() {
//    Serial.begin(9600);
//}
//
//void loop() {
//    float sensor_volt;
//    float RS_air; //  Get the value of RS via in a clear air
//    float R0;  // Get the value of R0 via in H2
//    float sensorValue;
//
//        /*--- Get a average data by testing 100 times ---*/
//    for(int x = 0 ; x < 100 ; x++)
//    {
//        sensorValue = sensorValue + analogRead(A0);
//    }
//    sensorValue = sensorValue/100.0;
//        /*-----------------------------------------------*/
//
//    sensor_volt = sensorValue/1024*5.0;
//    RS_air = (5.0-sensor_volt)/sensor_volt; // omit *RL
//    R0 = RS_air/6.5; // The ratio of RS/R0 is 6.5 in a clear air from Graph (Found using WebPlotDigitizer)
//
//    Serial.print("sensor_volt = ");
//    Serial.print(sensor_volt);
//    Serial.println("V");
//
//    Serial.print("R0 = ");
//    Serial.println(R0);
//    delay(1000);
//}
