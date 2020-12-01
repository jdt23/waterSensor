// include the library code:
#include <LiquidCrystal.h>
// include the humidity and temperature sensor library
#include <Arduino_HTS221.h>

// borrowed significantly from https://www.instructables.com/Christmas-Tree-Water-Level-Indicator/
// using this sensor: https://www.amazon.com/gp/product/B07THDH7Y4/

// assumes depth sensor is on analog pin 0 ("S" pin of the sensor)
const int depthSensorPin = A0; 
const int depthSensorLow  = 400;
const int depthSensorHigh = 800;
const int depthSensorMid  = (depthSensorLow + depthSensorHigh) / 2;
int depthSensorLastValue = 0;

const int pumpPin = D9;
const int pumpPinOn = 1;
const int pumpPinOff = 0;


// setLED inverts the LED request, so 1 == "on"
void setLED (int r, int g, int b) {
  digitalWrite(LEDR, 1-r);
  digitalWrite(LEDG, 1-g);
  digitalWrite(LEDB, 1-b);
}

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  while (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
  }

  pinMode(pumpPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {

  // read the depth sensor
  int depthValue = analogRead(depthSensorPin);
  depthSensorLastValue = depthValue;
  int depthValuePercent = map (depthValue, depthSensorLow, depthSensorHigh, 0, 100);

  // Passing in FAHRENHEIT as the unit parameter to ENV.readTemperature(...),
  // allows you to read the sensor values in imperial units
  float temperature = HTS.readTemperature(FAHRENHEIT);
  float humidity    = HTS.readHumidity();

  // print the temperature to lcd line 0 and serial
  String firstLine = "T=";
  firstLine += int(round(temperature));
  firstLine += char(0xDF);
  firstLine += "F,";
  Serial.print("Temp=");
  Serial.print(temperature);
  Serial.print("°F");

  // print the humidity to lcd line 0 and serial
  firstLine += " H=";
  firstLine += int(round(humidity));
  firstLine += "%             ";
  Serial.print(" Humi=");
  Serial.print(humidity);
  Serial.println("%");

  // print the water depth to lcd line 1 and serial
  String secondLine = "Depth=";
  secondLine += depthValue;
  secondLine += " (";
  secondLine += depthValuePercent;
  secondLine += "%)              ";
  Serial.print("Depth=");
  Serial.print(depthValue);
  Serial.print(" (");
  Serial.print(depthValuePercent);
  Serial.print("%)");

  // print the lines to the lcd
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  
  lcd.setCursor(0, 1);
  lcd.print(secondLine);

  // turn the pump on if it's less than 50% full, otherwise leave off
  if (depthValue < depthSensorMid) {
    digitalWrite(pumpPin, pumpPinOn);
  } else {
    digitalWrite(pumpPin, pumpPinOff);
  }
  
  //set LED depending on value
  if (depthValue > depthSensorHigh) {
    setLED (1,0,0); // red means overfilling!
  } else if (depthValue > depthSensorMid)  {
    setLED (0,1,0); // green means a good level
  } else if (depthValue > depthSensorLow) { 
    setLED (1,1,0); // yellow means low but should be filling
  } else { 
    setLED (0,0,1); // blue means very low and should be filling
  }
  
  // this sets the frequency at which we sample
  // but only take a break if the pump is off
  if (depthValue > depthSensorMid)
    delay(1 * 1000); // 10 sec seems like long enough
  else 
    delay(250); // 0.25 sec while filling
}
