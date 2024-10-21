#include "miros.h"
#include <stdint.h>
#include "stm32f10x.h"

OSThread * volatile OS_curr;  /*pointer to the current thread*/
OSThread * volatile OS_next;	/*pointer to the next thread to run*/
OSThread *OS_thread[32 + 1];
uint8_t OS_threadNum;
uint8_t OS_currIdx;						/*current index for round robin scheduler*/

void OSThread_start(
		OSThread *me,
		OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize)
{
		uint32_t *sp = (uint32_t*)((((uint32_t)stkSto + stkSize)/ 8)* 8);
		uint32_t *stk_limit;
		
		/*Cotex-M ISR stack frame for blinky1*/
		*(--sp) = (1U << 24U); /*xPSR*/
	  *(--sp) = (uint32_t)threadHandler;  /*PC*/
		*(--sp) = 0x0000000EU;  /*LR*/
	  *(--sp) = 0x0000000CU;  /*R12*/
	  *(--sp) = 0x00000003U;  /*R3*/
	  *(--sp) = 0x00000002U;  /*R2*/
	  *(--sp) = 0x00000001U;  /*R1*/
	  *(--sp) = 0x00000000U;  /*R0*/
		/*Additionally, fake registers R4 - R11*/
		*(--sp) = 0x0000000BU;  /*R11*/
	  *(--sp) = 0x0000000AU;  /*R10*/
	  *(--sp) = 0x00000009U;  /*R9*/
	  *(--sp) = 0x00000008U;  /*R8*/
	  *(--sp) = 0x00000007U;  /*R7*/
	  *(--sp) = 0x00000006U;  /*R6*/
	  *(--sp) = 0x00000005U;  /*R5*/
	  *(--sp) = 0x00000004U;  /*R4*/
	
		/*save the top of the stack in the thread's attibute*/
		me->sp = sp;
		
		/*round up the bottom of the stack to the 8-byte boundary*/
		stk_limit = (uint32_t *)(((((uint32_t)stkSto - 1U)/ 8) + 1U)* 8);
		
		/*pre-fill the unused part of the stack with 0xDEADBEEF*/
		for(sp = sp - 1U; sp >=stk_limit; --sp){
				*sp = 0xDEADBEEFU;
		}
		if(OS_threadNum < MAX_THREAD){
				/* register the thread with the OS */
	    	OS_thread[OS_threadNum] = me;
		    ++OS_threadNum;
		}else{
				/* do something to take error log*/
		}
}

void OS_init(void){
		/*set the PendSV interrupt priority to the lowest level */
	  *(uint32_t volatile *)0xE000ED20 |= (0xFFU << 16);
}
void OS_sched(void){
    ++OS_currIdx;
		if(OS_currIdx == OS_threadNum){
				OS_currIdx = 0U;
		}
		OS_next = OS_thread[OS_currIdx];
		/*OS_next = ...*/
	  if(OS_next != OS_curr){
				*(uint32_t volatile  *)0xE000ED04 = (1U << 28U);
		}
}

void OS_run(void){
	  /*callback to configure and start interrupts*/
		OS_onStartup();
	
		__disable_irq();
		OS_sched();
	  __enable_irq();
	
		/*add some assert fail*/
}

void PendSV_Handler(void){
		/* __disable_irq(); */
		__asm volatile (
		/* __ASM volatile ("cpsid i" : : : "memory"); */
		"CPSID   I\n"

		"MOVW     r0,#:lower16:OS_curr\n"
		"MOVT     r0,#:upper16:OS_curr\n"
		"LDR      r0,[r0,#0x00]\n"
		"CBZ      r0,PendSV_storing\n"
		"B        PendSV_if\n"
		/*  OS_curr->sp = sp; */
		"PendSV_if:\n"
		/* if(OS_curr != (OSThread *)0){ */
		/* Push register r4 - r11 on the stack */ 
		"PUSH     {r4 - r11}\n"
		/* LDR      r0,[sp,#0x00] */
		"MOVW     r1,#:lower16:OS_curr\n"
		"MOVT     r1,#:upper16:OS_curr\n"
		"LDR      r1,[r1,#0x00]\n"
		"STR      sp,[r1,#0x00]\n"
		/*  } */
		 /* sp = OS_next->sp;  */
		"PendSV_storing:\n"
		"MOVW     r0, #:lower16:OS_next\n"
		"MOVT     r0, #:upper16:OS_next\n"
		"LDR      r1,[r0,#0x00]\n"
		"LDR      r1,[r1,#0x00]\n"
		/* STR     r1, sp */
		"MOV      sp, r1\n"
		/* OS_curr = OS_next; */

		/* __enable_irq(); */
		"LDR      r0,[r0,#0x00]\n"
		"MOVW     r1,#:lower16:OS_curr\n"
		"MOVT     r1,#:upper16:OS_curr\n"
		"STR      r0,[r1,#0x00]\n"
	   /* pop registers r4 - r11 on the stack */ 
		"POP     {r4 - r11}\n"
		/* __ASM volatile ("cpsie i" : : : "memory"); */
		"CPSIE    I \n"
		/* } */
		
		"BX       lr\n"
		);
}
