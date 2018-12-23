#include <DCCar.h>

DCCar dc;

void counterL();
void counterR();

void setup() {
  dc.init(10, 9, 6, 5, 3, 2);

  //- 20181223: running these commands in the main program because counterL and counterR need to be static
  //- functions in order to reside in the .cpp file.  We can implement this later.
  attachInterrupt(digitalPinToInterrupt(dc.encoderL_global),counterL,RISING);
  attachInterrupt(digitalPinToInterrupt(dc.encoderR_global),counterR,RISING);
}

void loop() {
  dc.forward(200,60);
  delay(1000);
  dc.backward(200,60);
  delay(1000);
  dc.left(200,60);
  delay(1000);
  dc.right(200,60);
  delay(1000);
}

void counterL(){
  dc.countL++;
  if (dc.countL>dc.cnt_global){
    digitalWrite(dc.leftA_global,LOW);
    digitalWrite(dc.leftB_global,LOW);
  }
}

void counterR(){
  dc.countR++;
  if (dc.countR>dc.cnt_global){
    digitalWrite(dc.rightA_global,LOW);
    digitalWrite(dc.rightB_global,LOW);
  }
}
