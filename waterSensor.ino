// borrowed significantly from https://www.instructables.com/Christmas-Tree-Water-Level-Indicator/
// using this sensor: https://www.amazon.com/gp/product/B07THDH7Y4/

// assumes depth sensor is on analog pin 0 ("S" pin of the depth sensor)
const int depthSensorPin = A0; 
const int depthSensorLow  = 400;
const int depthSensorHigh = 800;
const int depthSensorMid  = (depthSensorLow + depthSensorHigh) / 2;
int depthSensorLastValue = 0;

// tank pin depth sensor only turns device on if water level is between low and high
const int tankPin = A1;
const int tankThresholdLow = 500;
const int tankThresholdHigh = 750;
const int tankDelay = 2; // seconds

//
const int pumpPin = 9;
const int pumpPinOn = HIGH;
const int pumpPinOff = LOW;
const int pumpPinOffDelay = 2; // seconds
const int pumpPinOnDelay = 0.25; // 250ms

void setup() {
  Serial.begin(9600);

  pinMode(pumpPin, OUTPUT);
}

void loop() {

  // read the tank sensor. if it's too low or overflowing, do nothing
  int tankSensor = analogRead(tankPin);
  Serial.print("Tank=");
  Serial.print(tankSensor);
  Serial.print(", ");
  if ((tankSensor < tankThresholdLow) || (tankSensor > tankThresholdHigh)) {
    Serial.print(" turning off for ");
    Serial.print(tankDelay);
    Serial.println(" seconds");
    delay(tankDelay * 1000);
    return;
  }

  // tank sensor says we're ok at this point, so proceed with checking depth
  // read the depth sensor
  int depthValue = analogRead(depthSensorPin);
  depthSensorLastValue = depthValue;
  int depthValuePercent = map (depthValue, depthSensorLow, depthSensorHigh, 0, 100);
  Serial.print("Depth=");
  Serial.print(depthValue);
  Serial.print(" (");
  Serial.print(depthValuePercent);
  Serial.print("%)");

  // turn the pump on if it's less than 50% full, otherwise leave off
  if (depthValue < depthSensorMid) {
    digitalWrite(pumpPin, pumpPinOn);
    Serial.println(" Pump ON");
  } else {
    digitalWrite(pumpPin, pumpPinOff);
    Serial.println(" Pump OFF");
  }
  
  // how long to pause depends on if the pump is on or off
  if (depthValue > depthSensorMid)
    delay(pumpPinOffDelay * 1000); 
  else 
    delay(pumpPinOnDelay * 1000); 
}
