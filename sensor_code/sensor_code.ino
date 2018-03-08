//code for Amanda Lewis thesis 2017
//presently includes code for MQ-5, MQ-2, and dust sensor

// include the lcd library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(3,4,5,6,7,8);
LiquidCrystal lcd(12,11,5,4,3,2);

//define parameters for dust sensor
#define        COV_RATIO                       0.2            //ug/mmm / mv
#define        NO_DUST_VOLTAGE                 400            //mv
#define        SYS_VOLTAGE                     5000       

float density, voltage;
int   adcvalue;
const int iled = 9;                                            //drive the led of sensor
const int vout = 1;                                            //analog input

//for the mq-2 sensor:
float ratio2;

//for the mq-5 sensor:
float ratio5;

//water conductivity level
float conductivity;

void setup() {

 // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);  
   Serial.begin(9600);                                         //send and receive at 9600 baud
  
 //  dust sensor
    pinMode(iled, OUTPUT);
    digitalWrite(iled, LOW);                                     //iled default closed
   
}

void loop() {

    MQ2();
    MQ5();
//  dust();
//  waterconductivity();
    
//to print on lcd screen:
//    lcd.clear();
    lcd.setCursor(0,0); 
      lcd.print("MQ2: "); 
      lcd.print(ratio2); 
    lcd.setCursor(0,1); 
      lcd.print("MQ5: "); 
      lcd.print(ratio5); 
      
//delay(200);

//  lcd.clear();
//    lcd.setCursor(0,0); 
//      lcd.print("Dust: ");
//      lcd.print(density);
//      lcd.print(" ug/m3\n");  
//    lcd.setCursor(0,1); 
//    lcd.print("Temp: ");
//    lcd.print(temp);
//    lcd.println(" *C");
  delay(500);
Serial.print(ratio2);
Serial.print(" ");
Serial.print(ratio5);
Serial.print(" ");
Serial.println(density);

}

/*-----------------------------------------------------------------------*/
void MQ2(){
  //MQ-2 Gas Sensor Code  
  /*-Replace the value with a value from the test of c02 levels in clean area -*/
    float R0 = 1.27;
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    int sensorValue = analogRead(A3);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    ratio2 = RS_gas/R0;  // ratio = RS/R0
          
//    Serial.print("sensor_volt = ");
//    Serial.println(sensor_volt);
//    Serial.print("RS_ratio = ");
//    Serial.println(RS_gas);
//    Serial.println("Rs/R0 = ");
//    Serial.print("MQ2: ");
//    Serial.print(ratio2);
//    Serial.println("\n\n");


  }

/*-----------------------------------------------------------------------*/
void MQ5(){
    float R0 = 2.0;
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
//    float ratio5; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL

          /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio5 = RS_gas/R0;  // ratio = RS/R0
          /*-----------------------------------------------------------------------*/

//    Serial.print("sensor_volt = ");
//    Serial.println(sensor_volt);
//    Serial.print("RS_ratio = ");
//    Serial.println(RS_gas);
//    Serial.print("MQ5: ");
//    Serial.print(ratio5);
//    Serial.println("\n\n");
  
  }

/*-----------------------------------------------------------------------*/
void dust(){

//  get adcvalue

  digitalWrite(iled, HIGH);
  delayMicroseconds(280);
  adcvalue = analogRead(vout);
  digitalWrite(iled, LOW);
  
  adcvalue = Filter(adcvalue);
  
  
//  covert voltage (mv)
  voltage = (SYS_VOLTAGE / 1024.0) * adcvalue * 11;
  
//  voltage to density

  if(voltage >= NO_DUST_VOLTAGE)
  {
    voltage -= NO_DUST_VOLTAGE;
    
    density = voltage * COV_RATIO;
  }
  else
    density = 0;
    
  /*
  display the result
  */
//  Serial.print("dust: ");
//  Serial.print(density);
//  Serial.println(" ug/m3\n");  
  

  }  
  
/*-----------------------------------------------------------------------*/
void waterconductivity(){
  int sensorval = analogRead(A2);
  float conductivity = sensorval*(5.0/1023.0);
//  Serial.println(String("Conductivity is ")+ conductivity);
}


/*-----------------------------------------------------------------------*/
/*
private function used for dust sensor
*/
int Filter(int m)
{
  static int flag_first = 0, _buff[10], sum;
  const int _buff_max = 10;
  int i;
  
  if(flag_first == 0)
  {
    flag_first = 1;

    for(i = 0, sum = 0; i < _buff_max; i++)
    {
      _buff[i] = m;
      sum += _buff[i];
    }
    return m;
  }
  else
  {
    sum -= _buff[0];
    for(i = 0; i < (_buff_max - 1); i++)
    {
      _buff[i] = _buff[i + 1];
    }
    _buff[9] = m;
    sum += _buff[9];
    
    i = sum / 10.0;
    return i;
  }
}

