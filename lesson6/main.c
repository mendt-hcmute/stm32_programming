#include <stdint.h>
#include "delay.h"

#define RCC_BASE    0x40021000U
#define GPIOC_BASE  0x40011000U

#define RCC_APB2ENR (*(uint32_t*)(RCC_BASE   + 0x18U))
#define GPIOC_CRH   (*(uint32_t*)(GPIOC_BASE + 0x04U))
#define GPIOC_ODR   (*(uint32_t*)(GPIOC_BASE + 0x0CU))

unsigned fact(unsigned n);

unsigned fact(unsigned n){
		//0! = 1
		//n = n*(n-1)!
		unsigned foo[6];
		foo[n] = n;
		if(n == 0U){
				return 1;
		}else {
				return foo[n] * fact(n - 1);
		}
}

int main()
{
	  unsigned volatile x;
	  x = fact(9U);
	  x = 2U + 3U + fact(3U);
	  (void)fact(5U);
    /* Enable peripheral clock for PORTC (bit 4 in APB2ENR) */
    RCC_APB2ENR |= (1U << 4U);

    /* Configure PC13 as General purpose output push-pull */
    GPIOC_CRH &= ~(0xF << 20U);          // Clear bits [23:20] for PC13
    GPIOC_CRH |= (0b0011 << 20U);        // Set push-pull mode

    /* Toggle the LED at PC13 */
    while (1)
    {
        GPIOC_ODR &= ~(1U << 13);
        /* Simple delay */
				delay(1000000);
			  GPIOC_ODR |= (1U << 13);
				delay(4000000);
    }
    return 0;
}