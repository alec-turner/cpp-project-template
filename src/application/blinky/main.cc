/**
 * @file main.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief This is the main file for the PCA10040-based blinky application.
 */
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

int main(void)
{
  // initialize the board's LEDs
  bsp_board_init(BSP_INIT_LEDS);

  // loop forever, rotating through each of the available LEDs
  while (1) {
    for (uint8_t i = 0; i < LEDS_NUMBER; i++) {
      // toggle the current LED then wait for a half second
      bsp_board_led_invert(i);
      nrf_delay_ms(500);
    }
  }
}