#include "../inc/includes.h"

static unsigned int TIMER_1US_COUNT = 24000;  
volatile bool flag_timer = false;

/*habilita o clock para DMTIMEER7 TRM 8.1.12.1.25*/
void ckmSetCLKModuleRegister()
{
        // ligar o clocck
    HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) =
        CM_PER_TIMER7_CLKCTRL_MODULEMODE_ENABLE;

    while ((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) &
            CM_PER_TIMER7_CLKCTRL_MODULEMODE_DISABLE) !=
            CM_PER_TIMER7_CLKCTRL_MODULEMODE_ENABLE)
    {
    }
    //ativar o modo posted
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TSICR) |= (1 << 2);

    while (HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TWPS) &
        DMTIMER_TWPS_W_PEND_TCLR);
    // parar o timer caso o contador congele 
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST;

    while (HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TWPS) &
       DMTIMER_TWPS_W_PEND_TCRR);
    // zerar o timer 
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) = 0x00000000;

    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TLDR) = 0x00000000;
}


unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd) {
    return (HWREG(baseAdd +DMTIMER_TWPS));
}



#define DMTimerWaitForWrite(reg, baseAdd) \
    while(DMTimerWritePostedStatusGet(baseAdd) & (reg));

void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter) {
    DMTimerWaitForWrite(DMTIMER_TWPS_W_PEND_TCRR , baseAdd);
    HWREG(baseAdd + DMTIMER_TCRR) = counter;
}


unsigned int DMTimerCounterGet(unsigned int baseAdd) {
    DMTimerWaitForWrite(DMTIMER_TWPS_W_PEND_TCRR , baseAdd);
    return (HWREG(baseAdd + DMTIMER_TCRR));
}
   
void DMTimerEnable(unsigned int baseAdd) {
    DMTimerWaitForWrite(DMTIMER_TWPS_W_PEND_TCLR, baseAdd);
    HWREG(baseAdd + DMTIMER_TCLR) |= DMTIMER_TCLR_ST;
}

void DMTimerDisable(unsigned int baseAdd) {
    DMTimerWaitForWrite(DMTIMER_TWPS_W_PEND_TCLR, baseAdd);
    HWREG(baseAdd + DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST;
}


void uDelay (unsigned int us) {
    
    unsigned int ticks_needed = us * TIMER_1US_COUNT;

    DMTimerCounterSet(SOC_DMTIMER_7_REGS, 0);

    DMTimerEnable(SOC_DMTIMER_7_REGS);

    while(DMTimerCounterGet(SOC_DMTIMER_7_REGS)<ticks_needed);

    DMTimerDisable(SOC_DMTIMER_7_REGS);

    
}


void msDelayInterrupt(unsigned int ms) {
    unsigned int ticks_needed_2 = TIMER_OVERFLOW - (ms * TIMER_1MS_COUNT);

    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR) = ticks_needed_2;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TLDR) = ticks_needed_2;

    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = DMTIMER_IRQ_OVF_IT_FLAG;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCLR) |= DMTIMER_TCLR_ST;

   
    while(!(HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS_RAW) & DMTIMER_IRQ_OVF_IT_FLAG));

    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = DMTIMER_IRQ_OVF_IT_FLAG;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_SET) = DMTIMER_IRQ_OVF_IT_FLAG;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCLR) &= ~DMTIMER_TCLR_ST;
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQENABLE_CLR) = DMTIMER_IRQ_OVF_IT_FLAG; // @
}
 

void DMTimerIsr(void) {
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = DMTIMER_IRQ_OVF_IT_FLAG;
    flag_timer = true;
}




static uint32_t lfsr_state;

void srand_init(void) {
    uint32_t seed = HWREG(SOC_DMTIMER_7_REGS + DMTIMER_TCRR);
    lfsr_state = seed ? seed : 0xDEADBEEFu;
}

int rand(void) {
    uint32_t bit = lfsr_state & 1u;
    lfsr_state >>= 1;
    if (bit) lfsr_state ^= 0xB4BCD35Cu;
    return (int)(lfsr_state & 0x7FFFFFFFu);
}