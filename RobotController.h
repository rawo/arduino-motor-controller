#ifndef ROBOT_CONTROLLER
#define ROBOT_CONTROLLER

#include <AFMotor.h>


class RobotController 
{
    private:
        AF_DCMotor* leftMotor;
        AF_DCMotor* rightMotor;


        uint8_t currentSpeed;
        uint8_t movement;

        const uint8_t motor_maxSpeed;
        const uint8_t motor_zeroSpeed;
        const uint8_t acceleration;
        const uint8_t acceleration_delay;

        const uint8_t DRIVING_BACKWARD;
        const uint8_t DRIVING_FORWARD;
        const uint8_t STOPPED;

      
    public:
        RobotController(AF_DCMotor* leftMotor, AF_DCMotor* rightMotor);
        RobotController();
        void turnLeft();
        void turnRight();
        void driveForward();
        void driveBackward();
        void stop();
        uint8_t getCurrentSpeed();

    private:
        uint8_t speedUp();
        uint8_t speedDown();
        void accelerate();
        void deaccelerate();
        void bothMotorsRunForward();
        void bothMotorsRelease();
        void bothMotorsRunBackward();
        void setMotorsToCurrentSpeed();

        bool drivingBackward();
        bool drivingForward();

};
#endif
