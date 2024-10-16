#include "delay.h"

void delay(unsigned iter){
		unsigned volatile counter = 0;
		while (counter < iter){
				counter++;
		}
}