//Motor variables

//Port is A
uint8_t Motor1A=9;
uint8_t Motor1B=10;


//starboard is B
uint8_t Motor2A=6;
uint8_t Motor2B=7;


//pins for encoder!
uint8_t encoderA=3;
uint8_t encoderB=2;


uint8_t led = 8;
uint8_t button = 11;


//how much before correction, (used in the encoder)
double maxCorrection = 1.05;
double minCorrection = .95;


//used for speed calculation
double AoverB = 1;
double BoverA = 1;


//encoder counters (try to reset after each comand)
double countA=1;
double countB=1;

//default speed for racer!
//will be used to set the avg speed of the racer
uint8_t targetSpeed = 200;

bool testing = false;
int count = 0;

void counterA(){
  countA++;
  if(countA>=100||countB>100){
    displayCounts();
    //parameters (0 == a / b)   -----    (1 == b / a)
    double AtoBcal = getCalculation(0);
    double BtoAcal = getCalculation(1);


      //can change the correction up in the initial variables
      if(AtoBcal>maxCorrection||AtoBcal<minCorrection){
        digitalWrite(led, HIGH);
        AoverB = AtoBcal;
        Serial.println("Diffrence too great!");
        Serial.println("Reset count and stoping for 5 seconds!");
        halt(3);
        digitalWrite(led, LOW);
      }
      else if(BtoAcal>maxCorrection||BtoAcal<minCorrection){
        digitalWrite(led, HIGH);
        BoverA = BtoAcal;
        Serial.println("Diffrence too great!");
        Serial.println("Reset count and stoping for 5 seconds!");
        halt(3);
        digitalWrite(led, LOW);
      }
      restCount();
  }
  //Serial.println(countA);
}

void counterB(){
  countB++;
}

void setup() {
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2A,OUTPUT);
  pinMode(Motor2B,OUTPUT);
  pinMode(encoderA,INPUT);
  pinMode(encoderB,INPUT);

  pinMode(led,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  //for encoder
  
  attachInterrupt(digitalPinToInterrupt(encoderA),counterA,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB),counterB,RISING);
  Serial.begin(9600);

}


void loop() {
//inital methods I wanted to implement


//  go_left();
//  sharpLeft();
//  go_right();
//  sharpRight();
//  forward();//enter number of sec (example: 3)
//  forward();//enter number of sec and power 0-255 (example: 3,200)
//  back();
//  halt();//enter number of sec (example: 3)
//  spin();//enter number of sec (example: 3)
while(digitalRead(button)==LOW){
  Serial.println("------------------------------------------------------");
  Serial.print("Initiating loop ");
  Serial.println(count++);
  delay(1000);
  
  forward(5,targetSpeed);
  reduceCorrection();//has a halt for 1 sec
  spin(3);
  halt(1);
  Serial.println("END OF LOOP");
  Serial.println();
  Serial.println();

}
  

}

//reduces tolerance for correction by .01
void reduceCorrection(){
  if(maxCorrection>=1.05||minCorrection<=.95){
    maxCorrection=maxCorrection-.01;
    minCorrection=minCorrection+.01;
  }

  Serial.println("Correction limits: ");
  Serial.print("Max Correction: ");
  Serial.println(maxCorrection);
  Serial.print("Min Correction: ");
  Serial.println(minCorrection);
  halt(1);
}


//base forward useing target speed
//take length
void forward(int seconds){
  seconds = seconds * 1000;
  analogWrite(Motor1A,targetSpeed);
  digitalWrite(Motor1B,HIGH);
  analogWrite(Motor2A,targetSpeed);
  digitalWrite(Motor2B,HIGH);
  delay(seconds);
}

//To go at max, go with HIGH + 0 or LOW + 255
//takes length and power
void forward(int seconds, int motorSpeed){
  seconds = seconds * 1000;
  analogWrite(Motor1A,(motorSpeed*AoverB));
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,(motorSpeed*BoverA));
  digitalWrite(Motor2B,LOW);
  delay(seconds);
}


//if (int a) is 0 then comparing A/B else B/A
double getCalculation(int a){
  String motorsCompared = "";
  
  double temp;
  if(a==0){
    motorsCompared = "A/B";
    //compare big number or else it will compare single digit number!
    if(countA>80&&countB>80){
      temp = countA/countB;
      
    }
    //do nothing if not greater than 80
    else{
      temp = 1;
    }
  }
  else{
    motorsCompared = "B/A";
    //compare big number or else it will compare single digit number!
    if(countA>80&&countB>80){
      temp = countB/countA;
      
    }
    //do nothing if not greater than 80
    else{
      temp = 1;
    }
  }
  Serial.print("Returning ");
  Serial.print(motorsCompared);
  Serial.print(": ");
  Serial.println(temp);
  return temp;

}


//for debugging
void displayCounts(){
  Serial.print("A_Rotations: ");
  Serial.println(countA); 
  Serial.print("B_Rotations: ");
  Serial.println(countB); 
}



void spin(int sec){
  analogWrite(Motor1A,targetSpeed);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,0);
  digitalWrite(Motor2B,LOW);
  delay(sec*1000);
  restCount();
  
}

void goLeft(){
  analogWrite(Motor1A,targetSpeed/2);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,targetSpeed);
  digitalWrite(Motor2B,LOW);
  delay(1000);
  restCount();
}

void sharpLeft(){
  analogWrite(Motor1A,0);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,targetSpeed);
  digitalWrite(Motor2B,LOW);
  delay(500);
  restCount();
}

void goRight(){
  analogWrite(Motor1A,targetSpeed);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,targetSpeed/2);
  digitalWrite(Motor2B,LOW);
  delay(1000);
  restCount();
}

void sharpRight(){
  analogWrite(Motor1A,0);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,targetSpeed);
  digitalWrite(Motor2B,LOW);
  delay(500);
  restCount();
}

void back(int sec){
  analogWrite(Motor1A,0);
  digitalWrite(Motor1B,HIGH);
  analogWrite(Motor2A,targetSpeed);
  digitalWrite(Motor2B,HIGH);
  delay(sec*1000);
  halt(1);
}

//used for a general purpose halt that wil rest the encoder counts
//and will also stop the motors
void halt(int seconds){
  restCount();
  Serial.println("going to halt!");
  seconds = seconds * 1000;
  analogWrite(Motor1A,0);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,0);
  digitalWrite(Motor2B,LOW);
  delay(seconds);
}

//sets ecoder counters to one
void restCount(){
  countA=1;
  countB=1;
}

