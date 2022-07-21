#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
// Pin for what?
#define trigPin 2
#define echoPin 3
#define echo_int 0
#define TIMER_US 50
#define TICK_COUNTS 4000
LiquidCrystal_I2C lcd(0x27,20,4);

volatile long echo_start = 0;
volatile long echo_end = 0;
volatile long echo_duration = 0;
volatile int trigger_time_count = 0;

int counter = 0;            // still needed??
int currentState = 0;
int previousState = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  // Can it be faster? 115200 or 38400
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Count No : ");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Timer1.initialize(TIMER_US);
  Timer1.attachInterrupt( timerIsr );
  attachInterrupt(echo_int, echo_interrupt, CHANGE)
}

// May need to monitor and record the distance (wave) first.
// At different speed, different shapes of "tamato" (balls)


void loop() {
//  long duration, distance;
// Seems like giving a start signal to the ultrasonic sensor?
// Does it have to be done every time before reading the sensor output?
// Check Arduino interrupt
// Try put this getDistance() into attachInterrupt()  
  getDistance = (echo_duration/2) / 29.1;
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


void timerIsr() 
{
  trigger_pulse();
}

void trigger_pulse()
{
  static volatile int state = 0;

  if (!(--trigger_time_count))
  {
    trigger_time_count = TICK_COUNTS;
    state = 1;
  }

  switch(state)
  {
    case 0:
      break;
    case 1:
      digitalWrite(trigPin, HIGH);
      state = 2;
      break;
    case 2:
    default:
      digitalWrite(trigPin, LOW);
      state = 0;
      break;
  }
}

void echo_interrupt()
{
  switch (digitalRead(echoPin))
  {
    case HIGH:
      echo_end = 0;
      echo_start = micros();
      break;
    case LOW:
      echo_end = micros();
      echo_duration = echo_end = echo_start;
      break;
  }
}
