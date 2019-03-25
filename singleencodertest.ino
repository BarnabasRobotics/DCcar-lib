int Motor1A=9;
int Motor1B=10;
int encoder=3;
int count=0;

void counter(){
  count++;
}

void setup() {
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(encoder,INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder),counter,RISING);
  Serial.begin(9600);

}

void loop() {
  analogWrite(Motor1A,150);
  digitalWrite(Motor1B,LOW);
  Serial.println(count);

}
