/**
 * @file pca10040_main.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief This is the main file for the pca10040-based BMP280 application.
 *
 * The BMP280 application demonstrates the use of either the SPI or TWI (I2C)
 * interface to communicate with a peripheral sensor; in this case the BMP280
 * pressure and temperature sensor. The application initialises the sensor and
 * continuously polls for new data, printing the results to the NRF LOG.
 */
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "boards.h"


// check which interface to use (default to spi)
#ifdef BMP280_USE_TWI
#include "platform/pca10040/bmp280/bmp280_twi.h"
pca10040::Bmp280Twi bmp;
#else
#include "platform/pca10040/bmp280/bmp280_spi.h"
pca10040::Bmp280Spi bmp;
#endif


int main(void)
{
  // initialize the board's LEDs
  bsp_board_init(BSP_INIT_LEDS);

  // initialize logging using defaults from sdk_config.h
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  // give the sensor a couple of ms to wakeup before attempting communication
  nrf_delay_ms(2);

  // initialise the BMP280 driver and check communication is working
  if (!bmp.init() ){
    NRF_LOG_INFO("BMP280 init failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  // perform a soft reset to ensure we're starting fresh
  bmp.reset();

  // apply default configuration to the sensor
  if (!bmp.configure() ){
    NRF_LOG_INFO("BMP280 config failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  // check the minimum delay between measurements (based on configuration)  
  uint32_t sampling_interval = bmp.get_sampling_interval();
  NRF_LOG_INFO("Sampling interval: %dus", sampling_interval);

  // no need to go any faster than this for this demo
  if ( sampling_interval < 10000 ) {
    NRF_LOG_INFO("Limiting sampling interval to 10ms");
    sampling_interval = 10000;
  }

  // request the sensor to start sampling
  if (!bmp.start() ){
    NRF_LOG_INFO("BMP280 start failed");
    NRF_LOG_FLUSH();
    bsp_board_led_invert(0);
    APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
  }

  // print a header line to the log and prep some status variables  
  NRF_LOG_INFO("temperature,pressure");
  NRF_LOG_FLUSH();
  float temperature;
  float pressure;
  bool result;

  // loop forever, sampling at (roughly) consistent intervals
  while (1) {

    // make sure the sensor is ready before reading data
    if ( bmp.meas_ready() ) {

      // indicate that we're reading data and read back the next sample
      bsp_board_led_invert(0);
      result = bmp.sample();
      if (!result) {
        APP_ERROR_CHECK(NRF_ERROR_INTERNAL);
      }

      // grab the latest temperature and pressure values and print to the log
      temperature = bmp.get_temperature();
      pressure = bmp.get_pressure();
      NRF_LOG_INFO(NRF_LOG_FLOAT_MARKER "," NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(temperature), NRF_LOG_FLOAT(pressure));
      NRF_LOG_FLUSH();
      bsp_board_led_invert(0);

    }

    // timing isn't too critical here, so a simple delay is fine
    nrf_delay_ms(sampling_interval/1000);
  }

  // should never get here...
  bsp_board_led_invert(0);

  return 0;
}