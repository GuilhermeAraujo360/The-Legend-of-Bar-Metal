#ifndef _SET_GPIO_H
#define _SET_GPIO_H
#include <stdbool.h>


extern volatile bool botao1;
extern volatile bool botao2;

void set_gpio(volatile int offset);
void set_output(volatile int base, volatile int offset, int pin);
void set_input(volatile int base, volatile int offset, int pin);
bool get_dataIn(volatile int base, volatile int pin);
void set_gpio_input(volatile int offset, int mu);

#endif

