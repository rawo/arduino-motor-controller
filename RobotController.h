#ifndef ROBOT_CONTROLLER
#define ROBOT_CONTROLLER

#include <AFMotor.h>


class RobotController 
{
    private:
        AF_DCMotor* leftMotor;
        AF_DCMotor* rightMotor;


        volatile uint8_t currentSpeed;
        volatile uint8_t movement;

        const uint8_t motor_maxSpeed;
        const uint8_t motor_zeroSpeed;
        const uint8_t acceleration;
        const uint8_t acceleration_delay;

        const uint8_t DRIVING_BACKWARD;
        const uint8_t DRIVING_FORWARD;
        const uint8_t STOPPED;

        const uint8_t TURNING_LEFT;
        const uint8_t TURNING_RIGHT;

      
    public:

        RobotController(AF_DCMotor* leftMotor, AF_DCMotor* rightMotor);

        void turnLeft();
        void turnRight();
        void driveForward();
        void driveBackward();
        void stop();

        uint8_t getCurrentSpeed();

        void test();

    private:
        uint8_t speedUp();
        uint8_t speedDown();

        void deaccelerate();
        
        void bothMotorsRunForward();
        void bothMotorsRelease();
        void bothMotorsRunBackward();

        void setMotorsToCurrentSpeed();

        bool isDrivingBackward();
        bool isDrivingForward();
        bool isTurningLeft();
        bool isTurningRight();
        bool isStopped();

};
#endif
