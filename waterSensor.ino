// borrowed significantly from https://www.instructables.com/Christmas-Tree-Water-Level-Indicator/
// using this sensor: https://www.amazon.com/gp/product/B07THDH7Y4/

// assumes depth sensor is on analog pin 0 ("S" pin of the depth sensor)
const int depthSensorPin = A0; 
const int depthSensorLow  = 400;
const int depthSensorHigh = 800;
const int depthSensorMid  = (depthSensorLow + depthSensorHigh) / 2;
int depthSensorLastValue = 0;

const int pumpPin = 9;
const int pumpPinOn = HIGH;
const int pumpPinOff = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(pumpPin, OUTPUT);
}

void loop() {

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
  
  // this sets the frequency at which we sample
  // but only take a break if the pump is off
  if (depthValue > depthSensorMid)
    delay(10 * 1000); // 10 sec seems like long enough
  else 
    delay(250); // 0.25 sec while filling
}
