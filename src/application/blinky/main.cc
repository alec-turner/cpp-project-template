#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

int main(void)
{
  bsp_board_init(BSP_INIT_LEDS);

  while (1) {
    for (uint8_t i = 0; i < LEDS_NUMBER; i++) {
      bsp_board_led_invert(i);
      nrf_delay_ms(500);
    }
  }
}