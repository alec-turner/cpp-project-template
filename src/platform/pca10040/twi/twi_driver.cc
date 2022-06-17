/**
 * @file twi_driver.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Implementation of the TwiDriver class.
 */

#include "platform/pca10040/twi/twi_driver.h"


/**
 * @brief Construct a new TWI Driver:: TWI Driver object
 */
pca10040::TwiDriver::TwiDriver() {
  _initialized = false;
  _transfer_complete = false;

  switch (kTwiIndex) {
    case 0:
      _twi = NRFX_TWI_INSTANCE(0);
      break;
    default:
      APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }
}


/**
 * @brief Destroy the TWI Driver:: TWI Driver object
 */
pca10040::TwiDriver::~TwiDriver() {
  deinit();
}


/**
 * @brief Initialise the TWI driver.
 */
void pca10040::TwiDriver::init() {
  if (_initialized) {
    return;
  }

  _initialized = false;
  _transfer_complete = false;

  _twi_config.scl = kTwiSClkPin;
  _twi_config.sda = kTwiSdaPin;
  _twi_config.frequency = kTwiClockSpeed;
  _twi_config.interrupt_priority = kTwiIrqPriority;

  ret_code_t result = nrfx_twi_init(&_twi, &_twi_config, twi_event_handler, NULL);
  if (result != NRF_SUCCESS) {
    APP_ERROR_CHECK(result);
  }

  nrfx_twi_enable(&_twi);
  
  _initialized = true;
}


/**
 * @brief Deinitialise the TWI driver.
 */
void pca10040::TwiDriver::deinit() {
  if (!_initialized) {
    return;
  }

  nrfx_twi_uninit(&_twi);
  _initialized = false;
}


/**
 * @brief Write to a TWI device.
 * @param address The address of the device to write to.
 * @param data The data to write.
 * @param length The length of the data to write.
 * @param no_stop If true, the TWI will not set the stop condition after the write.
 * @param blocking If true, wait for the transaction to complete before returning
 */
void pca10040::TwiDriver::write(uint8_t address, uint8_t * data, uint32_t length, bool no_stop, bool blocking) {
  if (!_initialized || nrfx_twi_is_busy(&_twi) ) {
    return;
  }

  _transfer_complete = false;

  // send control byte
  ret_code_t result = nrfx_twi_tx(&_twi, address & kWriteMask, data, length, no_stop);
  if (result != NRF_SUCCESS) {
    APP_ERROR_CHECK(result);
  }

  if (blocking) {
    while (nrfx_twi_is_busy(&_twi)) {
      __WFE();
    }
  }
}


/**
 * @brief Read from a TWI device.
 * @param address The address of the device to read from.
 * @param data The data buffer to store the read data.
 * @param length The number of bytes to read.
 * @param blocking If true, wait for the transaction to complete before returning
 */
void pca10040::TwiDriver::read(uint8_t address, uint8_t * data, uint32_t length, bool blocking) {
  if (!_initialized || nrfx_twi_is_busy(&_twi)) {
    return;
  }

  _transfer_complete = false;

  ret_code_t result = nrfx_twi_rx(&_twi, address | kReadMask, data, length);
  if (result != NRF_SUCCESS) {
    APP_ERROR_CHECK(result);
  }

  if (blocking) {
    while (nrfx_twi_is_busy(&_twi)) {
      __WFE();
    }
  }
}


/**
 * @brief Write to a TWI device register
 * 
 * @param address device bus address
 * @param reg register address
 * @param data data buffer to write from
 * @param length number of bytes to write
 */
void pca10040::TwiDriver::write_reg(uint8_t address, uint8_t reg, uint8_t * data, uint32_t length) {
  if (!_initialized) {
    return;
  }

  _tx_buffer[0] = reg;
  memcpy(&_tx_buffer[1], data, length);
  write(address, _tx_buffer, length + 1, false, true);
}


/**
 * @brief Read from a TWI device register
 *
 * @param address device bus address
 * @param reg register address
 * @param data data buffer to store read data
 * @param length number of bytes to read
 */
void pca10040::TwiDriver::read_reg(uint8_t address, uint8_t reg, uint8_t * data, uint32_t length) {
  if (!_initialized) {
    return;
  }

  _tx_buffer[0] = reg;
  write(address, _tx_buffer, 1, true, true);

  read(address, data, length, true);
}


/**
 * @brief TWI event handler.
 * @param p_event The event that occurred.
 * @param p_context The related TwiDriver class instance.
 */
void pca10040::TwiDriver::twi_event_handler(nrfx_twi_evt_t const * p_event, void * p_context) {
  TwiDriver * twi_driver = static_cast<TwiDriver *>(p_context);

  switch (p_event->type) {
    case NRFX_TWI_EVT_DONE:
      twi_driver->_transfer_complete = true;
      break;
    case NRFX_TWI_EVT_ADDRESS_NACK:
      APP_ERROR_CHECK(NRF_ERROR_INVALID_ADDR);
      break;
    case NRFX_TWI_EVT_DATA_NACK:
      APP_ERROR_CHECK(NRF_ERROR_INVALID_DATA);
      break;
    case NRFX_TWI_EVT_OVERRUN:
      APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
      break;
    case NRFX_TWI_EVT_BUS_ERROR:
      APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
      break;
    default:
      break;
  }
}
