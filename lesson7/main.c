#include <stdint.h>
#include "delay.h"

#define RCC_BASE    0x40021000U
#define GPIOC_BASE  0x40011000U

#define RCC_APB2ENR (*(uint32_t*)(RCC_BASE   + 0x18U))
#define GPIOC_CRH   (*(uint32_t*)(GPIOC_BASE + 0x04U))
#define GPIOC_ODR   (*(uint32_t*)(GPIOC_BASE + 0x0CU))
int* swap(int *x, int *y);

int* swap(int *x, int *y){
		static int tmp[2];
		tmp[0] = *x;
	  tmp[1] = *y;
		*x = tmp[1];
		*y = tmp[0];
		return tmp;
}

int main()
{

    /* Enable peripheral clock for PORTC (bit 4 in APB2ENR) */
    RCC_APB2ENR |= (1U << 4U);
		
    /* Configure PC13 as General purpose output push-pull */
    GPIOC_CRH &= ~(0xF << 20U);          // Clear bits [23:20] for PC13
    GPIOC_CRH |= (0b0011 << 20U);        // Set push-pull mode

    /* Toggle the LED at PC13 */
    while (1)
    {
				int x = 1000000;
				int y = 4* 1000000;
				int* p = swap(&x, &y);
        GPIOC_ODR &= ~(1U << 13);
				delay(p[0]);
			  GPIOC_ODR |= (1U << 13);
				delay(p[1]);
    }
    return 0;
}
