/**
 * @file bmp280_spi.h
 * @author Alec Turner (<)alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Definition of the Bmp280Spi class.
 */

#ifndef SRC_PLATFORM_PCA10040_BMP280_BMP280_SPI_H_
#define SRC_PLATFORM_PCA10040_BMP280_BMP280_SPI_H_ 

#include "platform/pca10040/bmp280/bmp280_driver.h"
#include "platform/pca10040/spi/spi_driver.h"

namespace pca10040 {

  class Bmp280Spi : public Bmp280Driver {
  public:
    Bmp280Spi();
    ~Bmp280Spi();

    virtual bool init();
    virtual void deinit();
    static void delay(uint32_t duration, void * intf_ptr);
    static int8_t read(uint8_t reg, uint8_t * data, uint32_t length, void * intf_ptr);
    static int8_t write(uint8_t reg, const uint8_t * data, uint32_t length, void * intf_ptr);

  protected:

  private:

    SpiDriver _spi_driver;
    
};

}  // namespace pca10040

#endif // SRC_PLATFORM_PCA10040_BMP280_BMP280_SPI_H_