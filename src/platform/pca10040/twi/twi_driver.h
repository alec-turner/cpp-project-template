/**
 * @file twi_driver.h
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Definition of the TwiDriver class.
 */

#ifndef SRC_PLATFORM_PCA10040_TWI_TWI_DRIVER_H_
#define SRC_PLATFORM_PCA10040_TWI_TWI_DRIVER_H_ 

#include "nrfx_twi.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


namespace pca10040 {

  class TwiDriver {
  public:
    TwiDriver();
    ~TwiDriver();

    void init();
    void deinit();
    void write(uint8_t address, uint8_t * data, uint32_t length, bool no_stop, bool blocking);
    void read(uint8_t address, uint8_t * data, uint32_t length, bool blocking);
    void write_reg(uint8_t address, uint8_t reg, uint8_t * data, uint32_t length);
    void read_reg(uint8_t address, uint8_t reg, uint8_t * data, uint32_t length);

    static void twi_event_handler(nrfx_twi_evt_t const * p_event, void * p_context);

  private:
    static constexpr uint8_t kTwiIndex = 0;
    static constexpr uint8_t kTwiSClkPin = 3;
    static constexpr uint8_t kTwiSdaPin = 4;
    static constexpr	nrf_twi_frequency_t kTwiClockSpeed = NRF_TWI_FREQ_400K;
    static constexpr uint8_t kTwiIrqPriority = 6;

    static constexpr uint8_t kReadMask = 0x80;
    static constexpr uint8_t kWriteMask = 0x7F;
    static constexpr uint8_t kBufferSize = 255;

    nrfx_twi_t _twi;
    nrfx_twi_config_t _twi_config;

    bool _initialized;
    volatile bool _transfer_complete;

    uint8_t _rx_buffer[kBufferSize];
    uint8_t _tx_buffer[kBufferSize];
    
};

}  // namespace pca10040

#endif // SRC_PLATFORM_PCA10040_TWI_TWI_DRIVER_H_