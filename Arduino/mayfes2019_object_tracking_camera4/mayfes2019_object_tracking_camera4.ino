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
  Serial.begin(115200);
  servo1.write(45,10,true);
  servo2.write(90,10,true);
  servo3.write(45,10,true);
  servo4.write(90,10,true);
}





void loop() {
  if (Serial.available() >= sizeof(char)){
    char header = Serial.read();
    if(header=='H'){
      Serial.write('a');
      while(Serial.available() < sizeof(char)*3){
      }
      Status=0;
      char servo_number = Serial.read();
      int Theta = (int)Serial.read();
      int Speed = (int)Serial.read();
      if(servo_number == '1'){
        servo1.write(Theta,Speed);
      }
      if(servo_number == '2'){
        servo2.write(Theta,Speed);
      }
      if(servo_number == '3'){
        servo3.write(Theta,Speed);
      }
      if(servo_number == '4'){
        servo4.write(Theta,Speed);
      }
    }
    if(header == 'S'){
      unsigned char nowtheta1=(unsigned char)servo1.read();
      Serial.write((unsigned char)201);
      Serial.write(nowtheta1);
      unsigned char nowtheta2=(unsigned char)servo2.read();
      Serial.write((unsigned char)202);
      Serial.write(nowtheta2);
      unsigned char nowtheta3=(unsigned char)servo3.read();
      Serial.write((unsigned char)203);
      Serial.write(nowtheta3);
      unsigned char nowtheta4=(unsigned char)servo4.read();
      Serial.write((unsigned char)204);
      Serial.write(nowtheta4);
    }
  }
  if(!servo1.isMoving() &!servo2.isMoving()&!servo3.isMoving()&!servo4.isMoving()&0){
    if(Status==0){
      servo1.write(45,25);
      servo2.write(90,25);
      servo3.write(45,25);
      servo4.write(90,25);
      servo1.wait();
      servo2.wait();
      servo3.wait();
      servo4.wait();
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
