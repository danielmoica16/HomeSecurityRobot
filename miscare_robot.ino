#include <Servo.h>
#define SERVO_PIN     9  
#define Echo_PIN    11 
#define Trig_PIN    12  
#define BUZZ_PIN     13
#define SPEED  500     
int stanga ,centru, dreapta, diagonalastanga, diagonaladreapta;
const int distantalimita = 27;         
const int sidedistantalimita = 12; 
int distanta;
int num = 0;
const int intoarcere = 3000; 
int t;
Servo head;
void servo() {
  head.attach(SERVO_PIN); 
  head.write(90);
}
int MOTOR2_PIN1 = 3;
int MOTOR2_PIN2 = 5;
int MOTOR1_PIN1 = 6;
int MOTOR1_PIN2 = 9;
void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  }
  else {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }

  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  } else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}
void buzz_ON()  
{
  digitalWrite(BUZZ_PIN, LOW);
}
void buzz_OFF() 
{
  digitalWrite(BUZZ_PIN, HIGH);
}
void alarm(){
   buzz_ON();
   delay(100);
   buzz_OFF();
}
int observa(){
  long dep;
  digitalWrite(Trig_PIN,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(Trig_PIN,HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN,LOW);
 dep=pulseIn(Echo_PIN,HIGH);
  dep=dep*0.01657; 
  return round(dep);
}

void imprejurimi(){                     
  centru= observa();
  if(centru<distantalimita){
    alarm();
    }
  head.write(120);
  delay(100);
 diagonalastanga = observa();                                       
  if(diagonalastanga<distantalimita){
go(0,0);
    alarm();
    }
  head.write(170); 
  delay(300);
  stanga  = observa();
  if(stanga <distantalimita){
go(0,0);
    alarm();
    }
  head.write(120);
  delay(100);
  diagonalastanga=observa();
  if(diagonalastanga<distantalimita){
   go(0,0);
    alarm();
    }
  head.write(90); 
  delay(100);
  centru = observa();
  if(centru<distantalimita){
   go(0,0);
    alarm();
    }
  head.write(40);
  delay(100);
  diagonaladreapta = observa();
  if(diagonaladreapta<distantalimita){
  go(0,0);
    alarm();
    }
  head.write(0);
  delay(100);
  dreapta = observa();
  if(dreapta<sidedistantalimita){
   go(0,0);
    alarm();
    }
  head.write(90); 
  delay(300);
}

void evitare(){
  go(SPEED,SPEED);
  ++num;
  if(num!=0){ 
  imprejurimi();
    if(stanga<sidedistantalimita || diagonalastanga<distantalimita){
      go(SPEED,-SPEED);
      delay(intoarcere);
    }
    if(dreapta<sidedistantalimita || diagonaladreapta<distantalimita){
      go(-SPEED,SPEED);
      delay(intoarcere);
    }
    if((dreapta<sidedistantalimita || diagonaladreapta<distantalimita)\
        &&(stanga<sidedistantalimita || diagonalastanga<distantalimita)\
        &&(centru<distantalimita)){
          go(-SPEED,-SPEED);
          delay(2*intoarcere);
        }
    num=0; 
  }
 distanta = observa(); 
  if (distanta<distantalimita){ 
      ++t;}
  if (distanta>distantalimita){
      t=0;} 
  if (t > 25){
    go(0,0);
    t=0;
  }
}


void setup() {
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT); 
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);  
  buzz_OFF();
  digitalWrite(Trig_PIN,LOW);
  head.attach(SERVO_PIN); 
  head.write(90);
  Serial.begin(9600);

}


void loop()
{ evitare();
imprejurimi();
observa();
}
