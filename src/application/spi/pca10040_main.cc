/**
 * @file pca10040_main.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "boards.h"
#include "platform/pca10040/bmp280/bmp280_spi.h"


// Initialise base SPI and BMP280 drivers
pca10040::Bmp280Spi bmp;


int main(void)
{
  bsp_board_init(BSP_INIT_LEDS);

  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  if (!bmp.init() ){
    NRF_LOG_INFO("BMP280 SPI init failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  if (!bmp.configure() ){
    NRF_LOG_INFO("BMP280 SPI config failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  uint32_t sampling_interval = bmp.get_sampling_interval();
  NRF_LOG_INFO("Sampling interval: %dus", sampling_interval);

  if ( sampling_interval < 10000 ) {
    NRF_LOG_INFO("Limiting sampling interval to 10ms");
    sampling_interval = 10000;
  }

  if (!bmp.start() ){
    NRF_LOG_INFO("BMP280 start failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  
  NRF_LOG_INFO("temperature,pressure");
  NRF_LOG_FLUSH();
  uint32_t index = 0;
  float temperature;
  float pressure;
  bool result;

  while (1) {

    bsp_board_led_invert(0);

    if ( bmp.meas_ready() ) {
      result = bmp.sample();
      if (!result) {
        APP_ERROR_CHECK(1);
      }

      temperature = bmp.get_temperature();
      pressure = bmp.get_pressure();
      NRF_LOG_INFO(NRF_LOG_FLOAT_MARKER "," NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(temperature), NRF_LOG_FLOAT(pressure));
      NRF_LOG_FLUSH();

    }
    nrf_delay_us(sampling_interval);
    index++;
  }

  bsp_board_led_invert(0);

  return 0;
}