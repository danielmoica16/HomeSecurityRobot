 #include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
const int temperatura =A2 ;
int val;
int vib_pin=7;
int v;
int fum = A0;
int gaz=A1; 
int sensorThres = 300;             
const int buzzer = 6; 
void buzz(){
 
  tone(buzzer, 5000); 
  delay(1000);        
  noTone(buzzer);    
  delay(1000);       
  
}
 
void setup()
{
    lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(A3, INPUT);
  pinMode(vib_pin,INPUT);
   pinMode(fum, INPUT);
   pinMode(gaz, INPUT); 
     pinMode(temperatura,INPUT);

}
void loop()
{  
//temperatura
int valoare = analogRead(temperatura);
  lcd.setCursor(0,1);
  float m = (valoare / 1024.0) * 5000;
  float celsius = m/ 100  ;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
   lcd.setCursor(0,2);
  lcd.print(celsius);
  lcd.print(" C");
  lcd.setCursor(0,1);
  delay(1000);
  //umiditate
   val = analogRead(A3);
   Serial.println(val);
  if(val>100)
  { 
     Serial.println(val);
    buzz();  
       
   }
   else
   noTone(buzzer);
 //vibratie
   int v;
  v=digitalRead(vib_pin);
  if(v==1)
  { 
     Serial.println(v);
    delay(1000);
  buzz();       
   }
   else
  { 
   noTone(buzzer);
    delay(1000);
  }
   //fum
   int analogSensor = analogRead(fum);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
 
  if (analogSensor > sensorThres)
   {
      Serial.println(analogSensor);
  buzz(); 
  }
   else 
  noTone(buzzer);
  
  delay(1000); 
  //gaz
  int senzor = analogRead(gaz);
  Serial.print("Pin A1: ");
  Serial.println(senzor);
 
  if (senzor > sensorThres)
  {
      Serial.println(senzor);
       buzz();
  }
  else
   noTone(buzzer);
  delay(1000);
  }

