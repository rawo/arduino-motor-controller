#include "RobotController.h"
#include <AFMotor.h>
#include <stdint.h>
#include "Arduino.h"

RobotController::RobotController(AF_DCMotor* leftMotor, AF_DCMotor* rightMotor)
: motor_maxSpeed(255), 
    motor_zeroSpeed(0),
    acceleration(50), 
    acceleration_delay(50),
    DRIVING_BACKWARD(1),
    DRIVING_FORWARD(2),
    STOPPED(0)
{
    Serial.println("RobotController constructor()");
    this->leftMotor = leftMotor;
    this->rightMotor = rightMotor;

    this->currentSpeed = 0;
    this->movement = STOPPED;
}

void RobotController::turnLeft()
{
    leftMotor->setSpeed(100);
    rightMotor->setSpeed(currentSpeed);
}

void RobotController::turnRight()
{
    leftMotor->setSpeed(currentSpeed);
    rightMotor->setSpeed(100);
}

void RobotController::driveForward()
{
    if (drivingBackward()) // <--- Something is wrong with this statement
    {
        stop();
    }
    bothMotorsRunForward();
    speedUp();
    setMotorsToCurrentSpeed();
    //accelerate();
}
void RobotController::setMotorsToCurrentSpeed()
{
    leftMotor->setSpeed(currentSpeed);
    rightMotor->setSpeed(currentSpeed);
}

bool RobotController::drivingBackward()
{
    return movement == DRIVING_BACKWARD;

}

void RobotController::accelerate()
{
    while(speedUp()){
        delay(acceleration_delay);
        setMotorsToCurrentSpeed();
    }
}

void RobotController::bothMotorsRunBackward()
{
    movement = DRIVING_BACKWARD;
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
}

void RobotController::bothMotorsRunForward()
{
    movement = DRIVING_FORWARD;
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void RobotController::bothMotorsRelease()
{
    movement = STOPPED;
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
}


uint8_t RobotController::speedUp()
{
    if (currentSpeed == motor_maxSpeed) return 0;

    int temporarySpeed = currentSpeed;
    temporarySpeed = temporarySpeed + this->acceleration;
    if (temporarySpeed <= motor_maxSpeed) 
    {
        currentSpeed = temporarySpeed;
        return 1;
    }

    return 0;
}

uint8_t RobotController::speedDown()
{
    if (currentSpeed == motor_zeroSpeed) return 0;

    int temporarySpeed = currentSpeed;
    temporarySpeed = temporarySpeed - this->acceleration;
    if (temporarySpeed >= motor_zeroSpeed) 
    {
        currentSpeed = temporarySpeed;
        return 1;
    }

    return 0;
}


void RobotController::driveBackward()
{
    if (drivingForward()) 
    {
        this->stop();
    }
    bothMotorsRunBackward();
    accelerate();
}

bool RobotController::drivingForward() 
{
    return movement == DRIVING_FORWARD;
}

void RobotController::stop() 
{

    deaccelerate();
    bothMotorsRelease();
    currentSpeed = 0;
}

void RobotController::deaccelerate() 
{
    while(speedDown())
    {
        delay(acceleration_delay);
        setMotorsToCurrentSpeed();
    }

}
uint8_t RobotController::getCurrentSpeed() 
{
    return currentSpeed;
}
