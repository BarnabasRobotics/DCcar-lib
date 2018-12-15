int countL=0;
int countR=0;
int cnt_global=0;
int leftB_global;
int leftA_global;
int rightB_global;
int rightA_global;

void counterL(){
  countL++;
  if (countL>cnt_global){
    digitalWrite(leftA_global,LOW);
    digitalWrite(leftB_global,LOW);
  }
}
void counterR(){
  countR++;
  if (countR>cnt_global){
    digitalWrite(rightA_global,LOW);
    digitalWrite(rightB_global,LOW);
  }
}
class DCcar {
  public:
    int encoderL_global;
    int encoderR_global;
    
    void init(int leftA=10, int leftB=9, int rightA=6, int rightB=5, int encoderL=3,int encoderR=2){
      leftB_global=leftB;
      leftA_global=leftA;
      rightB_global=rightB;
      rightA_global=rightA;
      encoderL_global=encoderL;
      encoderR_global=encoderR;
      attachInterrupt(digitalPinToInterrupt(encoderL_global),counterL,RISING);
      attachInterrupt(digitalPinToInterrupt(encoderR_global),counterR,RISING);
      pinMode(leftA,OUTPUT);
      pinMode(leftB,OUTPUT);
      pinMode(rightA,OUTPUT);
      pinMode(rightB,OUTPUT);
      pinMode(encoderL,INPUT);
      pinMode(encoderR,INPUT);
    }

    void forward(int spd, int cnt){
      countL=0;
      countR=0;
      cnt_global=cnt;
      digitalWrite(leftB_global,LOW);
      digitalWrite(rightB_global,LOW);
      analogWrite(leftA_global,spd);
      analogWrite(rightA_global,spd);
    }

    void backward(int spd, int cnt){
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftB_global,spd);
      analogWrite(rightB_global,spd);
      digitalWrite(leftA_global,LOW);
      digitalWrite(rightA_global,LOW);
    }

    void left(int spd, int cnt){
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftB_global,spd);
      digitalWrite(leftA_global,LOW);
      digitalWrite(rightB_global,LOW);
      analogWrite(rightA_global,spd);
    }

   void right(int spd, int cnt){
      countL=0;
      countR=0;
      cnt_global=cnt;
      analogWrite(leftA_global,spd);
      digitalWrite(leftB_global,LOW);
      digitalWrite(rightA_global,LOW);
      analogWrite(rightB_global,spd);
    } 
};

DCcar dc;

void setup() {
  dc.init();
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
