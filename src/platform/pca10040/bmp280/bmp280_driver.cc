/**
 * @file bmp280_driver.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Implementation of the Bmp280Driver class.
 */
#include "platform/pca10040/bmp280/bmp280_driver.h"


/**
 * @brief Construct a new BMP280 Driver:: BMP280 Driver object
 *
 * @param i2c_bus The I2C bus to use.
 * @param i2c_addr The I2C address of the BMP280.
 */
pca10040::Bmp280Driver::Bmp280Driver() {
  _config.os_mode = kDefaultOsMode;
  _config.filter = kDefaultFilter;
  _config.odr = kDefaultOdr;
  _power_mode = kDefaultPowerMode;
  _sampling_interval = 0;
}


/**
 * @brief Destroy the BMP280 Driver:: BMP280 Driver object
 *
 */
pca10040::Bmp280Driver::~Bmp280Driver() {

}


/**
 * @brief Configure the BMP280.
 *
 * @return true if successful, false otherwise.
 */
bool pca10040::Bmp280Driver::configure() {
  // apply settings
  int8_t result = bmp2_set_config(&_config, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 configuration failed");
    return false;
  }

  // get and update measurement interval time
  uint32_t meas_time;
  result = bmp2_compute_meas_time(&meas_time, &_config, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 measurement time calculation failed");
    _sampling_interval = 0;
    return false;
  }
  _sampling_interval = meas_time;

  return true;
}


/**
 * @brief Initialise the BMP280.
 *
 * @return true if successful, false otherwise.
 */
bool pca10040::Bmp280Driver::start() {
  int8_t result = bmp2_set_power_mode(_power_mode, &_config, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 start failed");
    return false;
  }

  return true;
}


/**
 * @brief Check if the BMP280 is ready to sample.
 *
 * @return true if ready, false otherwise.
 */
bool pca10040::Bmp280Driver::stop() {
  int8_t result = bmp2_set_power_mode(BMP2_POWERMODE_SLEEP, &_config, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 stop failed");
    return false;
  }

  return true;
}


/**
 * @brief Check if the BMP280 is ready to sample.
 *
 * @return true if ready, false otherwise.
 */
bool pca10040::Bmp280Driver::reset() {
  int8_t result = bmp2_soft_reset(&_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 reset failed");
    return false;
  }

  return true;
}


/**
 * @brief Read the BMP280's temperature.
 *
 * @return The temperature in degrees C.
 */
bool pca10040::Bmp280Driver::meas_ready() {
  bmp2_status status;
  int8_t result = bmp2_get_status(&status, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 status read failed");
    return false;
  }

  return status.measuring == BMP2_MEAS_DONE;
}


/**
 * @brief Read the BMP280's temperature.
 *
 * @return The temperature in degrees C.
 */
bool pca10040::Bmp280Driver::sample() {
  int8_t result = bmp2_get_sensor_data(&_data, &_bmp);
  if (result != BMP2_OK) {
    NRF_LOG_ERROR("BMP280 sample failed");
    return false;
  }

  return true;
}


/**
 * @brief Read the BMP280's temperature.
 *
 * @return The temperature in degrees C.
 */
float pca10040::Bmp280Driver::get_temperature() {
  return _data.temperature;
}


/**
 * @brief Read the BMP280's pressure.
 *
 * @return The pressure in Pa.
 */
float pca10040::Bmp280Driver::get_pressure() {
  return _data.pressure;
}


