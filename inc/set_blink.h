#ifndef _SET_BLINK_H_
#define _SET_BLINK_H_
#include "hw_types.h"
#include "module_config.h"


void on(int base, int pin);
void off(int base, int pin);
void blink(volatile int base, volatile int pin, volatile int time);

#endif