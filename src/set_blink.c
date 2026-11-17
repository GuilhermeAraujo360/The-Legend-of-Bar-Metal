#include "../inc/includes.h"



void on( volatile int base, volatile int pin) {
    HWREG(base + GPIO_SETDATAOUT) = (1 << pin);
    
}
void off(volatile int base, volatile int pin) {
    HWREG(base + GPIO_CLEARDATAOUT) = (1 << pin);
    
}

void blink(volatile int base, volatile int pin, volatile int time) {
    on(base, pin);
    msDelayInterrupt(time);
    off(base, pin);
    msDelayInterrupt(time);
}