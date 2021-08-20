/* 
 * LCD RS pin to digital pin A0
 * LCD Enable pin to digital pin A1
 * LCD D4 pin to digital pin A2
 * LCD D5 pin to digital pin A3
 * LCD D6 pin to digital pin A4
 * LCD D7 pin to digital pin A5
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/


#define S0 2 //grey
#define S1 3 //pink
#define S2 4 //green
#define S3 5 //Yellow
#define sensorOut 6 //BLUE

#define RED_THRESHOLD 1000
#define GREEN_THRESHOLD 400
#define BLUE_THRESHOLD 800


enum theColors {
  RED = 0,
  GREEN,
  BLUE , 
  COLOR_ERROR
};

void sensorBegin()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);  
}
long getRed()
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  return pulseIn(sensorOut, HIGH);
}

long getBlue()
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  return pulseIn(sensorOut, HIGH);
}

long getGreen()
{
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  return pulseIn(sensorOut, HIGH);  
}

void logColors(){
  long frequency = 0;
  frequency = getRed();
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  frequency = getGreen();
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  frequency = getBlue();
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}

uint8_t getColors(){
  uint32_t beginning = millis();
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(F("Identifying"));  
  lcd.setCursor(0,1); 
  lcd.print(F("the color!"));    
  while (millis() < beginning + 10000) // wait Ten seconds
    {
    long red = 0, green = 0, blue = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
      red += getRed();
      delay(10);
      green += getGreen();  
      delay(10);
      blue += getBlue();
      delay(10); 
    }
    red /= 100;
    green /= 100;
    blue /= 100;
    
    if (green >= GREEN_THRESHOLD)
      return GREEN;
    else if (red >= RED_THRESHOLD)
      return RED;
    else if (blue >= BLUE_THRESHOLD)
      return BLUE;
    else 
      continue;
  }
    return COLOR_ERROR;
}
