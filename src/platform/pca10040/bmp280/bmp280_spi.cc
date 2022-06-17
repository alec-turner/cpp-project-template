/**
 * @file bmp280_spi.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Implementation of the Bmp280Spi class.
 */
#include "nrf_delay.h"
#include "nrf_log.h"
#include "platform/pca10040/bmp280/bmp280_spi.h"


/**
 * @brief Construct a new BMP280 Spi:: BMP280 Spi object
 */
pca10040::Bmp280Spi::Bmp280Spi() {

}


/**
 * @brief Destroy the BMP280 Spi:: BMP280 Spi object
 */
pca10040::Bmp280Spi::~Bmp280Spi() {
  
}


/**
 * @brief Initialise the BMP280.
 *
 * @return true if successful, false otherwise.
 */
bool pca10040::Bmp280Spi::init() {
  int8_t result = BMP2_OK;

  // configure SPI
  _spi_driver.init();

  // configure BMP280
  // set interface pointer to allow static functions to access class instance
  _bmp.intf_ptr = this;
  _bmp.intf = BMP2_SPI_INTF;
  _bmp.read = read;
  _bmp.write = write;
  _bmp.delay_us = delay;

  result = bmp2_init(&_bmp);
  if (result != BMP2_OK){
    NRF_LOG_INFO("BMP280 SPI init failed");
    return false;
  }

  return true;
}


/**
 * @brief Deinitialise the BMP280.
 */
void pca10040::Bmp280Spi::deinit() {
  _spi_driver.deinit();

}


/**
 * @brief Read data from the BMP280.
 *
 * @param reg The register address to read from.
 * @param data The data buffer to store the read data.
 * @param length The number of bytes to read.
 * @param intf_ptr Pointer to the Bmp280Spi class instance.
 * @return BMP2 return code.
 */
int8_t pca10040::Bmp280Spi::read(uint8_t reg, uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Spi * instance = (Bmp280Spi *)intf_ptr;

  instance->_spi_driver.read(reg, data, length);

  return BMP2_INTF_RET_SUCCESS;
}


/**
 * @brief Write data to the BMP280.
 *
 * @param reg The register address to write to.
 * @param data The data buffer to write.
 * @param length The number of bytes to write.
 * @param intf_ptr Pointer to the Bmp280Spi class instance.
 * @return BMP2 return code.
 */
int8_t pca10040::Bmp280Spi::write(uint8_t reg, const uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Spi * instance = (Bmp280Spi *)intf_ptr;

  instance->_spi_driver.write(reg, (uint8_t *)data, length);
  
  return BMP2_INTF_RET_SUCCESS;
}


/**
 * @brief Delay for the specified number of microseconds.
 *
 * @param us The number of microseconds to delay.
 * @param intf_ptr Pointer to the Bmp280Spi class instance.
 */
void pca10040::Bmp280Spi::delay(uint32_t duration, void * intf_ptr){
  (void) intf_ptr;
  // Note: ms delays are better implemented in nRF5 SDK; BMP delays are ms increments anyway
  nrf_delay_ms(duration / 1000);
}