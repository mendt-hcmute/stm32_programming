#ifndef MIROS_H_
#define MIROS_H_
#include <stdint.h>

#define MAX_THREAD 32
/* Thread Control Block (TCB) */
typedef struct {
		void *sp; /*stack pointer*/
	  
}OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void);

/*this function must be called with interrupt DISABLED*/
void OS_sched(void);

/* transfer control to the RTOS to run the threads*/
void OS_run(void);

/*callback to configure and start interrupts*/
void OS_onStartup(void);

void OSThread_start(
		OSThread *me,
		OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);
#endif