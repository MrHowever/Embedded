#include "RainDetector.hh"
#include <math.h>

RainDetector::RainDetector(Adc& adc, uint8_t channel) : _adc(adc), _channel(channel)
{
  _maxVoltage = eeprom_read_float(&MAX_OUT_VOLTAGE);
  _minVoltage = eeprom_read_float(&MIN_OUT_VOLTAGE);
  _threshold  = eeprom_read_byte(&RAIN_THRESHOLD);
}

uint8_t RainDetector::rainIntensity()
{
  float rainIntensity = Adc::toVolts(_adc.getValue(_channel));
  float scaledIntensity = rainIntensity - _maxVoltage;
  return (uint8_t) round(100.0 - ((scaledIntensity / _minVoltage) * 100.0));
}

bool RainDetector::isRaining()
{
    return rainIntensity() > _threshold;
}

void RainDetector::calibrate(RainDetectorControl instruction, uint32_t value)
{
  switch(instruction)
  {
    case MAX_VAL:
      eeprom_update_float(&MAX_OUT_VOLTAGE, value);
      _maxVoltage = value;
      break;

    case MIN_VAL:
      eeprom_update_float(&MIN_OUT_VOLTAGE, value);
      _minVoltage = value;
      break;

    case THRESHOLD:
      eeprom_update_byte(&RAIN_THRESHOLD, value);
      _threshold = value;
      break;

    case CHANNEL:
      _channel = value;
      break;
      
    default:
      return;
  }
}
