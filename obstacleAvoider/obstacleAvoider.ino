#include <Arduino.h>
#include <Servo.h>
#include "obstacleAvoider.h"

Servo eyeServo; //Define a servo object, we will use this servo to sweep the surroundings
                //It is equivalent to making the robot look left and right to get the distance
                //from HCSR04 ultrasonic sensor mounted on it.
int pos = 90; //position angle for servo

//define trigger pin and echo pin for HCSR04
uint8_t trigger_pin = 11;
uint8_t echo_pin = 12;
int temperature = 26; //Temperature in Celcius

//Define an HCSR04 object
HCSR04 ultrasoundEye(echo_pin,trigger_pin,temperature);

//define variables and objects for rover
int lf = 5, lb=7; //Left forward and Left backward
int rf=9, rb=10; //right forward and right backward

Rover rover(lf,lb,rf,rb);

float dist_right = 0;
float dist_left = 0; 


void setup() {
  // Let us define a control pin for servo, choose any PWM pin you like
  eyeServo.attach(3); //Here I chose 3
  eyeServo.write(pos); //Let the eye face forward
  Serial.begin(9600);
}

void loop() {
    //move forward
    rover.forward();
    
     if(ultrasoundEye.get_distance() <= 5){
       
       //Stop! Obstacle ahead
       rover.stop();
       Serial.println("Stopped!");
       delay(100);

       //Back up a bit
       rover.backward();
       Serial.println("Going back");
       delay(1000);
       rover.stop();
     
       //Look from zero to 180 degrees with some delay between each step, this will
      //create an illusion of a smooth sweep
      for (pos=90;pos<=180;pos++){
        eyeServo.write(pos);
        delay(15);
      }
      delay(1000);
      dist_left = ultrasoundEye.get_distance();
      
     Serial.print("Left Distance:");
     Serial.println(dist_left);


      
      //Here we will make the servo look left
      for (pos=180;pos>=0;pos--){
        eyeServo.write(pos);
        delay(15);
      }
     
     delay(1000);
     
     dist_right = ultrasoundEye.get_distance();

     Serial.print("Right Distance:");
     Serial.println(dist_right);

     
     //Look ahead
     for (pos=0;pos<=90;pos++){
        eyeServo.write(pos);
        delay(15);
      }
     
     if(dist_right > dist_left){
       Serial.println("Going Right!");
       rover.turn_right();
       delay(1000);
       rover.stop();
     }
     else{
       Serial.println("Going Left!");
       rover.turn_left();
       delay(1000);
       rover.stop();
     }
      
  }
 
}