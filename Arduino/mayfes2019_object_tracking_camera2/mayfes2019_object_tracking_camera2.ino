#include <VarSpeedServo.h>
#include<TinyContainer>
using namespace std;

Tiny::vector<VarSpeedServo> servo(4);
int Status=0;


void setup() {
  servo[1].attach(9);
  servo[2].attach(10);
  servo[3].attach(11);
  servo[0].attach(6);
  Serial.begin(9600);
  servo[1].write(45,10,true);
  servo[2].write(90,10,true);
  servo[3].write(45,10,true);
  servo[0].write(90,10,true);
}

void loop() {
  if (Serial.available() >= sizeof(char)*4){
    if(Serial.read()=='H'){
      Status=0;
      char servo_number = Serial.read();
      int Theta = (int)Serial.read();
      int Speed = (int)Serial.read();
      servo[servo_number].write(Theta,Speed);
      unsigned char nowtheta=(unsigned char)servo[servo_number].read();
      Serial.println((unsigned char)200+servo_number);
      Serial.println(nowtheta);
    }
  }
  if(!servo[1].isMoving() &!servo[2].isMoving()&!servo[3].isMoving()&!servo[0].isMoving()){
    if(Status==5){
      servo[1].write(45,255);
      servo[2].write(90,255);
      servo[3].write(45,255);
      servo[0].write(90,255);
      Status=6;
    }
    if(Status==4){
      servo[0].write(150,30);
      Status=5;
    }
    if(Status==3){
      servo[0].write(30,30);
      Status=4;
    }
    if(Status==2){
      servo[3].write(90,30);
      Status=3;
    }
    if(Status==1){
      servo[3].write(150,30);
      Status=2;
    }
    if(Status==0){
      servo[3].write(30,30);
      Status=1;
    }
    if(Status==6){
      Status=0;
    }
  }
}
