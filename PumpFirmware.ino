


#include "max6675.h"

const int DEBUG = 1; 

//Thermocouples Max 6675, type k 
int DO = 13;
int wCS = 12; //water temp
int bCS = 11; //box temp
int CLK = 10;
MAX6675 waterTemp(CLK, wCS, DO);
MAX6675 boxTemp(CLK, bCS, DO);


//btns for pump and heater
int pumpBtn_p = 5;    //controls the logic
int pumpBtn_lp = 6;   //for the light
int heaterBtn_p = 4;  //controls the logic
int heaterBtn_lp = 7; //for the light
int relayP = 3; // turns on the relay for the pump
int relayH = 2; // turns on the relay for the heater

bool pumpON = false;
bool heaterON = false;
bool heaterONbtn = false;

int waterTempMax = 180;
int boxTempMax = 200;

void setup() {
  Serial.begin(9600);
  
  pinMode(pumpBtn_p, INPUT_PULLUP);
  pinMode(pumpBtn_lp, OUTPUT);
  pinMode(heaterBtn_p, INPUT_PULLUP);
  pinMode(heaterBtn_lp, OUTPUT);

  pinMode(relayP, OUTPUT);
  pinMode(relayH, OUTPUT);

  
}

void loop() {
  
//  Serial.print("box temp: ");
//  Serial.println(boxTemp.readCelsius());
  Serial.print("water temp: ");
  Serial.println(waterTemp.readCelsius());
  //Serial.print("   box temp: ");
  //Serial.println(boxTemp.readCelsius());

  //Serial.println(!digitalRead(pumpBtn_p));
  //Serial.println(!digitalRead(heaterBtn_p));
  
  /*
  if(boxTemp.readFahrenheit() < boxTempMax){  //if box is below temp then proceed to check the pump
    if(DEBUG>2) {
      //Serial.print("Box temp < ");
      //Serial.println(boxTempMax);
    }
    */
    if(!digitalRead(pumpBtn_p)){  //if the pump button is pressed then proceed to chedk the heater overtemp
      digitalWrite(relayP, HIGH);
      digitalWrite(pumpBtn_lp, HIGH);
      if(DEBUG>3) Serial.println("Pump button pressed");
      
      if(waterTemp.readFahrenheit() < waterTempMax && !digitalRead(heaterBtn_p)){  //if heater overtemp < threshold and heater button pressed then allow PID control of the heater
         digitalWrite(relayH, HIGH);
         digitalWrite(heaterBtn_lp, HIGH);
         if(DEBUG>3) Serial.println("Heater button Pressed and water temp below threshold");
         
      }else{ //else heater overtemp > threshold or heater button not selected then restrict heater
      digitalWrite(relayH, LOW);
      digitalWrite(heaterBtn_lp, LOW);
     if(DEBUG>3) Serial.println("Heater Restricted");
  
    }}else{ //else if the pump is off then, restrict PID control of heater
    digitalWrite(relayP, LOW);
    digitalWrite(pumpBtn_lp, LOW);
    if(DEBUG>3) Serial.println("Pump Off");
    digitalWrite(relayH, LOW);
    digitalWrite(heaterBtn_lp, LOW);
    if(DEBUG>3) Serial.println("Heater Restricted");
  /*   
  }}else{  //else if box is above temp; then restrict both the pump and the heater
  digitalWrite(relayP, LOW);
  digitalWrite(relayH, LOW);
  digitalWrite(pumpBtn_lp, LOW);
  digitalWrite(heaterBtn_lp, LOW);
  if(DEBUG>2) Serial.println("Box Overtemp: Pump Off and Heater Restricted");
*/

  
  }
  
   
  if(DEBUG>2) delay(2000);
  delay(200);
}

/*

  //check to see if the SSR are overheating, if so, turn off the pump and heater to let them cool down
  if(boxTemp.readFahrenheit() > boxTempMax){
    pumpON = false; 
    heaterON = false; 
  }

  //monitor the water temp if the pump is on 
  if(pumpON && waterTemp.readFahrenheit() < waterTempMax && heaterONbtn){
    heaterON = heaterONbtn; 
  } else heaterON = false; 

  //turn on the pump and heater respectively
  if(pumpON) digitalWrite(relayP, HIGH);
  if(heaterON && pumpON) digitalWrite(relayH, HIGH);

  if(DEBUG>0){
    Serial.print("Pump Info: wT: ");
    Serial.print(waterTemp.readFahrenheit()); 
    Serial.print("  aT: ");
    Serial.println(boxTemp.readFahrenheit());
  }
  
}
*/
