/* 
	DCCar.cpp - Libary for controlling the Barnabas Racer - DC Car version
	Created by Eric Lin & Ed Li, 12/23/2018
*/

#include "Arduino.h"
#include "DCCar.h"

void DCCar::init(int leftA, int leftB, int rightA, int rightB, int encoderL,int encoderR) 
{
      leftA_global=leftA;
      rightB_global=rightB;
      rightA_global=rightA;
      encoderL_global=encoderL;
      encoderR_global=encoderR;

      //- 20181223: running these commands in the main program.  Unable to get it to compile here.
      //- counterL and counterR need to be static functions to work.  Implement this later.
      //  attachInterrupt(digitalPinToInterrupt(encoderL_global),counterL,RISING);
      //  attachInterrupt(digitalPinToInterrupt(encoderR_global),counterR,RISING);
      pinMode(leftA,OUTPUT);
      pinMode(leftB,OUTPUT);
      pinMode(rightA,OUTPUT);
      pinMode(rightB,OUTPUT);
      pinMode(encoderL,INPUT);
      pinMode(encoderR,INPUT);

      countL=0;
      countR=0;
      cnt_global=0;
}

void DCCar::forward(int spd, int cnt)
{
      countL=0;
      countR=0;
      cnt_global=cnt;
      digitalWrite(leftB_global,LOW);
      digitalWrite(rightB_global,LOW);
      analogWrite(leftA_global,spd);
      analogWrite(rightA_global,spd);
}


void DCCar::backward(int spd, int cnt)
{
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftB_global,spd);
      analogWrite(rightB_global,spd);
      digitalWrite(leftA_global,LOW);
      digitalWrite(rightA_global,LOW);
}

void DCCar::left(int spd, int cnt)
{
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftB_global,spd);
      digitalWrite(leftA_global,LOW);
      digitalWrite(rightB_global,LOW);
      analogWrite(rightA_global,spd);
}

void DCCar::right(int spd, int cnt)
{
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftA_global,spd);
      digitalWrite(leftB_global,LOW);
      digitalWrite(rightA_global,LOW);
      analogWrite(rightB_global,spd);
} 
