//Motor variables

//Port is A
uint8_t Motor1A=9;
uint8_t Motor1B=10;

//starboard is B
uint8_t Motor2A=6;
uint8_t Motor2B=7;


//pins for encoder!
int encoderA=3;
int encoderB=2;

//how much before correction, (used in the encoder)
double maxCorrection = 1.05;
double minCorrection = .95;


//used for speed calculation
double AoverB = 1;
double BoverA = 1;

double countA=1;
double countB=1;

//default speed for racer!
uint8_t targetSpeed = 200;

bool testing = false;
int count = 0;

void counterA(){
  countA++;
  if(countA>=100){
    displayCounts();

  //parameters (0 == a / b)   -----    (1 == b / a)
  double AtoBcal = getCalculation(0);
  double BtoAcal = getCalculation(1);


  
    if(AtoBcal>maxCorrection||AtoBcal<minCorrection){
      AoverB = AtoBcal;
      Serial.println("Diffrence too great!");
      Serial.println("Reset count and stoping for 5 seconds!");
      halt(5);
    }
    else if(BtoAcal>maxCorrection||BtoAcal<minCorrection){
      BoverA = BtoAcal;
      Serial.println("Diffrence too great!");
      Serial.println("Reset count and stoping for 5 seconds!");
      halt(5);
    }
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

  //for encoder
  attachInterrupt(digitalPinToInterrupt(encoderA),counterA,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderB),counterB,RISING);
  Serial.begin(9600);

}


void loop() {
//  go_left();
//  go_right();
//  forward();
//  back();
//  halt();

  Serial.println("------------------------------------------------------");
  Serial.print("Initiating loop ");
  Serial.println(count++);

  
  forward(5,targetSpeed);
  //halt(1);
  Serial.println("END OF LOOP");
  Serial.println();
  Serial.println();

}

void forward(int seconds){
  seconds = seconds * 1000;
  analogWrite(Motor1A,150);
  digitalWrite(Motor1B,HIGH);
  analogWrite(Motor2A,150);
  digitalWrite(Motor2B,HIGH);
  delay(seconds);
}

//To go at max, go with HIGH + 0 or LOW + 255
void forward(int seconds, int motorSpeed){
  seconds = seconds * 1000;
  analogWrite(Motor1A,(motorSpeed*AoverB));
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,(motorSpeed*BoverA));
  digitalWrite(Motor2B,LOW);
  delay(seconds);
}

double getCalculation(int a){
  double temp;
  String motorsCompared = "";
  if(a==0){
    motorsCompared = "A/B";
    //compare big number or else it will compare single digit number!
    if(countA>80&&countB>80){
      temp = countA/countB;
      
    }
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

void displayCounts(){
  Serial.print("A_Rotations: ");
  Serial.println(countA); 
  Serial.print("B_Rotations: ");
  Serial.println(countB); 
}

void goLeft(){
  
}

void goRight(){
  
}

void halt(int seconds){
  Serial.println("going to halt!");
  seconds = seconds * 1000;
  analogWrite(Motor1A,0);
  digitalWrite(Motor1B,LOW);
  analogWrite(Motor2A,0);
  digitalWrite(Motor2B,LOW);
  restCount();
  delay(seconds);
}

void restCount(){
  float countA=1;
  float countB=1;
}

