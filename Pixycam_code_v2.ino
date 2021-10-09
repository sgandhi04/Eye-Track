#include <ArduinoRobotMotorBoard.h>
#include <EasyTransfer2.h>
#include <LineFollow.h>
#include <Multiplexer.h>

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PixyI2C.h>

#include "mBot.h"
#include "MePort.h"
MeBoard myBoard(mBot);
#include "MeDCMotor.h"

PixyI2C pixy;
int signature = 0;
int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;
unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;
int Xmax = 200;
int maxArea = 0;
int minArea = 0;
static int i = 0;

long startTime,stopTime;
long myDesiredTime;

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

void setup()
{
  {
  startTime = 0;
  stopTime = 0;
  myDesiredTime = 1500;
}
{ 
  Stop();
  pixy.init();
}
}

void loop()
{ 
  while(millis()<5000)
  {
    scan();
    area = width * height;
    maxArea = area + 1000;
    minArea = area - 1000;
  }

    scan(); 

  if(signature == 1 or signature == 2)
  {
    newarea = width * height;
    
      if (x < Xmin)
      {     
       left();
       stopTime = millis();
      }
      else if (x < Xmin)
      {
       left();
       return;
       stopTime = millis();
      }
      else if (x > Xmax)
      {
       right();
       stopTime = millis();
      }
      else if (x > Xmax)
      {
       right();
       return;
       stopTime = millis();
      }
      else if(newarea < minArea)
      {
       forward(); 
       stopTime = millis();
      }
      else if(newarea < minArea)
      {
        forward();
        return;
        stopTime = millis();
      }
      else if(newarea > maxArea)
      {
       backward(); 
       stopTime = millis();
      }
      else if(newarea > maxArea)
      {
        backward();
        return;
        stopTime = millis();
      }
      else
      {
        Stop(); 
      } 
   }
   else
   {
    Stop();
     }
}

void backward()
  {
  motor_9.run((9)==M1?-(-255):(-255));
  motor_10.run((10)==M1?-(-255):(-255));
  }

void forward()
  {
  motor_9.run((9)==M1?-(255):(255));
  motor_10.run((10)==M1?-(255):(255));
  }

void right()
  {
  motor_9.run((9)==M1?-(255):(255));
  motor_10.run((10)==M1?-(0):(0)); 
  }

void left()
  {
  motor_9.run((9)==M1?-(0):(0));
  motor_10.run((10)==M1?-(255):(255)); 
  }

void Stop()
  {
  motor_9.run((9)==M1?-(0):(0));
  motor_10.run((10)==M1?-(0):(0)); 
  }
  
void scan()
  {
  uint16_t blocks;
  blocks = pixy.getBlocks();
  signature = pixy.blocks[i].signature;
  x = pixy.blocks[i].x;
  y = pixy.blocks[i].y;
  width = pixy.blocks[i].width;
  height = pixy.blocks[i].height;
  }
