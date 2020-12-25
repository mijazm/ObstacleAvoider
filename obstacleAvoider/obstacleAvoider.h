/*
Library for Alfred Robot
Mijaz Mukundan
MIT Lisence
*/

#ifndef obstacleAvoider_h
#define obstacleAvoider_h

#include<Arduino.h>
class Rover
{
    public:
        Rover(int motor_left_forward, int motor_left_backward, int motor_right_forward, int motor_right_backward);
        void forward();
        void backward();
        void turn_left();
        void turn_right();
        void stop();
    private:
        int _motor_left_forward, _motor_left_backward, _motor_right_forward, _motor_right_backward;

};

class HCSR04
{
    public:
            HCSR04(uint8_t echo_pin, uint8_t trigger_pin, int temperatureC);
            float get_distance();
    private:
            uint8_t _trigger_pin, _echo_pin;
            long _duration;
            float _distance;
            int _temperatureC;
};
#endif