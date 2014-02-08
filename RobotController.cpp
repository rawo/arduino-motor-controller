#include "RobotController.h"
#include <AFMotor.h>
#include <stdint.h>
#include "Arduino.h"

RobotController::RobotController(AF_DCMotor* leftMotor, AF_DCMotor* rightMotor)
: motor_maxSpeed(100), 
    motor_zeroSpeed(0),
    acceleration(50), 
    acceleration_delay(250),
    STOPPED(0),
    DRIVING_BACKWARD(1),
    DRIVING_FORWARD(2),
    TURNING_LEFT(3),
    TURNING_RIGHT(4)
{
    this->leftMotor = leftMotor;
    this->rightMotor = rightMotor;

    this->currentSpeed = 0;
    this->movement = STOPPED;
}

void RobotController::turnLeft()
{
    if (isTurningLeft())
    {
        Serial.println("is turning left");
        return;
    }

    if(!isStopped())
    {
        Serial.println("not stopped. Stopping!");
        stop();
    }


    leftMotor->setSpeed(motor_maxSpeed);
    rightMotor->setSpeed(motor_maxSpeed);

    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);

    movement = TURNING_LEFT;

    Serial.println("Turning left");
}

bool RobotController::isStopped()
{
    return movement == STOPPED;
}

bool RobotController::isTurningLeft()
{
    return movement == TURNING_LEFT;
}

void RobotController::turnRight()
{
    if (isTurningRight())
    {
        return;
    }

    if(!isStopped())
    {
        stop();
    }

    leftMotor->setSpeed(motor_maxSpeed);
    rightMotor->setSpeed(motor_maxSpeed);

    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);

    movement = TURNING_RIGHT;

}

bool RobotController::isTurningRight()
{
    return movement == TURNING_RIGHT;
}

void RobotController::driveForward()
{
    if (isDrivingBackward()) 
    {
        stop();
    }
    speedUp();
    setMotorsToCurrentSpeed();
    bothMotorsRunForward();
}
void RobotController::setMotorsToCurrentSpeed()
{
    rightMotor->setSpeed(currentSpeed);
    leftMotor->setSpeed(currentSpeed);
}

bool RobotController::isDrivingBackward()
{
    return movement == DRIVING_BACKWARD;

}

void RobotController::bothMotorsRunBackward()
{
    if (movement != DRIVING_BACKWARD) 
    {
        movement = DRIVING_BACKWARD;
        rightMotor->run(BACKWARD);
        leftMotor->run(BACKWARD);
    }
}

void RobotController::bothMotorsRunForward()
{
    if ( movement != DRIVING_FORWARD) {
        movement = DRIVING_FORWARD;
        leftMotor->run(FORWARD);
        rightMotor->run(FORWARD);
    }
}

void RobotController::bothMotorsRelease()
{
    if (movement != STOPPED)
    {
        movement = STOPPED;
        rightMotor->run(RELEASE);
        leftMotor->run(RELEASE);
    }
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
    if (isDrivingForward()) 
    {
        this->stop();
    }
    speedUp();
    setMotorsToCurrentSpeed();
    bothMotorsRunBackward();
}

bool RobotController::isDrivingForward() 
{
    return movement == DRIVING_FORWARD;
}

void RobotController::stop() 
{

    deaccelerate();
    leftMotor->setSpeed(motor_zeroSpeed);
    rightMotor->setSpeed(motor_zeroSpeed);
    bothMotorsRelease();
    currentSpeed = 0;
    delay(500);
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

void RobotController::test() 
{
    delay(1000);
    leftMotor->setSpeed(100);
    rightMotor->setSpeed(100);
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    
    delay(5000);

    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);

    delay(2000);

    leftMotor->setSpeed(100);
    rightMotor->setSpeed(100);
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);

    delay(5000);

    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
}
