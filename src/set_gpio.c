#include "../inc/includes.h"

// define um pino como entrada/sáida
void set_gpio(volatile int offset) {
    HWREG(SOC_CONTROL_REGS + offset) = MUX_MODE7;

}
// define um botão como pull_down
void set_gpio_input(volatile int offset, int mu) {
    HWREG(SOC_CONTROL_REGS + offset) = (1<<5)|(mu<<4)| MUX_MODE7; 
}
// define a direção de um pino como sáida
void set_output(volatile int base, volatile int offset, int pin) {
    HWREG(base + offset) &= ~(1 << pin );
}
// define um pino como entrada
void set_input(volatile int base, volatile int offset, int pin) {
    HWREG(base + offset) |= (1 << pin );
}

// verifica se há corrente passando pelo botao 
bool get_dataIn(volatile int base, volatile int pin) {
    return (HWREG(base + CONF_DATAIN ) & (1 << pin)) != 0;
    
}
