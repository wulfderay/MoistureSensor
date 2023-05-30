#include "DHT.h"

#define DHTPIN 8 // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // DHT11 sensor type
const int MOISTURE_PIN = 0;
const int RED_PIN = 11;
const int GREEN_PIN = 12;
const int BLUE_PIN = 13;
int TOO_DRY = 250; //set low parameter for plant
int TOO_WET = 550; //set high parameter for plant
const float SCALE = 0.008985 * 0.7;
const float OFFSET = 0.207762;
const float E_SQUARED = 2.718282 * 2.718282;




DHT dht(DHTPIN, DHTTYPE);

void printJsonStatus(int moistureValue, int moisturePercentage, const char* moistureStatus, float humidity, float temperature);
const char* updateMoistureLED(int moistureValue);
void parseSerialCommand();
void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  int moistureValue = analogRead(MOISTURE_PIN);
  int moisturePercentage = E_SQUARED * (SCALE * moistureValue + OFFSET);
  const char* moistureStatus = updateMoistureLED(moistureValue);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    printJsonStatus(moistureValue, moisturePercentage, "Failed to read from DHT sensor!", -1, -999);
  } else {
    printJsonStatus(moistureValue, moisturePercentage, moistureStatus, humidity, temperature);
  }
  if (Serial.available() > 0)
  {
    parseSerialCommand();
  }

  delay(1000);
}

void parseSerialCommand()
{
  String commandString = Serial.readString(); 
  
  if (commandString.startsWith("set_min "))
  {
    TOO_DRY = commandString.substring(commandString.indexOf(" ")+1).toInt();
    return;
  }
  if (commandString.startsWith("set_max "))
  {
    TOO_WET = commandString.substring(commandString.indexOf(" ")+1).toInt();
    return;
  }
  
  // otherwise, unknown command. ignore.
  Serial.print("Command not understood");
}

const char* updateMoistureLED(int moistureValue) {
  const char* moistureStatus;
  
  if (moistureValue <= TOO_DRY) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    moistureStatus = "Too Dry";
  } else if (moistureValue >= TOO_WET) {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    moistureStatus = "Too Wet";
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    moistureStatus = "Just Right";
  }

  return moistureStatus;
}

void printJsonStatus(int moistureValue, int moisturePercentage, const char* statusMessage, float humidity, float temperature) {
  char jsonBuffer[256];
  char humidityStr[8];
  char temperatureStr[8];

  dtostrf(humidity, 5, 2, humidityStr);
  dtostrf(temperature, 5, 2, temperatureStr);

  snprintf(jsonBuffer, sizeof(jsonBuffer),
           "{\"moistureValue\": %d, \"moisturePercentage\": %d, \"statusMessage\": \"%s\", \"humidity\": %s, \"temperature\": %s, \"minValue\": %d, \"maxValue\": %d }\n",
           moistureValue, moisturePercentage, statusMessage, humidityStr, temperatureStr, TOO_DRY, TOO_WET);

  Serial.print(jsonBuffer);
}
