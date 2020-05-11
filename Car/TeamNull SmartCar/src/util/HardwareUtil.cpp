#include "HardwareUtil.hpp"
#include <Smartcar.h>

unsigned long BLINK_INTERVAL = 200;

VL53L0X frontSensor;
// VL53L0X rearSensor;

const int frontSensorPin = 33;
const int rearSensorPin = 32;

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

SimpleCar car(control);

void setSpeed(int speed) {
  car.setSpeed(speed);
}

void setAngle(int angle) {
  car.setAngle(angle);
}

void blink(int toBlink){
  boolean builtinLEDState = false;
  unsigned long previousToggle = 0;
  int blinkCount = 0;

  while((blinkCount/2) < toBlink) {
    unsigned long currentTime = millis();
    if(currentTime > previousToggle + BLINK_INTERVAL) {
      builtinLEDState = !builtinLEDState;
      digitalWrite(LED_BUILTIN, builtinLEDState);
      previousToggle = currentTime;
      ++blinkCount;
    }
  }
  digitalWrite(LED_BUILTIN, false);
  builtinLEDState = false;
}

void blink(int toBlink, unsigned long blinkDuration) {
    BLINK_INTERVAL = blinkDuration;
    blink(toBlink);
}

void initialiseSensors() {

  // GY50 gyro(0); // Provide the gyroscope with a random offset
  // Serial.println("Calibrating gyroscope, this might take some seconds");
  // int offset = gyro.getOffset();
  // Serial.print("This gyro's offset value is: ");
  // Serial.println(offset);
  // Serial.print("Please initialize Gyroscope with the above value as: GY50 gyro(");
  // Serial.print(offset);
  // Serial.println("); or another similar value that works better according to your experimentation.");
  GY50 gyro(12);

  // pinMode(rearSensorPin, OUTPUT);
  // pinMode(frontSensorPin, OUTPUT);
  // digitalWrite(rearSensorPin, LOW);
  // digitalWrite(frontSensorPin, LOW);

  // delay(1000);

  // //Set front sensor address
  // // digitalWrite(frontSensorPin, HIGH);
  // pinMode(frontSensorPin, INPUT);
  // delay(150);
  // Serial.println("00");
  frontSensor.setTimeout(500);
  while (!frontSensor.init()) {
    Serial.println("Failed to initialise FRONT sensor");
    blink(2);
    // car.set
    // pinMode(frontSensorPin, OUTPUT);
    // digitalWrite(frontSensorPin, LOW);

    // delay(1500);
    // pinMode(frontSensorPin, INPUT);
  }

  delay(100);
  // frontSensor.setAddress((uint8_t)01);

  //Set rear sensor address
  // Serial.println("01");
  // digitalWrite(rearSensorPin, HIGH);
  pinMode(rearSensorPin, INPUT);
  delay(150);
  // rearSensor.setTimeout(500);
  // // rearSensor.setAddress((uint8_t)01);
  // while (!rearSensor.init()) {
  //   Serial.println("Failed to initialise REAR sensor");
  //   blink(2);
  //   pinMode(frontSensorPin, OUTPUT);
  //   digitalWrite(frontSensorPin, LOW);

  //   delay(1500);
  //   pinMode(frontSensorPin, INPUT);
  // }
  // rearSensor.setAddress((uint8_t)02);

  frontSensor.startContinuous();
  Serial.print("Front distance: ");
  Serial.println(frontSensor.readRangeContinuousMillimeters());

  // rearSensor.startContinuous();
  // Serial.print("Rear distance: ");
  // Serial.println(rearSensor.readRangeContinuousMillimeters());
}

int getFrontDistance() {
  return frontSensor.readRangeContinuousMillimeters();
  if(frontSensor.timeoutOccurred()) {
    Serial.println("FrontSensor TIMEOUT");
  }
  // return 10;
}

int getLeftFrontDistance() {
  return 100;
}

int getRightFrontDistance() {
  return 100;
}

int getRearDistance() {
  return 300;
}