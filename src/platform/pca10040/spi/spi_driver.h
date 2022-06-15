/**
 * @file spi_driver.h
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SRC_PLATFORM_PCA10040_SPI_SPI_DRIVER_H_
#define SRC_PLATFORM_PCA10040_SPI_SPI_DRIVER_H_ 

#include "nrfx_spim.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


namespace pca10040 {

  class SpiDriver {
  public:
    SpiDriver();
    ~SpiDriver();

    void init();
    void deinit();
    void transfer(const uint8_t * tx_data, uint32_t tx_length, uint8_t * rx_data, uint32_t rx_length, bool blocking);
    void write(uint8_t reg, uint8_t * data, uint32_t length);
    void read(uint8_t reg, uint8_t * data, uint32_t length);

    static void spi_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);

  private:
    static constexpr uint8_t kSpiIndex = 0;
    static constexpr uint8_t kSpiClkPin = 3;   // SCL
    static constexpr uint8_t kSpiMosiPin = 4;  // SDI
    static constexpr uint8_t kSpiCsPin = 28;    // CSB
    static constexpr uint8_t kSpiMisoPin = 29;  // SDO
    static constexpr uint8_t kSpiIrqPriority = 6;
    static constexpr uint8_t kOverrunChar = 0xFF;

    static constexpr	nrf_spim_frequency_t kSpiSpeed = NRF_SPIM_FREQ_8M;
    static constexpr nrf_spim_mode_t kSpiMode = NRF_SPIM_MODE_0;
    static constexpr nrf_spim_bit_order_t kSpiBitOrder = NRF_SPIM_BIT_ORDER_MSB_FIRST;

    static constexpr uint8_t kBufferSize = 255;

    nrfx_spim_t _spi;
    nrfx_spim_config_t _spi_config;
    nrfx_spim_xfer_desc_t _spi_xfer;

    bool _initialized;
    volatile bool _transfer_complete;

    uint8_t _rx_buffer[kBufferSize];
    uint8_t _tx_buffer[kBufferSize];
    
};

}  // namespace pca10040

#endif // SRC_PLATFORM_PCA10040_SPI_SPI_DRIVER_H_