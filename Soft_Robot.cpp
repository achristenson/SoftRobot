//
//  Soft_Robot.cpp
//  Arduino
//
//  Created by Alex Christenson on 4/21/15.
//  Copyright (c) 2015 Alex Christenson. All rights reserved.
//

#include "Soft_Robot.h"

//Pins for the LCD - uses code from its own library
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

SoftRobot::SoftRobot(){
  //This section of the code gives each variable an Arduino pin
    //These can be adjusted depending upon how the electronics are done
    
    //Joystick
    //Analog A0 and A1 associate a movement with a number
    //A0 for vertical movement - rests at appx. 311, up at 1, down at 500
    vertical = 0;
    //A1 for hosrizontal movement - rests at appx 333, right at 600, left at 1
    horizontal = 1;
    //Digital tell whether button pressed or not - reads HIGH when pressed, LOW if not
    JSPin = 13;
    
    //Pump and the Valve
    //Digital pins 9 and 10 for the solenoid valve and pump
    pumpPin = 10;
    valvePin = 9;
    
    //The LEDs
    //Green
    greenLED = 6;
    //Yellow
    yellowLED = 7;
    //Red
    redLED = 8;
    
    //This section documents the rest of the variables used
    //Counter to iterate through the actions of the robot - 0 Deflated, 1 Inflating, 2 Inflated, 3 Deflating
    count = 0;
    
    //Tells whether to run in manual(true) or automatic(false)
    rT = true;
    
    //Initializes the runtype to match the boolean
    runType[true]="Manual Run";
    runType[false]="Automatic Run";
    
    
}

SoftRobot::~SoftRobot(){
  
}

void SoftRobot::initialize(){
  //Setup code for the robot
  //Set the pump and valve pins to output
  pinMode(pumpPin, OUTPUT);
  pinMode(valvePin, OUTPUT);
  //Read from the Joystick pin
  pinMode(JSPin, INPUT);
  //Put the LEDs in output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  //Start the LCD and display initial text
  lcd.begin(16,2);
  lcd.print("Soft Robot!");
  
  
}

//This is a function that recieves a true or false to turn on or off
//the relay to the pump
void SoftRobot::pump(bool turnOn)
{
  //Recieves wether or not to turn on pump
  if(turnOn)
  {
    //turns on the pump
    digitalWrite(pumpPin,HIGH);
  }
  else
  {
    //when false turns it off
    digitalWrite(pumpPin,LOW);
  }
}

//This is a function that recieves a true or false to turn on or off
//the valve to the pump
void SoftRobot::valve(bool turnOn)
{
  //Recieves wether or not to turn on pump
  if(turnOn)
  {
    //opens the valve
    digitalWrite(valvePin,HIGH);
  }
  else
  {
    //when false closes it
    digitalWrite(valvePin,LOW);
  }
}

//This function is called to turn on lights according to what the robot
//is doing, red for deflated, green for inflated, and yellow for either
//inflating or deflating.
void SoftRobot::lights(){
  //The use of a count here iterates through the steps, and is
  //incremented in the auto run or manual run sequence, depending on
  //which is being used
  if(count%4==0)
  {
    digitalWrite(redLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,LOW);
    //The pump and valve functions are called here in order to coordinate
    //with the colors of the lights
    pump(false);
    valve(false);
  }
  else if(count%4==1)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,LOW);
    pump(true);
    valve(false);
  }
  else if(count%4==2)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(greenLED,HIGH);
    pump(false);
    valve(false);
  }
  else if(count%4==3)
  {
    digitalWrite(redLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(greenLED,LOW);
    pump(false);
    valve(true);
  }
}

//This function controls the outputs for the lcd display
void SoftRobot::lcdFunction(){
  //Count is used again to iterate and synchronize with the lights
  if(count%4==0){
    lcd.clear(); //Clears the screen from previous text
    lcd.setCursor(0,0); //Sets the location for the cursor to start (top left)
    lcd.print(runType[rT]); //Prints either "manual run" or "auto run" depending on run type
    lcd.setCursor(0,1); //Moves cursor to the bottom left
    lcd.print("Deflated"); //Prints text for what robot is doing
  }
  if(count%4==1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(runType[rT]);
    lcd.setCursor(0,1);
    lcd.print("Filling Chamber");
  }
  if(count%4==2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(runType[rT]);
    lcd.setCursor(0,1);
    lcd.print("Inflated");
  }
  if(count%4==3){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(runType[rT]);
    lcd.setCursor(0,1);
    lcd.print("Deflating");
  } 
}

//This is an auto run sequence triggered by the select on the Joystick
void SoftRobot::autoRun(){
  while(!done())
  {
    count++;
    lights();
    lcdFunction();
    if(count%4==0){ //Waits 5 seconds off
      delay(5000);
    }
    if(count%4==1){ //Fills for 8 seconds
      delay(8000);
    }
    if(count%4==2){ //Inflated for 5 sec
      delay(5000);
    }
    if(count%4==3){ //Empties for 5 sec
      delay(5000);
    }
  }
  //Prints that auto run has ended
  lcd.setCursor(0,1);
  lcd.print("Auto run ended");
}

bool SoftRobot::done(){
  if(digitalRead(JSPin) == LOW){
    lcd.clear(); //Clears screen and prints stopping
    lcd.setCursor(0,0);
    lcd.print("Stopping auto run");
    delay(1000); //Waits 1 second
    return true; //Returns true, stoppin auto run
  }
 else //Otherwise continue the loop
   return false;
}

void SoftRobot::manualRun(){
  //Checks if joystick pushed to left or right
  if(analogRead(horizontal) > 360)
  {
    //If pushed to the right, adds to the count, cycling forward
    count++;
    lcdFunction();
    delay (300);
  }
  else if(analogRead(horizontal) < 300)
  {
    //Left cycles it backwards
    count--;
    lcdFunction();
    delay (300);
  }
  lights();
}

bool SoftRobot::mRun(){
  if(digitalRead(JSPin)==LOW){
    rT = false;
    return false;
  }
  else{
    rT = true;
    return true;
  }
}

