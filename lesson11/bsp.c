#include "bsp.h"
#include "miros.h"

static uint32_t volatile l_tickCtr;
void BSP_delay(uint32_t ticks){
		while(ticks > 0){
				ticks--;
		};
}
 
 void BSP_init(){
    RCC->APB2ENR |= RCC_GPIOB;
    GPIOB->CRH &= ~((0xF << 4U) | (0xF));
	  GPIOB->CRH |= ((0b0011 << 4U) | (0b0011)); 
    GPIOB->CRL &= ~(0xF << 28U);
    GPIOB->CRL |= (0b0011 << 28U); 	
}

void BSP_LedGreenOn(){
		GPIOB->ODR &= ~(1U << 9U);
}

void BSP_LedGreenOff(){
		GPIOB->ODR |= (1U << 9U);
}

void BSP_LedRedOn(){
		GPIOB->ODR &= ~(1U << 8U);
}

void BSP_LedRedOff(){
		GPIOB->ODR |= (1U << 8U);
}

void BSP_LedYellowOn(){
		GPIOB->ODR &= ~(1U << 7U);
}

void BSP_LedYellowOff(){
		GPIOB->ODR |= (1U << 7U);
}

void SysTick_Handler(void) {
    ++l_tickCtr;
		__disable_irq();
		OS_sched();
	  __enable_irq();
}

void OS_onStartup(void){
	  SysTick->LOAD = SYSTICK_RELOAD;
		SysTick->VAL = 0;
	  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
		/*set the system tick interrupt priority (highest)*/
	  NVIC_SetPriority(SysTick_IRQn, 0U);
}