#include "../inc/includes.h"


void IntAINTCInit() {
    
    HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;
   
    while((HWREG(SOC_AINTC_REGS + INTC_SYSSTATUS) &
     INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);

    HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = INTC_THRESHOLD_PRIORITYTHRESHOLD;
    
}


void interrupt_enable_GPIO1(int k) {
    unsigned int n = (k) & (0x1F);
    HWREG(SOC_AINTC_REGS + ENABLE3) = (1 << n);  
}
void interrupt_enable_GPIO3(int k) {
    unsigned int n = (k) & (0x1F);
    HWREG(SOC_AINTC_REGS + ENABLE1) = (1 << n);  
}

void interrupt_enable_timer7() {
    unsigned n = (0x5F) & (0x1F);     
    HWREG(SOC_AINTC_REGS + ENABLE2) = (1 << n);  
}
void ISR_Handler(void) {
    
    unsigned int intrNum;
    intrNum = HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) & (0x7F);

    if (intrNum == 98 || intrNum == 62) {
        gpioIsr1();
    } 

    if (intrNum == 99) {
        gpioIsr2();
    }

    if (intrNum == 95) {
        DMTimerIsr();
    }
    HWREG(SOC_AINTC_REGS + INTC_CONTROL) = 0x1;
    
}

