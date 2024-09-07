#include <Wire.h>

#define AM2301B_I2C_ADDRESS 0x38  // I2C address of the sensor
#define MEASUREMENT_DELAY 2000    // Delay between measurements
#define MEASUREMENT_COMMAND 0xAC  // Command to initiate measurement

const int soilSensorPin = 34;  // GPIO pin for the soil moisture sensor (analog)

void setup() {
  // Initialize I2C for AM2301B sensor with SDA on GPIO21 and SCL on GPIO22
  Wire.begin(21, 22);  
  Serial.begin(115200);

  // Initialize the soil moisture sensor pin as input
  pinMode(soilSensorPin, INPUT);

  Serial.println("Sensor Test: AM2301B and Soil Moisture");
}

void loop() {
  // Read temperature and humidity from the AM2301B sensor
  Serial.println("Requesting temperature and humidity measurement...");

  uint8_t error = requestMeasurement();
  
  if (error == 0) {
    delay(20);  // Wait for sensor to stabilize

    uint8_t data[7];
    error = readSensorData(data);

    if (error == 0) {
      // Print the raw data bytes
      Serial.print("Raw data: ");
      for (int i = 0; i < 7; i++) {
        Serial.print(data[i], HEX);  // Print each byte in hexadecimal format
        Serial.print(" ");
      }
      Serial.println();

      uint16_t rawHumidity = (data[1] << 8) | data[2];  // Combine bytes for humidity
      uint16_t rawTemperature = (data[3] << 8) | data[4];  // Combine bytes for temperature

      // Convert and print the human-readable values
      float temperature = convertTemperature(rawTemperature);
      float humidity = convertHumidity(rawHumidity);

      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    } else {
      Serial.println("Failed to read data from AM2301B sensor!");
    }
  } else {
    Serial.println("Failed to request measurement from AM2301B sensor!");
  }

  // Read the soil moisture sensor value
  int soilMoistureValue = analogRead(soilSensorPin);
  
  // Print the analog value (range from 0 to 4095 on ESP32)
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);
  
  // Interpret the moisture level
  if (soilMoistureValue > 3000) {
    Serial.println("Dry Soil");
  } else if (soilMoistureValue > 1500) {
    Serial.println("Moist Soil");
  } else {
    Serial.println("Wet Soil");
  }

  // Wait for the next measurement cycle
  delay(MEASUREMENT_DELAY);
}

// Request measurement from the AM2301B sensor
uint8_t requestMeasurement() {
  Wire.beginTransmission(AM2301B_I2C_ADDRESS);
  Wire.write(MEASUREMENT_COMMAND);  // Send measurement command
  
  if (Wire.endTransmission() != 0) {
    return 1;  // Error
  }
  
  return 0;  // Success
}

// Read data from the AM2301B sensor
uint8_t readSensorData(uint8_t *data) {
  Wire.requestFrom(AM2301B_I2C_ADDRESS, 7);  // Request 7 bytes of data from sensor
  
  if (Wire.available() == 7) {
    for (int i = 0; i < 7; i++) {
      data[i] = Wire.read();
    }
    return 0;  // Success
  } else {
    return 1;  // Error: insufficient data
  }
}

// Convert raw humidity to percentage
float convertHumidity(uint16_t rawHumidity) {
  return ((float)rawHumidity / 65536.0) * 100.0;  // Convert to percentage
}

// Convert raw temperature to °C (-40°C to 80°C range)
float convertTemperature(uint16_t rawTemperature) {
  // Temperature calculation for the range -40°C to 80°C
  float temperature = ((float)rawTemperature / 65536.0) * 120.0 - 40.0;  // Scale to -40 to 80°C
  
  // Ensure the temperature value is within the expected range
  if (temperature < -40.0) {
    temperature = -40.0;
  } else if (temperature > 80.0) {
    temperature = 80.0;
  }
  
  return temperature;
}
