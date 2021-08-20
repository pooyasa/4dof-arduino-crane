#include <Servo.h>
#include <LiquidCrystal.h>

uint8_t theColor;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);  

float resetStateTeta1 = 0, resetStateTeta2 = 70, resetStateTeta3 = 90;
float downTeta1 = 0, downTeta2 = 39, downTeta3 = 90;

int redSitePath1Teta1 = 0 , redSitePath1Teta2 = 60 , redSitePath1Teta3 = 100;
int redSitePath2Teta1 = -10 , redSitePath2Teta2 = 60 , redSitePath2Teta3 = 100;
int redSitePath3Teta1 = -35 , redSitePath3Teta2 = 50 , redSitePath3Teta3 = 105;
float redSiteTeta1 = -35, redSiteTeta2 = 31,  redSiteTeta3 = 110;

int greenSitePath1Teta1 = 0 , greenSitePath1Teta2 = 60 , greenSitePath1Teta3 = 100;
int greenSitePath2Teta1 = 10 , greenSitePath2Teta2 = 60 , greenSitePath2Teta3 = 100;
int greenSitePath3Teta1 = 35 , greenSitePath3Teta2 = 50 , greenSitePath3Teta3 = 105;
float greenSiteTeta1 = 35, greenSiteTeta2 = 31,  greenSiteTeta3 = 110;

int blueSitePath1Teta1 = -15 , blueSitePath1Teta2 = 66 , blueSitePath1Teta3 = 100;
int blueSitePath2Teta1 = -25 , blueSitePath2Teta2 = 62 , blueSitePath2Teta3 = 100;
int blueSitePath3Teta1 = -35 , blueSitePath3Teta2 = 52 , blueSitePath3Teta3 = 105;
float blueSiteTeta1 = -50, blueSiteTeta2 = 50,  blueSiteTeta3 = 60;

/*
int redSitePath1Teta1 = 0 , redSitePath1Teta2 = 60 , redSitePath1Teta3 = 100;
int redSitePath2Teta1 = -10 , redSitePath2Teta2 = 60 , redSitePath2Teta3 = 100;
int redSitePath3Teta1 = -35 , redSitePath3Teta2 = 50 , redSitePath3Teta3 = 105;
float redSiteTeta1 = -35, redSiteTeta2 = 31,  redSiteTeta3 = 110;
*/

#include "Functions.h" // Color Sensor 
#include "servos.h" // Servos
 
void setup() {
  sensorBegin();
  pinMode(12 , INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.createChar(0, full);
  delay(1000);  
  lcd.setCursor(0, 0);  
  lcd.print(F("Initializing!"));
  delay(1000);
  delay(10);
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  lcd.setCursor(1, 1);
  lcd.write(byte(0));
  lcd.setCursor(2, 1);
  lcd.write(byte(0));
//  delay(100);
  lcd.setCursor(3, 1);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);
  lcd.write(byte(0));  
//  delay(100);
    link1.attach(9,500,2300);
  lcd.setCursor(5, 1);  
  lcd.write(byte(0));
  lcd.setCursor(6, 1);  
  lcd.write(byte(0));  
  delay(50);
    link2.attach(10, 1050, 3250); //  link2.write(0) 180
  lcd.setCursor(7, 1);  
  lcd.write(byte(0));
//  delay(50);  
    link3.attach(11);  // 150 > 110 // 40 > 0
  lcd.setCursor(8, 1);  
  lcd.write(byte(0));
  lcd.setCursor(9, 1);  
  lcd.write(byte(0));  
//  delay(50);  
    clamp.attach(5,500,2500); // OPEN80 // Close 50
    Serial.begin(115200);
  lcd.setCursor(10, 1);  
  lcd.write(byte(0));  
  lcd.setCursor(11, 1);  
  lcd.write(byte(0));  
  lcd.setCursor(12, 1);  
  lcd.write(byte(0));          
  lcd.setCursor(13, 1);  
  lcd.write(byte(0));
  lcd.setCursor(14, 1);  
  lcd.write(byte(0));
  lcd.setCursor(15, 1);  
  lcd.write(byte(0));
//  delay(500);    
  lcd.clear();  
//  delay(500);  
  lcd.setCursor(0, 0);
  
  clampGoToAngle(resetStateTeta1,resetStateTeta2,resetStateTeta3); 
  delay(500); 
  clampOpen();
  delay(500);
  clampClose();
  delay(500);

  
  lcd.print ("Waiting!");
}

void loop() {  
  while(digitalRead(12)){  }
  
  if(!digitalRead(12)){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print(F("Starting!"));
    clampGoToXYZ(originX,originY,originZ);
    clampClose();
    theColor = getColors();
    switch (theColor){
      case RED:
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Identified Red!"));
        lcd.setCursor(0,1); 
        lcd.print(F("To the Red!"));      
        clampGoToXYZ(redSiteX,redSiteY,redSiteZ);
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Done!"));
        delay(500);
        break; 
      case GREEN:
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Identified Green"));
        lcd.setCursor(0,1); 
        lcd.print(F("To the Green!"));      
        clampGoToXYZ(greenSiteX,greenSiteY,greenSiteZ);
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Done!"));
        delay(500);      
        break;
      case BLUE:
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Identified Blue"));
        lcd.setCursor(0,1); 
        lcd.print(F("To the Blue!"));     
        clampGoToXYZ(blueSiteX,blueSiteY,blueSiteZ);
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Done!"));
        delay(500);        
        break;  
      case COLOR_ERROR:
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print(F("Couldn't identify"));
        lcd.setCursor(0,1); 
        lcd.print(F("the color :("));     
        break;              
    }
    clampOpen();   
    delay(500);
    clampGoToXYZ(resetStateX,resetStateY,resetStateZ);
  }
  logColors();
  delay(50);
}
