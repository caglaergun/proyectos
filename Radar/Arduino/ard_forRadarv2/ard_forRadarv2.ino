#include <Servo.h>. 
#define MotorRE 5
#define MotorLE 10
#define MotorL1 9
#define MotorL2 8
#define MotorR1 7
#define MotorR2 6
#define s0 A1 
#define s1 2
#define s2 3
#define s3 4
#define sensorOut 11
int K, Y, M = 0;
// Ultrasonik Sinyal pinleri
const int trigPin =12;
const int echoPin = 13;
long duration;
int distance;
long sure ;
boolean x=0;
Servo myServo; 

void setup() {
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT); 
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  myServo.attach(A0);// Servo motor sinyal pini
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(s1,LOW); 
  digitalWrite(s0,HIGH);  
  Serial.begin(9600);
}
void loop() {
  ileri();
  delay(100);
  
  for(int i=0; i<=180; i++){ 
myServo.write(i);
delay(30);
distance = calculateDistance(); 
Serial.print(distance);
Serial.print(",");
Serial.print(i);
Serial.print(":");
  if (distance < 30 && x==0 )
  { 
  x=1;
  myServo.detach();
  if ( 0<i<=90)
  {
    
    dur();
    delay(1000);
    sol();
   delay(500);
    ileri();
         
  }
  else if ( 90<i<=180)
  {
     
    dur();
    delay(1000);
    sag(); 
delay(500);
    ileri();
      
  } 
  }
   if (distance<6 && x==1)
 { 
x=0; 
   dur();
   delay(1000);
   renk_olcum();
   delay(1000);
   geri();
   delay(500);
   sol();
   delay(500);
   ileri();
   myServo.attach(A0);
  
  } 
}
for(int i=180; i>0; i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
Serial.print(distance);
Serial.print(",");
Serial.print(i);
Serial.print(":");
if (distance < 30 && x==0 )
  { 
x=1;
  myServo.detach();
  if ( 0<i<=90)
  {
     
    dur();
    delay(1000);
    sag();
    delay(500);  
    ileri();

  }
    else if( 90<i<=180)
  {
  
    dur();
    delay(1000);
    sol(); 
    delay(500);
    ileri();

  }
if (distance<6 && x==1)
 { 
  x=0; 
//Serial.print(distance); 
   dur();
   delay(1000);
   renk_olcum();
   delay(500);
   geri();
   delay(500);
   sag();
   delay(500);
   ileri();
   myServo.attach(A0);
   
  }  

  }
  
  
}
}

int calculateDistance(){ 
   
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;

}
void ileri(){  
    delay(50);
  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 50); 
  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 50); 
}
void geri(){ 
  delay(50);
  digitalWrite(MotorR1, LOW); 
  digitalWrite(MotorR2, HIGH); 
  analogWrite(MotorRE, 50); 
  digitalWrite(MotorL1, LOW); 
  digitalWrite(MotorL2, HIGH); 
  analogWrite(MotorLE, 50); 
}
void sag(){ 
  delay(50);
  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 0); 

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 50); 
}
void sol(){ 
  delay(50);
  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 50); 

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 0); 
}
void dur(){  
  
  digitalWrite(MotorR1, LOW); 
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorL1, LOW); 
  digitalWrite(MotorL2, LOW); 
   analogWrite(MotorRE, 0); 
   analogWrite(MotorLE, 0); 
}

void renk_olcum(){
  
  digitalWrite(s2, LOW); //Kırmızıyı filtrele
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(K); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
 
 
 
  digitalWrite(s2, HIGH); //Yeşili filtrele
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(Y); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  
 
  digitalWrite(s2, LOW); //Maviyi filtrele
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= "); 
  Serial.print(M); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
  
  if(K<70 && M<70 && Y<70) //Eğer tüm renklerin yoğunluğu yüksekse: Beyaz
  {
  Serial.print("Renk = Beyaz   ");
    
  }
  else if(K<100 && Y<M && abs(K-Y)<20)
  
  {
  Serial.print("Renk = Sarı   ");
 
  }
  else if(K<100 && M<Y && abs(M-K)<20)
  {
  Serial.print("Renk = Magenta   ");
 
  }
  else if(Y<130 && Y<M && Y<K)
  
  {
  Serial.print("Renk = Yeşil   ");

  }
  else if(M<100 && M<Y && M<K)

  {
  Serial.print("Renk = Mavi   ");
  
  }
  else if(K<100 && K<Y && K<M)
  
  {
  Serial.print("Renk = Kırmızı   ");
  
  }
  else
  {
  Serial.print("Renk algılanamadı   ");//Belirlediğimiz kıstaslara uymayan diğer renkler
  
  }
  
  Serial.println(); //Serial monitörde bir satır aşağı geç
  delay(1000);//1000 milisaniye bekle
  }
