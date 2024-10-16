#include <stdint.h>
#include "delay.h"
#include "stm32f10x.h"

int main()
{

    /* Enable peripheral clock for PORTC (bit 4 in APB2ENR) */
    RCC->APB2ENR |= (1U << 4U);
		
    /* Configure PC13 as General purpose output push-pull */
    GPIOC->CRH &= ~(0xF << 20U);          // Clear bits [23:20] for PC13
    GPIOC->CRH |= (0b0011 << 20U);        // Set push-pull mode

    /* Toggle the LED at PC13 */
    while (1)
    {
        GPIOC->ODR &= ~(1U << 13);
				delay(1000000);
			  GPIOC->ODR |= (1U << 13);
				delay(4* 1000000);
    }
    return 0;
}
