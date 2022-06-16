/**
 * @file bmp280_twi.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "nrf_delay.h"
#include "nrf_log.h"
#include "platform/pca10040/bmp280/bmp280_twi.h"

pca10040::Bmp280Twi::Bmp280Twi() {

}


pca10040::Bmp280Twi::~Bmp280Twi() {
  
}


bool pca10040::Bmp280Twi::init() {
  int8_t result = BMP2_OK;

  // configure TWI
  _twi_driver.init();

  // configure BMP280
  // set interface pointer to allow static functions to access class instance
  _bmp.intf_ptr = this;
  _bmp.intf = BMP2_I2C_INTF;
  _bmp.read = read;
  _bmp.write = write;
  _bmp.delay_us = delay;

  result = bmp2_init(&_bmp);
  if (result != BMP2_OK){
    NRF_LOG_INFO("BMP280 TWI init failed");
    return false;
  }

  return true;
}


void pca10040::Bmp280Twi::deinit() {
  _twi_driver.deinit();

}

int8_t pca10040::Bmp280Twi::read(uint8_t address, uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Twi * instance = (Bmp280Twi *)intf_ptr;

  instance->_twi_driver.read_reg(kDeviceAddress, address, data, length);

  return BMP2_INTF_RET_SUCCESS;
}


int8_t pca10040::Bmp280Twi::write(uint8_t address, const uint8_t * data, uint32_t length, void * intf_ptr) {
  Bmp280Twi * instance = (Bmp280Twi *)intf_ptr;

  instance->_twi_driver.write_reg(kDeviceAddress, address, (uint8_t *) data, length);
  
  return BMP2_INTF_RET_SUCCESS;
}


void pca10040::Bmp280Twi::delay(uint32_t duration, void * intf_ptr){
  (void) intf_ptr;
  // Note: ms delays are better implemented in nRF5 SDK; BMP delays are ms increments anyway
  nrf_delay_ms(duration / 1000);
}