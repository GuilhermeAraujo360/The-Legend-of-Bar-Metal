#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdbool.h>

extern volatile bool flag_timer;

unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd);
void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter);
unsigned int DMTimerCounterGet(unsigned int baseAdd);
void DMTimerEnable(unsigned int baseAdd);
void DMTimerDisable(unsigned int baseAdd);
void uDelay (unsigned int ms);
void ckmSetCLKModuleRegister();

void DMTimerIsr(void);
void msDelayInterrupt(unsigned int ms);
void srand_init(void);
int rand(void);
#define CM_PER_TIMER7_CLKCTRL                  (0x7C) // ok
#define CM_PER_TIMER7_CLKCTRL_MODULEMODE_ENABLE (0x2) // ok
// DMTIMER7 OK
#define CM_PER_TIMER7_CLKCTRL_MODULEMODE_DISABLE (0x03)

/* Timer Synchronous Interface Control Register */
#define DMTIMER_TSICR                 (0x54) // ok
#define DMTIMER_TSICR_POSTED          (1 << 2) // ok


#define DMTIMER_TWPS                  (0x48) // ok

// escrita depente nos registradores:
// TCLR, TCRR, TLDR, TTGR, TMAR]
// TODOS OK
#define DMTIMER_TWPS_W_PEND_TCLR      (1 << 0)
#define DMTIMER_TWPS_W_PEND_TCRR      (1 << 1)
#define DMTIMER_TWPS_W_PEND_TLDR      (1 << 2)
#define DMTIMER_TWPS_W_PEND_TTGR      (1 << 3)
#define DMTIMER_TWPS_W_PEND_TMAR      (1 << 4)

//======================================================
#define DMTIMER_TCLR                  (0x38) // OK
#define DMTIMER_TCLR_ST               (1 << 0)   /* Start/Stop timer ok */
#define DMTIMER_TCLR_AR               (1 << 1)   /* Auto reload  ok*/
//======================================================

#define DMTIMER_TCRR  (0x3C)  /* Counter Register */ // OK

#define DMTIMER_TLDR (0x40)   /* Load Register  OK */ 


#define DMTIMER_IRQSTATUS_RAW    (0x024)  /* Timer Status Raw Register */
#define DMTIMER_IRQSTATUS        (0x028)  /* Timer Status Register (limpa escrevendo 1) */
#define DMTIMER_IRQENABLE_SET    (0x02C)  /* Timer Interrupt Enable Set Register */
#define DMTIMER_IRQENABLE_CLR    (0x030)  /* Timer Interrupt Enable Clear Register */
#define DMTIMER_IRQWAKEEN        (0x034)  /* Timer IRQ Wakeup Enable Register */
 
#define DMTIMER_IRQ_MAT_IT_FLAG  (1 << 0) /* Match interrupt */
#define DMTIMER_IRQ_OVF_IT_FLAG  (1 << 1) /* Overflow interrupt */
#define DMTIMER_IRQ_TCAR_IT_FLAG (1 << 2) /* Capture interrupt */
 
#define TIMER_OVERFLOW            (0xFFFFFFFFU)
#define TIMER_1MS_COUNT           (24000U)  /* 24MHz => 24000 ticks por ms */
 
/* Linha de interrupção do DMTIMER7 no AINTC (Tabela 6.1 do TRM) */
#define SYS_INT_TINT7             (95)


#endif
