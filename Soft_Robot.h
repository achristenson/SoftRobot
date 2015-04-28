//
//  Soft_Robot.h
//  Arduino
//
//  Created by Alex Christenson on 4/21/15.
//  Copyright (c) 2015 Alex Christenson. All rights reserved.
//

#ifndef __Arduino__Soft_Robot__
#define __Arduino__Soft_Robot__

#include "Arduino.h"
#include <LiquidCrystal.h>

class SoftRobot{
  public:
    //This is the list of the functions used
    SoftRobot(); //Constructor for the robot
    ~SoftRobot();//Destructor
    void initialize();//Initialize function (declares variables)
    void pump(bool turnOn);//Turns the pump on or off
    void valve(bool turnOn);//Turns the valve on or off
    void lights();//Runs the lights and pump/valve
    void lcdFunction();//Runs the lcd
    void autoRun();//Function for the autorun sequence
    void manualRun();//Function for the manualrun sequence
    bool done();//Tells the autorun sequence whether or not the continue
    bool mRun();
    
    //This section of the code delares the variables
    //Joystick
    //Analog A0 and A1 associate a movement with a number
    //A0 for vertical movement - rests at appx. 311, up at 1, down at 500
    int vertical;
    //A1 for horizontal movement 1 for left, 600 for right
    int horizontal;
    //Digital tell whether button pressed or not - reads LOW when pressed, HIGH if not
    int JSPin;
    
    //Pump and the Valve
    //Digital pins 9 and 10 for the solenoid valve and pump
    int pumpPin;
    int valvePin;
    
    //The LEDs
    //Green
    int greenLED;
    //Yellow
    int yellowLED;
    //Red
    int redLED;
    
    //This section documents the rest of the variables used
    //Counter to iterate through the actions of the robot - 0 Deflated, 1 Inflating, 2 Inflated, 3 Deflating
    int count;
    
    //Tells whether or not the robot should be running automatically or manually
    bool rT;
    
    //Switches between manual and automatic depending on boolean(0 or 1)
    String runType[2];
};


#endif /* defined(__Arduino__Soft_Robot__) */
