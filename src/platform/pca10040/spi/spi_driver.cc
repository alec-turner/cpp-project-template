/**
 * @file spi_driver.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "platform/pca10040/spi/spi_driver.h"


pca10040::SpiDriver::SpiDriver() {
  _initialized = false;
  _transfer_complete = false;

  switch (kSpiIndex) {
    case 0:
       _spi = NRFX_SPIM_INSTANCE(0);
    default:
      break;
  }

  _spi_config = NRFX_SPIM_DEFAULT_CONFIG;
  _spi_config.sck_pin = kSpiClkPin;
  _spi_config.mosi_pin = kSpiMosiPin;
  _spi_config.miso_pin = kSpiMisoPin;
  _spi_config.ss_pin = kSpiCsPin;
  _spi_config.frequency = kSpiSpeed;
}

pca10040::SpiDriver::~SpiDriver() {
  deinit();
}


void pca10040::SpiDriver::init() {
  if (_initialized) {
    return;
  }

  ret_code_t err_code = nrfx_spim_init(&_spi, &_spi_config, spi_event_handler, this);
  // ret_code_t err_code = nrfx_spim_init(&_spi, &_spi_config, NULL, this);
  APP_ERROR_CHECK(err_code);

  _initialized = true;

}


void pca10040::SpiDriver::deinit() {
  if (!_initialized) {
    return;
  }

  nrfx_spim_uninit(&_spi);
  _initialized = false;
}


void pca10040::SpiDriver::transfer(const uint8_t * tx_data, uint32_t tx_length, uint8_t * rx_data, uint32_t rx_length, bool blocking){
  if (!_initialized) {
    return;
  }

  _transfer_complete = false;

  _spi_xfer.p_tx_buffer = tx_data;
  _spi_xfer.tx_length = tx_length;
  _spi_xfer.p_rx_buffer = rx_data;
  _spi_xfer.rx_length = rx_length;

  ret_code_t error = nrfx_spim_xfer(&_spi, &_spi_xfer, 0);

  if (blocking) {
    while (!_transfer_complete) {
      __WFE();
    }
  }
}


void pca10040::SpiDriver::write(uint8_t reg, uint8_t * data, uint32_t length) {
  if ( length + 1  > kBufferSize ){
    // length = kBufferSize - 1;
    APP_ERROR_CHECK(NRF_ERROR_INVALID_LENGTH);
  }

  _tx_buffer[0] = reg;
  memcpy(_tx_buffer + 1, data, length);
  transfer(_tx_buffer, length+1, _rx_buffer, 0, true);
}


void pca10040::SpiDriver::read(uint8_t reg, uint8_t * data, uint32_t length) {
  if ( length + 1  > kBufferSize ){
    // length = kBufferSize - 1;
    APP_ERROR_CHECK(NRF_ERROR_INVALID_LENGTH);
  }

  _tx_buffer[0] = reg | 0x80;
  transfer(_tx_buffer, 1, _rx_buffer, length+1, true);
  memcpy(data, _rx_buffer+1, length);
}


void pca10040::SpiDriver::spi_event_handler(nrfx_spim_evt_t const * p_event, void * p_context){
  SpiDriver * spi_driver = static_cast<SpiDriver *>(p_context);

  switch (p_event->type) {
    case NRFX_SPIM_EVENT_DONE:
      spi_driver->_transfer_complete = true;
      break;
    default:
      break;
  }
}