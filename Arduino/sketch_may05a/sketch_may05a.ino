#include <VarSpeedServo.h>
using namespace std;

VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
int Status=0;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(6);
  Serial.begin(9600);
  servo1.write(45,10,true);
  servo2.write(90,10,true);
  servo3.write(45,10,true);
  servo4.write(90,10,true);
}

void loop() {
  Serial.println("H");
  if (Serial.available() >= sizeof(char)*4){
    if(Serial.read()=='H'){
      Status=0;
      char servo_number = Serial.read();
      int Theta = (int)Serial.read();
      int Speed = (int)Serial.read();
      if(servo_number == '1'){
        servo1.sequenceStop();
        servo1.write(Theta,Speed);
        unsigned char nowtheta=(unsigned char)servo1.read();
        Serial.println((unsigned char)201);
        Serial.println(nowtheta);
      }
      if(servo_number == '2'){
        servo2.sequenceStop();
        servo2.write(Theta,Speed);
        unsigned char nowtheta=(unsigned char)servo2.read();
        Serial.println((unsigned char)202);
        Serial.println(nowtheta);
      }
      if(servo_number == '3'){
        servo3.sequenceStop();
        servo3.write(Theta,Speed);
        unsigned char nowtheta=(unsigned char)servo3.read();
        Serial.println((unsigned char)203);
        Serial.println(nowtheta);
      }
      if(servo_number == '4'){
        servo4.sequenceStop();
        servo4.write(Theta,Speed);
        unsigned char nowtheta=(unsigned char)servo4.read();
        Serial.println((unsigned char)204);
        Serial.println(nowtheta);
      }
    }
  }
  
  if(!servo3.isMoving())Serial.println("3");
  if(!servo4.isMoving())Serial.println("4");
  if(!servo2.isMoving())Serial.println("2");
  if(!servo1.isMoving())Serial.println("1");
  if(!servo1.isMoving() & !servo2.isMoving() & !servo3.isMoving() & !servo4.isMoving()){
    if(Status==5){
      servo1.write(45,25);
      servo2.write(90,25);
      servo3.write(45,25);
      servo4.write(90,25);
      Status=6;
      Serial.println("s5");
    }
    if(Status==4){
      servo4.write(150,30);
      Status=5;
      Serial.println("s4");
    }
    if(Status==3){
      servo4.write(30,30);
      Status=4;
      Serial.println("s3");
    }
    if(Status==2){
      servo3.write(90,30);
      Status=3;
      Serial.println("s2");
    }
    if(Status==1){
      servo3.write(150,30);
      Status=2;
      Serial.println("s1");
    }
    if(Status==0){
      servo3.write(30,30);
      Status=1;
      Serial.println("s0");
    }
    if(Status==6){
      Status=0;
    }
  }
}
