/*
Library for Alfred Robot
Mijaz Mukundan
MIT Lisence
*/

#include<Arduino.h>
#include "obstacleAvoider.h"

Rover::Rover(int motor_left_forward, int motor_left_backward, int motor_right_forward, int motor_right_backward){
    pinMode(motor_left_forward,OUTPUT);
    pinMode(motor_left_backward,OUTPUT);
    pinMode(motor_right_backward,OUTPUT);
    pinMode(motor_right_forward,OUTPUT);

    _motor_left_backward=motor_left_backward;
    _motor_left_forward=motor_left_forward;
    _motor_right_backward=motor_right_backward;
    _motor_right_forward=motor_right_forward;
}

void Rover::stop(){
    digitalWrite(_motor_left_forward,LOW);
    digitalWrite(_motor_right_forward,LOW);

    digitalWrite(_motor_left_backward,LOW);
    digitalWrite(_motor_right_backward,LOW);
}

void Rover::forward(){
    digitalWrite(_motor_left_forward,HIGH);
    digitalWrite(_motor_right_forward,HIGH);

    digitalWrite(_motor_left_backward,LOW);
    digitalWrite(_motor_right_backward,LOW);
}

void Rover::backward(){
    digitalWrite(_motor_left_forward,LOW);
    digitalWrite(_motor_right_forward,LOW);

    digitalWrite(_motor_left_backward,HIGH);
    digitalWrite(_motor_right_backward,HIGH);
}

void Rover::turn_left(){
    digitalWrite(_motor_left_forward,LOW);
    digitalWrite(_motor_right_forward,HIGH);

    digitalWrite(_motor_left_backward,HIGH);
    digitalWrite(_motor_right_backward,LOW);
}

void Rover::turn_right(){
    digitalWrite(_motor_left_forward,HIGH);
    digitalWrite(_motor_right_forward,LOW);

    digitalWrite(_motor_left_backward,LOW);
    digitalWrite(_motor_right_backward,HIGH);
}

//###########################################################################################################################


HCSR04::HCSR04(uint8_t echo_pin, uint8_t trigger_pin, int temperatureC){
    
    _echo_pin = echo_pin;
    _trigger_pin = trigger_pin;
    _temperatureC = temperatureC;

    pinMode(_trigger_pin, OUTPUT); //setting trigger pin as output, a pulse of 10us to trigger 
                                   //will cause ultrasonic sensor to send an 8 cycle 
                                   //burst of ultrasound
    pinMode(_echo_pin, INPUT); //We will read the echo pin to get the time of flight and use this
                               //later to calculate the distance
}
float HCSR04::get_distance(){
    /*
    Refer to the excellent articles at 
    https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
    or
    https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
    for more information on this code
    */

    //keep the trigger pin low at start to prevent miss fire
    digitalWrite(_trigger_pin, LOW);
    delay(2);

    //We will keep the trigger pin HIGH for 10us for HCSR04 to emitt the ultrasound
    digitalWrite(_trigger_pin,HIGH);
    delay(10);
    digitalWrite(_trigger_pin, LOW);
    
    //Let us find the time of flight by observing when the echo pin goes from HIGH to LOW
    _duration = pulseIn(_echo_pin,HIGH);

    //Let us now use the duration and calculate the distance
    // the formula would be Distance = Speed of sound x Duration / 2 
    // the division by two is used because the soundwave travels twice the distance 
    //between sensor and obstacle
    //Speed of sound = 340 m/s = 0.000340 m/us = 0.034 cm/us
    float speed_of_sound = 331 + 0.6 * _temperatureC; // in m/s
    _distance =  _duration / 2 * speed_of_sound / 10000;

    return _distance;
}