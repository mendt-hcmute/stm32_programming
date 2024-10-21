#ifndef BSP_H_
#define BSP_H_
#include <stdint.h>
#include "stm32f10x.h"

#define CORE_CLOCK 8000000U
#define SYSTICK_RELOAD CORE_CLOCK/200 - 1
#define RCC_GPIOB (1U << 3U)

void BSP_delay(uint32_t ticks);
void BSP_init();
void BSP_LedGreenOn();
void BSP_LedGreenOff();
void BSP_LedRedOn();
void BSP_LedRedOff();
void BSP_LedYellowOn();
void BSP_LedYellowOff();

#endif