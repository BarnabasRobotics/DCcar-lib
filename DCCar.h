/* 
	dcCar.h - Libary for controlling the Barnabas Racer - DC Car version
	Created by Eric Lin & Ed Li, 12/23/2018
*/

#ifndef dcCar_h
#define dcCar_h

#include "Arduino.h"

class DCCar {
  public:
    int encoderL_global;
    int encoderR_global;

    int leftB_global;
    int leftA_global;
    int rightB_global;
    int rightA_global;
    int countL;
    int countR;
    int cnt_global;	
 
    void init(int leftA, int leftB, int rightA, int rightB, int encoderL,int encoderR);	
    void forward(int spd, int cnt);
    void backward(int spd, int cnt);	
    void left(int spd, int cnt);
    void right(int spd, int cnt);	
            
  private:
    
};

#endif