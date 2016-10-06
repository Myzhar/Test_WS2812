#include "ws2812_handler.h"

#include "tim.h"

#define H_VAL 70
#define L_VAL 35
#define BITS_PER_LED (3*8)
#define BIT_BUF_SIZE ((N_LEDS * BITS_PER_LED) + 5)

uint32_t ws2812BitBuf[BIT_BUF_SIZE];

void initLedBar()
{
	for (int i = 0; i < BIT_BUF_SIZE; i++)
		ws2812BitBuf[i] = 0;

	turnOffBar();
}

void turnOffBar()
{
	for (int i = 0; i < N_LEDS; i++)
		ws2812_set_color(i, 0, 0, 0);

	lightLedBar();
}

void ws2812_set_color(int ledIdx, uint8_t r, uint8_t g, uint8_t b)
{
	if (ledIdx >= N_LEDS)
		return;

	int i = ledIdx * BITS_PER_LED;
	uint8_t mask;
	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & g) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}
	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & r) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}
	mask = 0x80;
	while (mask)
	{
		ws2812BitBuf[i] = (mask & b) ? H_VAL : L_VAL;
		mask >>= 1;
		i++;
	}
}

void lightLedBar()
{
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*) ws2812BitBuf,
			sizeof(ws2812BitBuf) / sizeof(ws2812BitBuf[0]));
}

void ledStartupSequence()
{
	int max_level = 255;

	for (int t = 0; t < max_level; t++)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, t, 0, 0);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	for (int t = max_level; t != 0; t--)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, t, 0, 0);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	for (int t = 0; t < max_level; t++)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, 0, t, 0);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	for (int t = max_level; t != 0; t--)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, 0, t, 0);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	for (int t = 0; t < max_level; t++)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, 0, 0, t);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	for (int t = max_level; t != 0; t--)
	{
		for (int i = 0; i < N_LEDS; i++)
		{
			ws2812_set_color(i, 0, 0, t);
		}

		lightLedBar();
		HAL_Delay(5); //*/
	}

	turnOffBar();
	// >>>>> Red run

	/*duration = 1000;
	 int levels = 255;
	 int step = duration/levels;
	 for( int i=0; i<levels; i++ )
	 {
	 ws2812_set_color(1, i, 0, 0);

	 lightLedBar();
	 HAL_Delay(step);
	 } //*/
}

