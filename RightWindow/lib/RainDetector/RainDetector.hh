#ifndef RIGHTWINDOW_RAINDETECTOR_HH
#define RIGHTWINDOW_RAINDETECTOR_HH

#include <stdint.h>
#include <avr/eeprom.h>
#include "adc.hh"

static float MAX_OUT_VOLTAGE EEMEM = 0.7f; // Voltage output at maximum (100%) rain intensity (or fully submerged in water)
static float MIN_OUT_VOLTAGE EEMEM = 3.25f; // Voltage output at minimum (0%) rain intensity or fully dry sensor
static uint8_t RAIN_THRESHOLD EEMEM = 10u; // Default percentage of rain intensity at which it is considered a "rain"

enum RainDetectorControl : uint8_t { MAX_VAL = 0x00, MIN_VAL = 0x01, THRESHOLD = 0x02, CHANNEL = 0x03};

class RainDetector {
  public:
  Adc& _adc;
  uint8_t _channel;
  uint8_t _threshold;
  float  _minVoltage;
  float _maxVoltage;

  RainDetector(Adc&,uint8_t);
  uint8_t rainIntensity();
  bool isRaining();
  void calibrate(RainDetectorControl, uint32_t);
};


#endif //RIGHTWINDOW_RAINDETECTOR_HH
