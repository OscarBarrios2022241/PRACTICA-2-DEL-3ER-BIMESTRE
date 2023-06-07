//PRACTICA BRAZO ROBOTICO
//OSCAR BARRIOS - 2022241

#include <Servo.h>//Librerias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define buzzerpin 8
#define Pul1 7
#define Pul2 6
#define Pul3 5
#define Pul4 4
#define Pul5 3

//Se define los pines de los potenciómetros y los servomotores
const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;

const int servoPin1 = 9;
const int servoPin2 = 10;
const int servoPin3 = 11;

//Notas para el buzzer
const int c=261; 
const int d=294;
const int e=329;
const int f=349;
const int g=391;
const int gS=415;
const int a=440;
const int aS=455;
const int b=466;
const int cH=523;
const int cSH=554;
const int dH=587;
const int dSH=622;
const int eH=659;
const int fH=698;
const int fSH=740;
const int gH=783;
const int gSH=830;
const int aH=880;
bool inter =0;

//Se crea objetos Servo para controlar los servomotores
Servo servo1;
Servo servo2;
Servo servo3;


LiquidCrystal_I2C lcd(0x27, 16, 2);// Inicializa el objeto LiquidCrystal_I2C para la pantalla LCD
 


void setup() {//Se inicializa los pines de los pulsadores
  pinMode(Pul1, INPUT);
  pinMode(Pul2, INPUT);
  pinMode(Pul3, INPUT);
  pinMode(Pul4, INPUT);
  pinMode(Pul5, INPUT);
  

  
  // Inicializa los servomotores
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  attachInterrupt(digitalPinToInterrupt(3) , Interrupcion, FALLING);//Interrupcion que controlara el 5to pulsador
  Wire.begin();// Inicializa la comunicación I2C
  lcd.backlight();// Encender la retroiluminación de la LCD

  // Inicializa la pantalla LCD
  lcd.begin(16, 2);
  lcd.print("Ser1:");//Imprime el texto en la LCD
  lcd.setCursor(0, 1);
  lcd.print("Ser2:");//Imprime el texto en la LCD
  lcd.setCursor(9, 1);
  lcd.print("Ser3:");//Imprime el texto en la LCD
}

void loop() {

  // Lee los valores de los potenciómetros
  int potValue1 = analogRead(potPin1);
  int potValue2 = analogRead(potPin2);
  int potValue3 = analogRead(potPin3);

  // Mapea los valores de los potenciómetros a ángulos para los servomotores
  int servoAngle1 = map(potValue1, 0, 1023, 0, 180);
  int servoAngle2 = map(potValue2, 0, 1023, 0, 180);
  int servoAngle3 = map(potValue3, 0, 1023, 0, 180);

  // Mueve los servomotores a los ángulos correspondientes
  servo1.write(servoAngle1);
  servo2.write(servoAngle2);
  servo3.write(servoAngle3);

  // Actualiza los valores mostrados en la pantalla LCD
  lcd.setCursor(5, 0);
  lcd.print(servoAngle1);
  lcd.setCursor(5, 1);
  lcd.print(servoAngle2);
  lcd.setCursor(14, 1);
  lcd.print(servoAngle3);


  delay(2);//Tiempo antes de repetir el bucle

  if(inter == 1){//Se crea la variable inter para controlar el 5to pulsador
      servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  Zumbador();
  delay(500);
  inter = 0;
  
  }
  //Si se presiona el pulsador 1 se ejecuta esto
  if(digitalRead(Pul1)== 0){
    servo1.write(0);
    servo2.write(20);
    servo3.write(90);
    delay(5000);
  }
  //Si se presiona el pulsador 2 se ejecuta esto
  if(digitalRead(Pul2)== 0){
    servo1.write(80);
    servo2.write(20);
    servo3.write(120);
    delay(5000);
  }
  //Si se presiona el pulsador 3 se ejecuta esto
  if(digitalRead(Pul3)== 0){
    servo1.write(0);
    servo2.write(0);
    servo3.write(10);
    delay(5000);
  }
  //Si se presiona el pulsador 4 se ejecuta esto
  if(digitalRead(Pul4)== 0){
    servo1.write(50);
    servo2.write(80);
    servo3.write(12);
    delay(5000);
  }
  
}

void Zumbador(){//Para el buzzer
  tone(buzzerpin, a, 500);
  delay(500+50);
  tone(buzzerpin, a, 500);
  delay(500+50);     
  tone(buzzerpin, a, 500); 
  delay(500+50);
  tone(buzzerpin, f, 350);  
  delay(350+50);
  tone(buzzerpin, cH, 150);
  delay(150+50); 
    
  tone(buzzerpin, a, 500);
  delay(500+50);
  tone(buzzerpin, f, 350);
  delay(350+50);
  tone(buzzerpin, cH, 150);
  delay(150+50);
  tone(buzzerpin, a, 1000);   
  delay(1000+50);
  noTone(buzzerpin);

}

void Interrupcion(){//Interrupcion que se va a ejecutar al momento de presionar el 5to pulsador
  inter = 1;
}