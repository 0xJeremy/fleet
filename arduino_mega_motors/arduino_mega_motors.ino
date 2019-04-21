#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

//Define Pins
#define EncoderPinA 2   // Encoder Pin A pin 2 and pin 3 are inturrpt pins
#define EncoderPinB 3   // Encoder Pin B

//Initialize Variables
long counts = 0; //counts the encoder counts.

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts+1;
  }
}

void stopIfFault()
{
  if (md.getM1Fault())
  {
    Serial.println("M1 fault");
    while(1);
  }
  if (md.getM2Fault())
  {
    Serial.println("M2 fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual VNH5019 Motor Shield");
  md.init();
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, LOW); //initialize Pin States
  digitalWrite(EncoderPinB, LOW);
  attachInterrupt(0, readEncoder, CHANGE); //attach interrupt to PIN 2 
}

void loop()
{
//    md.setM1Speed(100);
//    delay(20);
//    Serial.println(counts);
  for (int i = 0; i <= 400; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    delay(2);
    //Serial.println(counts);
  }
  
  for (int i = 400; i >= -400; i--)
  {
    md.setM1Speed(i);
    stopIfFault();
    delay(2);
    //Serial.println(counts);
  }
  
  for (int i = -400; i <= 0; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    delay(2);
    //Serial.println(counts);
  }

  for (int i = 0; i <= 400; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    delay(2);
  }
  
  for (int i = 400; i >= -400; i--)
  {
    md.setM2Speed(i);
    stopIfFault();
    delay(2);
  }
  
  for (int i = -400; i <= 0; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    delay(2);
  }
}
