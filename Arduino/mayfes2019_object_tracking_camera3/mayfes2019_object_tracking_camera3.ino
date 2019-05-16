#include <VarSpeedServo.h>
using namespace std;

VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
int Status=0;
int speed1=0,speed2=0,speed3=0,speed4=0,theta1=45,theta2=90,theta3=45,theta4=90,destination1=45,destination2=90,destination3=45,destination4=90;
int a_max=5;
int a2_max=5;
int speed_max=255;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(6);
  Serial.begin(9600);
  servo1.write(theta1,10,true);
  servo2.write(theta2,10,true);
  servo3.write(theta3,10,true);
  servo4.write(theta4,10,true);
}




void loop() {
  if (Serial.available() >= sizeof(char)*4){
    if(Serial.read()=='H'){
      Status=0;
      char servo_number = Serial.read();
      int Theta = (int)Serial.read();
      int Speed = (int)Serial.read();
      if(servo_number == '1'){
        //speed1=Speed;
        destination1=Theta;
        unsigned char nowtheta=(unsigned char)servo1.read();
        Serial.println((unsigned char)201);
        Serial.println(nowtheta);
      }
      if(servo_number == '2'){
        //speed2=Speed;
        destination2=Theta;
        unsigned char nowtheta=(unsigned char)servo2.read();
        Serial.println((unsigned char)202);
        Serial.println(nowtheta);
      }
      if(servo_number == '3'){
        //speed3=Speed;
        destination3=Theta;
        unsigned char nowtheta=(unsigned char)servo3.read();
        Serial.println((unsigned char)203);
        Serial.println(nowtheta);
      }
      if(servo_number == '4'){
        //speed4=Speed;
        destination4=Theta;
        unsigned char nowtheta=(unsigned char)servo4.read();
        Serial.println((unsigned char)204);
        Serial.println(nowtheta);
      }
    }
  }

  
  speed1 = min(speed1+a_max,(destination1-theta1)^2*a2_max);
  speed2 = min(speed2+a_max,(destination2-theta2)^2*a2_max);
  speed3 = min(speed3+a_max,(destination3-theta3)^2*a2_max);
  speed4 = min(speed4+a_max,(destination4-theta4)^2*a2_max);

  servo1.write(destination1,speed1);
  servo1.write(destination2,speed2);
  servo1.write(destination3,speed3);
  servo1.write(destination4,speed4);


  
  if(!servo1.isMoving() &!servo2.isMoving()&!servo3.isMoving()&!servo4.isMoving()){
    if(Status==5){
      servo1.write(45,255);
      servo2.write(90,255);
      servo3.write(45,255);
      servo4.write(90,255);
      Status=6;
    }
    if(Status==4){
      servo4.write(150,30);
      Status=5;
    }
    if(Status==3){
      servo4.write(30,30);
      Status=4;
    }
    if(Status==2){
      servo3.write(90,30);
      Status=3;
    }
    if(Status==1){
      servo3.write(150,30);
      Status=2;
    }
    if(Status==0){
      servo3.write(30,30);
      Status=1;
    }
    if(Status==6){
      Status=0;
    }
  }
}
