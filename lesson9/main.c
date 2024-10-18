#include <stdint.h>
#include "delay.h"
#include "stm32f10x.h"

int x = 9;
int y =8;
uint32_t z = 888;
int32_t m = 777;

typedef struct {
	int32_t s32;
	uint32_t u32;
	int16_t s16;
	uint16_t u16;
	int8_t s8;
	uint8_t u8;
}new_struct;
new_struct a = {1,2,3,4,5,6};
new_struct b = {1,2,3,4,5,6};
new_struct c = {1,2,3,4,5,6};
new_struct d = {1,2,3,4,5,6};
new_struct e = {1,2,3,4,5,6};
new_struct f;
new_struct g;
new_struct h;

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
