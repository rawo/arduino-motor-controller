#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <RobotController.h>


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

RobotController robot(1,2);  

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
    Serial.print("current speed:");
    Serial.println(robot.getCurrentSpeed());
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
}

void setup() {
  
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  Serial.begin(9600);
  serialToBluetooth.begin(9600);
  
//  robot.test();
}

void loop() {
 
  int intCmd = receiveCommandFromSerial(serialToBluetooth);
  
  handleCommand(intCmd);
  
  delay(25);
    
}
