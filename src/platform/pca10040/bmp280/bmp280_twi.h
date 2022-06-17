/**
 * @file bmp280_twi.h
 * @author Alec Turner (<)alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-15
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Definition of the Bmp280Twi class.
 */

#ifndef SRC_PLATFORM_PCA10040_BMP280_BMP280_TWI_H_
#define SRC_PLATFORM_PCA10040_BMP280_BMP280_TWI_H_ 


#include "platform/pca10040/bmp280/bmp280_driver.h"
#include "platform/pca10040/twi/twi_driver.h"


namespace pca10040 {

  class Bmp280Twi : public Bmp280Driver {
  public:
    Bmp280Twi();
    ~Bmp280Twi();

    virtual bool init();
    virtual void deinit();
    static void delay(uint32_t duration, void * intf_ptr);
    static int8_t read(uint8_t reg, uint8_t * data, uint32_t length, void * intf_ptr);
    static int8_t write(uint8_t reg, const uint8_t * data, uint32_t length, void * intf_ptr);

  protected:

  private:

    // Note: SDO-GND=0x76, SDO-VDDIO=0x77
    // static constexpr uint8_t kDeviceAddress = 0x76;
    static constexpr uint8_t kDeviceAddress = 0x77;
    static constexpr uint8_t kBufferSize = 255;
    TwiDriver _twi_driver;
    
    uint8_t _trx_buffer;
};

}  // namespace pca10040

#endif // SRC_PLATFORM_PCA10040_BMP280_BMP280_TWI_H_