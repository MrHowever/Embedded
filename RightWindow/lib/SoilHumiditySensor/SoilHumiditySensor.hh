#ifndef RIGHTWINDOW_SOILHUMIDITYSENSOR_HH
#define RIGHTWINDOW_SOILHUMIDITYSENSOR_HH

#include <stdint.h>
#include <avr/eeprom.h>
#include <adc.hh>

static float MOISTURE_SCALE_VALUE EEMEM = 10000.0f;
static uint16_t DRY_THRESHOLD_VALUE EEMEM = 300;
static uint16_t HUMID_THRESHOLD_VALUE EEMEM = 700;

enum MoistureSensorControl : uint8_t { DRY_THRESHOLD = 0x00, HUMID_THRESHOLD = 0x01, MOISTURE_SCALE = 0x02};

class SoilMoistureSensor {
  Adc& _adc;
  uint8_t _channel;
  float _moistureScale;
  uint16_t _dryThreshold;
  uint16_t _humidThreshold;
public:
  SoilMoistureSensor(Adc&,uint8_t);
  uint16_t soilMoisture();
  uint8_t isMoist();
  void calibrate(MoistureSensorControl, uint32_t);
};


#endif //RIGHTWINDOW_SOILHUMIDITYSENSOR_HH
