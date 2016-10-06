#ifndef WS2812_HANDLER_H
#define WS2812_HANDLER_H

#include "stm32f4xx_hal.h"

#define N_LEDS (8)

void initLedBar();

void ws2812_set_color( int ledIdx, uint8_t r, uint8_t g, uint8_t b );
void lightLedBar();
void turnOffBar();

void ledStartupSequence();

#endif
