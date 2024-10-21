#include <stdint.h>
#include "bsp.h"
#include "miros.h"

uint32_t stack_blinky1[40];
OSThread blinky1;
void main_blinky1(){
    while (1)
    {
		    BSP_LedGreenOn();
				BSP_delay(1000000);
			  BSP_LedGreenOff();
				BSP_delay(4* 1000000);
    }
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void main_blinky2(){
		while(1){
				BSP_LedRedOn();
				BSP_delay(1000000);
			  BSP_LedRedOff();
				BSP_delay(4* 1000000);
		}
}

uint32_t stack_blinky3[40];
OSThread blinky3;
void main_blinky3(){
		while(1){
			  BSP_LedYellowOn();
				BSP_delay(1000000);
			  BSP_LedYellowOff();
				BSP_delay(4* 1000000);
		}
}


int main(){
		BSP_init();
		OS_init();
		/* start Blinky1 thread*/
    OSThread_start(&blinky1,
									 &main_blinky1,
									 stack_blinky1, sizeof(stack_blinky1));
	
	  /* start Blinky2 thread*/
    OSThread_start(&blinky2,
									 &main_blinky2,
									 stack_blinky2, sizeof(stack_blinky2));
		/* start Blinky3 thread*/
    OSThread_start(&blinky3,
									 &main_blinky3,
									 stack_blinky3, sizeof(stack_blinky3));
		OS_run();
		//return 0;
}

void Q_onAssert(char const *module, int loc){
	  /*TBD: dame control*/
		(void)module; /*avoid the unused parameter*/
	  (void)loc; /*avoid the unused parameter*/
	  NVIC_SystemReset();
}