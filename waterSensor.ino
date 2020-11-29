// include the library code:
#include <LiquidCrystal.h>
#include <Arduino_HTS221.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  while (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
  }
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, John!");
}

void loop() {

  // Passing in FAHRENHEIT as the unit parameter to ENV.readTemperature(...),
  // allows you to read the sensor values in imperial units
  float temperature = HTS.readTemperature(FAHRENHEIT);
  float humidity    = HTS.readHumidity();

  String firstLine = "Temperature=";
  firstLine += int(round(temperature));
  firstLine += char(0xDF);
  firstLine += "F            ";
  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println("°F");

  String secondLine = "Humidity=";
  secondLine += int(round(humidity));
  secondLine += "%             ";
  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println("%");

  // print an empty line
  Serial.println();
  
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  
  lcd.setCursor(0, 1);
  lcd.print(secondLine);

  delay(2000);
}
