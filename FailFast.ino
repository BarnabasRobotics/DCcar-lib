//Motor variables
           
                //////////////////////////////////////////////////////
int MotorA1A=9; //This is in Refrence to the 1st DC Motor as Labeled//
int MotorA1B=10; //////////////////////////////////////////////////////


                 /////////////////////////////////////////////////////
int MotorB1A=4; //This is in refrence to the 2nd DC Motor as Labled//
int MotorB1B=5;  /////////////////////////////////////////////////////

                ////////////////////////////////////////////
int encoderA=3; //Initializes the integer for the encoders//
int encoderB=2; ///////////////////////////////////////////
      
              ////////////////////////////////////////////////////////////////////////////////////////
int countA=1; //Integers to be itterateted upon one full completion(1 revolution/2pi) of the encoder//
int countB=1; ////////////////////////////////////////////////////////////////////////////////////////
//Goals simple function/Movement, moving forward and backward, pausing, right turn, left turn
//Next Week: Maybe using the encoder as an odometer? 

void counterA(){ //Counting the rotations
  countA++;
  Serial.print("A=");
  Serial.println(countA);
}

void counterB(){ //Counting the rotations
  countB++;
  Serial.print("B=");
  Serial.println(countB);
}

void setup() {
  pinMode(MotorA1A,OUTPUT);
  pinMode(MotorA1B,OUTPUT);
  pinMode(MotorB1A,OUTPUT);
  pinMode(MotorB1B,OUTPUT);
  pinMode(encoderA,INPUT);
  pinMode(encoderB,INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderA),counterA,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB),counterB,RISING);
  Serial.begin(9600);

}

void loop() {

 analogWrite(MotorA1A,222);   ////////////////////////////////////////////////////////////////////////////////////////////////
 digitalWrite(MotorA1B,LOW);  //Adjusting potential so that it will spin at approximately the same speed as the other motor"//
                              ////////////////////////////////////////////////////////////////////////////////////////////////

  analogWrite(MotorB1A,125);    ///////////////////////////////////////////////////////////////
  digitalWrite(MotorB1B,HIGH);  //Adjusted Potential so that it will spin at the proper speed//
                                ///////////////////////////////////////////////////////////////
  
  
  
  


 

}

