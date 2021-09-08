#pragma once
#include "driver/gpio.h"

#if CONFIG_IDF_TARGET_ESP32S2
  #include "gpio_config_s2.h"
#else
  #include "gpio_config.h"
#endif

void epd_base_init(uint32_t epd_row_width);
void epd_base_deinit();
void epd_poweron();
void epd_poweroff();

/**
 * Start a draw cycle.
 */
void epd_start_frame();

/**
 * End a draw cycle.
 */
void epd_end_frame();

/**
 * Waits until all previously submitted data has been written.
 * Then, the following operations are initiated:
 *
 *  - Previously submitted data is latched to the output register.
 *  - The RMT peripheral is set up to pulse the vertical (gate) driver for
 *  `output_time_dus` / 10 microseconds.
 *  - The I2S peripheral starts transmission of the current buffer to
 *  the source driver.
 *  - The line buffers are switched.
 *
 * This sequence of operations allows for pipelining data preparation and
 * transfer, reducing total refresh times.
 */
void IRAM_ATTR epd_output_row(uint32_t output_time_dus);

/** Skip a row without writing to it. */
void IRAM_ATTR epd_skip();

/**
 * Get the currently writable line buffer.
 */
uint8_t IRAM_ATTR *epd_get_current_buffer();

/**
 * Switches front and back line buffer.
 * If the switched-to line buffer is currently in use,
 * this function blocks until transmission is done.
 */
void IRAM_ATTR epd_switch_buffer();

