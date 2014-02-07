#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <RobotController.h>
#include <MyTest.h>


const int CMD_FORWARD = 70; //F
const int CMD_BACKWARD = 66; //B
const int CMD_TURN_LEFT = 76; //L
const int CMD_TURN_RIGHT = 82;//R
const int CMD_STOP = 83; //S
const int CMD_TEST_LEFT = 48; //0
const int CMD_TEST_RIGHT = 49; //1
const int RX =15;
const int TX =14;
int inc = 0;

SoftwareSerial serialToBluetooth(RX, TX); // RX, TX

AF_DCMotor leftMotor(1);
AF_DCMotor rightMotor(2);
RobotController robot(&leftMotor,&rightMotor);

int receiveCommandFromSerial(SoftwareSerial& serial) {
  int c=0;
  if(serial.available()) {
    
    do {
      c = serial.read();
      
      if(c == '\r\n' 
      || c == -1 || c == 13 || c == 10) continue;

      
      Serial.print("I received: ");
      Serial.println(c);
      return c;
    }while(c != -1);
    
  }

  return c;
}

void handleCommand(int intCmd) {
  
  if (intCmd == CMD_FORWARD) {
    robot.driveForward();
  }
  
  if (intCmd == CMD_BACKWARD) {
    robot.driveBackward();
  }
  
  if (intCmd == CMD_TURN_LEFT) {
    robot.turnLeft();
  }
  
  if (intCmd == CMD_TURN_RIGHT) {
    robot.turnRight();
  }
  
  if (intCmd == CMD_STOP) {
    robot.stop();
  }  
  
  if (intCmd == CMD_TEST_LEFT) {
    leftMotor.run(FORWARD);
    leftMotor.setSpeed(255);
    delay(3000);
    leftMotor.setSpeed(0);
    leftMotor.run(RELEASE);
    delay(1000);
    leftMotor.setSpeed(255);
    leftMotor.run(BACKWARD);
    delay(3000);
    leftMotor.setSpeed(0);
    leftMotor.run(RELEASE);
  }
  
  if (intCmd == CMD_TEST_RIGHT) {
    rightMotor.run(FORWARD);
    rightMotor.setSpeed(255);
    delay(3000);
    rightMotor.setSpeed(0);
    rightMotor.run(RELEASE);
    delay(1000);
    rightMotor.setSpeed(255);
    rightMotor.run(BACKWARD);
    delay(3000);
    rightMotor.setSpeed(0);
    rightMotor.run(RELEASE);
    
  }

}

void setup() {
  
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  Serial.begin(9600);
  serialToBluetooth.begin(9600);
  
}

void loop() {
 
  int intCmd = receiveCommandFromSerial(serialToBluetooth);
  
  handleCommand(intCmd);
  
  delay(25);
    
}
