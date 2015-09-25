#include <Servo.h>
#include <Time.h>
#include <Timer.h>
 
Timer t;
Servo myservo;  // create servo object to control a servo
                // twelve servo objects can be created on most boards
 
const int buttonPin = 10;
const int buttonPin2 = 12;
const int buttonSS = 11;
const int buzzerPin = 13;
int pos = 0;    // variable to store the servo position
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int time = 0;
int check1 = 0;
int check2 = 0;
int lock = 1;
 
 
void buzz()
{
  digitalWrite(buzzerPin,HIGH);
  delay(2000);
  digitalWrite(buzzerPin,LOW);
}
void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonSS, INPUT);
  pinMode(buzzerPin,OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonSS);
  time = now() + 5; //adding 5 seconds only changes the time initially and is corrected after the 5 seconds
// I did this so that the pushbuttons could be clicked immediately as opposed waiting 5 seconds at the start
      
 if(buttonState == HIGH && ((time - check1)>=5)) //when the pushbutton is pressed and 5 seconds have passed from the last press
    {
      Serial.println("Doors are unlocking");
      check1 = time;     //resets check1 variable to the current time at the pushbutton press
      lock = 0;
      for(pos = 135; pos >= 0; pos -= 1) // goes from 0 degrees to 135 degrees
      {                                  // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position each 1 degree turn
      }

    if(buttonState == HIGH && lock==0) //when the pushbutton is pressed and the door is already unlocked
    {
      Serial.println("Doors are already unlocked.");
    }
 
  if((buttonState2 == HIGH) && ((time - check2)>=30)) //when the call pushbutton is pressed and 30 seconds have passed from the last press
    {
      Serial.println("Calling 911.");
      buzz();    //buzzes the buzzer to simulate calling 911
      check2 = time;
    }
}
