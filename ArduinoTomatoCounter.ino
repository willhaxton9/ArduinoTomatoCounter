#include <LiquidCrystal_I2C.h>
// Pin for what?
#define trigPin 2
#define echoPin 3
LiquidCrystal_I2C lcd(0x27,20,4);

int counter = 0;
int currentState = 0;
int previousState = 0;

long duration, distance;

void setup() {
  lcd.init();
  lcd.backlight();
  // Can it be faster? 115200 or 38400
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Count No : ");
}

// May need to monitor and record the distance (wave) first.
// At different speed, different shapes of "tamato" (balls)


void loop() {
//  long duration, distance;
// Seems like giving a start signal to the ultrasonic sensor?
// Does it have to be done every time before reading the sensor output?
// Check Arduino interrupt
// Try put this getDistance() into attachInterrupt()  
  digitalWrite(trigPin, LOW);
  delay(50);
  digitalWrite (trigPin, HIGH);
  delay(50);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance <= 20){
    currentState = 1;
  }
  else {
    currentState = 0;
  }
  // why delay here?
  delay(50);
  // See if it can be put also to an interrupt function
  if(currentState != previousState){
    if(currentState == 1) {
      counter = counter + 1;
      Serial.println(counter);
      lcd.setCursor(12,0);
      lcd.print(counter);
      delay(50);
    }
  }
}
