#include <LiquidCrystal.h>
#include "Soft_Robot.h"

SoftRobot robotOne;

void setup() {
  robotOne.initialize();
}

void loop() {
  if(robotOne.mRun()){
    robotOne.manualRun();
  }
  else{
    robotOne.autoRun();
  }
}
