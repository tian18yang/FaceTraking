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
  servo4.write(180,10,true);
}

void loop() {
  Serial.println("H");
  if(Status==0 and !servo4.isMoving()){
    servo4.write(180,10,true);
    Status=2;
    Serial.println("0");
  }
  if(Status==1){
    servo4.write(0,10);
    Status=0;
    Serial.println("1");
  }
  if(Status==2){
    Status=1;
  }
}
