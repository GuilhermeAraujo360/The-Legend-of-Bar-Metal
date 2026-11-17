#ifndef _INTERRUPTION_H_
#define _INTERRUPTION_H_
//#include "../inc/hw_types.h"
#include "../inc/soc_AM335x.h"

#define INTC_SYSCONFIG (0x10)
#define INTC_SYSCONFIG_SOFTRESET (1 << 1)
#define INTC_SYSSTATUS (0x14) // ok 
#define INTC_SYSSTATUS_RESETDONE (1 << 0)
#define INTC_THRESHOLD (0x68) // ok 
#define INTC_THRESHOLD_PRIORITYTHRESHOLD (0x3F)
#define SYS_INT_GPIOINT3A                      (62)
#define SYS_INT_GPIOINT3B                      (63)
#define CLEAR1 (0xA8) // ok 
#define INTC_SIR_IRQ (0x40) // ok
#define INTC_SIR_FIQ (0x44) // ok
#define INTC_MIR_CLEAR0  (0x88) // ok 
#define ENABLE1 (0xA4)   /* MIR_CLEAR1 — habilita interrupções 32–63  */
#define ENABLE2 (0xC4)   /* MIR_CLEAR2 — habilita interrupções 64–95  */
#define ENABLE3 (0xE4)   /* MIR_CLEAR3 — habilita interrupções 96–127 */
#define INTC_CONTROL (0x48) // ok 
#define CLEAR3 (0xE8) // ok 
#define GPIO_IRQSTATUS_SET_0 (0x34)
#define GPIO_IRQSTATUS_SET_1 (0x38)
#define GPIO_IRQSTATUS_0  (0x2C)
#define GPIO_IRQSTATUS_1  (0x30)
#define GPIO_RISINGDETECT    (0x148)
#define GPIO_FALLINGDETECT   (0x14C)
#define GPIO_IRQSTATUS_CLR_0  (0x3C)
#define GPIO_DEBOUNCENABLE   (0x150)
#define GPIO_DEBOUNCINGTIME  (0x154)
#define CLEAR2 (0xC8)
void IntAINTCInit();
void interrupt_enable_GPIO1(int k);
void interrupt_enable_timer7();
void ISR_Handler(void);
void IntMasterIRQEnable(void);
void interrupt_enable_GPIO3(int k);
#endif