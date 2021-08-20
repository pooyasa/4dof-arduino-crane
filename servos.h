byte full[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
};
Servo link1; //PIN 9
Servo link2; //PIN 10
Servo link3; //PIN 11
Servo clamp; //PIN 5

uint8_t servoSpeed = 5; // 1 to 100
int angles[3];


/*void solveBackwardEquations(int16_t X,int16_t Y,int16_t Z , int* returnAngles){
  returnAngles[0] = X * 10;
  returnAngles[1] = Y * 10;
  returnAngles[2] = Z * 10;
}*/

void writeAngles(int* theAngles){
  //theAngles[1] = 2 * theAngles[1];
  int done = 0;
  while (done < 3){
    done = 0;
    int currentAngles[3] = {
      link1.read(),
      link2.read(),
      link3.read()
    };    
     if (currentAngles[0] < theAngles[0])// check LINK1!
      link1.write(currentAngles[0] +1 );
     else if (currentAngles[0] > theAngles[0])
      link1.write(currentAngles[0] -1 );
     else
      done ++;
     if (currentAngles[1] < theAngles[1])
      link2.write(currentAngles[1] +1 );
     else if (currentAngles[1] > theAngles[1])
      link2.write(currentAngles[1] -1 );
     else
      done ++;
     if (currentAngles[2] < theAngles[2])
      link3.write(currentAngles[2] +1 );
     else if (currentAngles[2] > theAngles[2])
      link3.write(currentAngles[2] -1 );
     else
      done ++;     
     delay(100 /servoSpeed);
   }
   Serial.println("Done!");
}

void clampGoToAngle(double X ,double Y ,double Z) // CONVERT real word tetas to servo angles
{
    angles[0] = X + 90;
    angles[1] = Y * 2;
    Z = 180 - Y - Z + 40;
    angles[2] = Z; 
    writeAngles(angles);
}


/*
 * void clampGoToXYZ(int16_t X,int16_t Y,int16_t Z){
  solveBackwardEquations(X , Y, Z, angles);
  writeAngles(angles);
}
*/
void clampClose(){
  clamp.write(50);  
}

void clampOpen(){
  clamp.write(75);  
}
