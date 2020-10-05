//
// Created by mrhowever on 06.04.2020.
//

#include <math.h>
#include "SoilHumiditySensor.hh"

SoilMoistureSensor::SoilMoistureSensor(Adc& adc, uint8_t channel) : _adc(adc), _channel(channel)
{
  _moistureScale = eeprom_read_float(&MOISTURE_SCALE_VALUE);
  _dryThreshold = eeprom_read_word(&DRY_THRESHOLD_VALUE);
  _humidThreshold = eeprom_read_word(&HUMID_THRESHOLD_VALUE);
}

uint16_t SoilMoistureSensor::soilMoisture()
{
    double soilMoisture = Adc::toVolts(_adc.getValue(_channel));
    double scaledMoisture = soilMoisture * _moistureScale;
    return (uint16_t) round(scaledMoisture);
}

uint8_t SoilMoistureSensor::isMoist()
{
  double moisture = soilMoisture();
  
  if(moisture < _dryThreshold) {
    return 0;           // Dry soil
  }
  else if(moisture < _humidThreshold) {
    return 1;           // Humid soil
  }
  else {
    return 2;           // Water
  }
}

void SoilMoistureSensor::calibrate(MoistureSensorControl type, uint32_t value)
{
  switch(type)
  {
    case DRY_THRESHOLD:
      eeprom_update_word(&DRY_THRESHOLD_VALUE, value);
      _dryThreshold = value;
      break;

    case HUMID_THRESHOLD:
      eeprom_update_word(&HUMID_THRESHOLD_VALUE, value);
      _humidThreshold = value;
      break;

    case MOISTURE_SCALE:
      eeprom_update_float(&MOISTURE_SCALE_VALUE, value);
      _moistureScale = value;

    default:
      return;
  }
}
