/**
 * @file bmp280_driver.h
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SRC_PLATFORM_PCA10040_BMP280_BMP280_DRIVER_H_
#define SRC_PLATFORM_PCA10040_BMP280_BMP280_DRIVER_H_ 

#include <stdint.h>
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "platform/pca10040/bmp280/bmp2.h"
#include "platform/pca10040/bmp280/bmp2_defs.h"


namespace pca10040 {

  class Bmp280Driver {
  public:
    Bmp280Driver();
    ~Bmp280Driver();
    bool configure();
    bool start();
    bool stop();
    bool reset();
    bool meas_ready();
    bool sample();
    uint32_t get_sampling_interval(){ return _sampling_interval; }
    float get_temperature();
    float get_pressure();

    void set_power_mode(uint8_t mode){ _power_mode = mode; }
    void set_os_mode(uint8_t mode){ _config.os_mode = mode; }
    void set_odr(uint8_t odr){ _config.odr = odr; }
    void set_filter(uint8_t filter){ _config.filter = filter; }

    virtual bool init() = 0;
    virtual void deinit() = 0;

  protected:
    bmp2_dev _bmp;

  private:
    static constexpr uint8_t kDefaultPowerMode = BMP2_POWERMODE_NORMAL;
    static constexpr uint8_t kDefaultOsMode = BMP2_OS_MODE_STANDARD_RESOLUTION;
    static constexpr uint8_t kDefaultFilter = BMP2_FILTER_OFF;
    static constexpr uint8_t kDefaultOdr = BMP2_ODR_0_5_MS;

    bmp2_config _config;
    bmp2_data _data;
    uint8_t _power_mode;
    uint32_t _sampling_interval;
    
};

}  // namespace pca10040

#endif // SRC_PLATFORM_PCA10040_BMP280_BMP280_DRIVER_H_