/**
 * @file bmp280_spi.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "nrf_delay.h"
#include "platform/pca10040/bmp280/bmp280_spi.h"

pca10040::Bmp280Spi::Bmp280Spi() {

}


pca10040::Bmp280Spi::~Bmp280Spi() {
  
}


bool pca10040::Bmp280Spi::init() {
  int8_t result = BMP2_OK;

  // configure SPI
  _spi_driver.init();

  // while (1){

  //   _spi_driver.read(0xD0, &test, 1);
  //   nrf_delay_ms(100);
  // }



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


void pca10040::Bmp280Spi::deinit() {
  _spi_driver.deinit();

}

int8_t pca10040::Bmp280Spi::read(uint8_t address, uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Spi * instance = (Bmp280Spi *)intf_ptr;

  instance->_spi_driver.read(address, data, length);

  return BMP2_INTF_RET_SUCCESS;
}


int8_t pca10040::Bmp280Spi::write(uint8_t address, const uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Spi * instance = (Bmp280Spi *)intf_ptr;

  instance->_spi_driver.write(address, (uint8_t *)data, length);
  
  return BMP2_INTF_RET_SUCCESS;
}


void pca10040::Bmp280Spi::delay(uint32_t duration, void * intf_ptr){
  nrf_delay_us(duration);
}