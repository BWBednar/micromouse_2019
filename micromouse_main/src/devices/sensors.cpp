/* sensors.cpp */


#include "sensors.h"
#include "../settings.h"

// Sensor object to communicate with all the the sensors
Adafruit_VL6180X vl6180x = Adafruit_VL6180X();

sensor_t sensors[NUM_SENSORS] = {
    {
        .address = 0x00, // dummy value
        .interruptPin = 1 // dummy value
    },
    {
        .address = 0x01, // dummy value
        .interruptPin = 2 // dummy value
    },
    {
        .address = 0x02, // dummy value
        .interruptPin = 3 // dummy value
    },
    {
        .address = 0x03, // dummy value
        .interruptPin = 4 // dummy value
    },
    {
        .address = 0x04, // dummy value
        .interruptPin = 5 // dummy value
    }
};

void tcaselect(uint8_t i) {
  if (i > 7) return;

  digitalWrite(I2C_RESET_PIN, LOW);
  delay(1);
  digitalWrite(I2C_RESET_PIN, HIGH);
  
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}


bool sensorSetup() {
  
  // Important, we need this for tcaselect to work!
  Wire.begin();

  for (int i = 0; i < NUM_SENSORS; i++){
    tcaselect(sensors[i].address);
    if (! vl6180x.begin()) {
      return false;
    }
  }

  // TODO register interrupts
  return true;
}

bool readSensors(sensor_t* sensor_data) {

  if (sensor_data == NULL) { return false; }

  for (int i = 0; i < NUM_SENSORS; ++i) {
    if (sensors[i].needsUpdated) {
      tcaselect(sensors[i].address);
      // TODO read the thing
      sensors[i].needsUpdated = 0;
    }
  }
  return true;
}
