#include <LiquidCrystal.h>
#include <Servo.h>
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define echo 15
#define trigger 14

Servo myservo;
const int en1 = 10;
const int en2 = 11;
const int en3 = 13;
LiquidCrystal lcd1(12, en2, 5, 4, 3, 2);
LiquidCrystal lcd2(12, en1, 5, 4, 3, 2);
LiquidCrystal lcd3(12, en3, 5, 4, 3, 2);
int pos = 0; // position of servo motor
int IRSensor = 6; // connect ir sensor to arduino pin 6
int LED = 7; // connect Led to arduino pin 7
int LED1 = 17; // connect Led to arduino pin 17
int LED2 = 18; // connect Led to arduino pin 18
int LED3 = 19; // connect Led to arduino pin 19
int LED4 = 20; // connect Led to arduino pin 20
int LED5 = 21; // connect Led to arduino pin 21
int value = 0;
int value1 = 0;
int lm350 = A2; // connect lm35 sensor to arduino pin A2
int lm351 = A3; // connect lm35 sensor to arduino pin A3
float millivolts, millivolts1, cel, cel1; 
long duration;
int distance;
int buzzer = 16; //buzzer to arduino pin 16
int pump = 8; //motor to arduino pin 8

void setup()
{
  lcd1.begin(16,2);
  lcd2.begin(16,2);
  lcd3.begin(16,2);
  pinMode(IRSensor, INPUT); // sensor pin INPUT
  pinMode(LED, OUTPUT); // Led pin OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  myservo.attach(9); //Servo motor connection
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 16 as an output
  pinMode(pump, OUTPUT);
}

void loop()
{
  int sensor_status = digitalRead (IRSensor);
  value = analogRead(lm350); 
  value1 = analogRead(lm351); 
  
  millivolts = (value / 1024.0) * 5 * 1000;
  cel = millivolts / 10;
  float farh = cel * (9 / 5) + 32;
  
  millivolts1 = (value1 / 1024.0) * 5 * 1000;
  cel1 = millivolts1 / 10;
  float farh1 = cel1 * (9 / 5) + 32;

  digitalWrite(trigger, LOW); //clear trigger pin
  delay(2);  
  digitalWrite(trigger, HIGH);
  delay(10);  // Set trigPin on HIGH state for 10 micro seconds  
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;

  displayTemperature();
  waterLevel();

  if (sensor_status == 1) {
    digitalWrite(LED, HIGH); // LED ON
    unlockdoor();
  }
  else
  {
    digitalWrite(LED, LOW); // LED OFF
  }
}

//-------------- Function 1 - OPEN THE DOOR ----------------//
void unlockdoor()
{
  lcd1.setCursor(0,0);
  lcd1.println(" ");
  lcd1.setCursor(2,0);
  lcd1.print("Door Opening");
  lcd1.setCursor(4,1);
  lcd1.println("WELCOME!!");

  for(pos = 0; pos <= 73; pos +=5) // open the door
  { 
    myservo.write(pos); 
    delay(205);     
  }

  counterbeep();

  for(pos = 73; pos>=0; pos-=5) // close the door
  {
    myservo.write(pos); 
    delay(205); 
  } 
}

//-------------- Function 2 - Count down ------------------//
void counterbeep()
{
  lcd1.clear();
  lcd1.setCursor(2,0);
  lcd1.println("GET IN WITHIN:::");

  for(int i = 3; i > 0; i--)
  {
    lcd1.setCursor(8,1);
    lcd1.print(i);
    delay(1000);
  }

  lcd1.clear();
  lcd1.setCursor(2,0);
  lcd1.print("RE-LOCKING");
  delay(500);
  lcd1.setCursor(12,0);
  lcd1.print(".");
  delay(500);
  lcd1.setCursor(13,0);
  lcd1.print(".");
  delay(500);
  lcd1.setCursor(14,0);
  lcd1.print(".");
  delay(400);
  lcd1.clear();
  lcd1.setCursor(4,0);
  lcd1.print("LOCKED!");
  delay(440);
}

//-------------- Function 3 - Display Temperature ------------------//
void displayTemperature()
{
  lcd2.clear();
  lcd2.setCursor(1,0);
  lcd2.print("Temp in Pool!!");
  lcd2.setCursor(0,1);
  lcd2.print("Temperature");
  lcd2.setCursor(12, 1);
  lcd2.print(cel);
  lcd2.setCursor(14, 1);
  lcd2.print("*C");

  lcd3.clear();
  lcd3.setCursor(2,0);
  lcd3.print("Temp in Air!!");
  lcd3.setCursor(0,1);
  lcd3.print("Temperature");
  lcd3.setCursor(12, 1);
  lcd3.print(cel1);
  lcd3.setCursor(14, 1);
  lcd3.print("*C");
}

//-------------- Function 4 - Water level monitoring ------------------//
void waterLevel()
{
  if(distance >= 0 && distance <= 20)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);

    digitalWrite(pump, LOW);
  }
  else if(distance >= 21 && distance <= 40)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);

    digitalWrite(pump, LOW);
  }
  else if(distance >= 41 && distance <= 60)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);

    digitalWrite(pump, LOW);
  }
  else if(distance >= 61 && distance <= 80)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);

    digitalWrite(pump, LOW);
  }
  else if(distance >= 81)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    
    digitalWrite(LED1, HIGH);

    tone(buzzer, NOTE_C4, 500);
    delay(500);
    tone(buzzer, NOTE_D4, 500);
    delay(500);
    tone(buzzer, NOTE_E4, 500);
    delay(500);
    tone(buzzer, NOTE_F4, 500);
    delay(500);
    tone(buzzer, NOTE_G4, 500);
    delay(500);

    digitalWrite(pump, HIGH);
  }
}
