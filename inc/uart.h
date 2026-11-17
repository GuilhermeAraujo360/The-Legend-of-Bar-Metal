#ifndef _UART_H_
#define _UART_H_

#include "../inc/hw_types.h"

#define base_wkup (0x44E00400) // ligar clock
#define uart0 (0x0B4) // offset do uart0 para o clock

#define uart_base (0x44E09000) // base do uart0
#define uart0_RXD (0x970) 
#define uart0_TXD (0x974)
#define uart0_LSR (0x014)

#define uart0_THR (0x000)
#define uart0_RHR (0x000)

#define uart0_LCR (0x00C)
#define uart0_DLL (0x000)
#define uart0_DLH (0x004)
#define uart0_FCR (0x008)

#define SYSC (0x054)
#define SYSS (0x058)
#define MCR  (0x010)
#define MDR1 (0x020)
#define EFR  (0x008)  // acessível quando LCR = 0xBF

#define LSR (HWREG(uart_base + uart0_LSR))
#define THR (HWREG(uart_base + uart0_THR))
#define RHR (HWREG(uart_base + uart0_RHR))

void print_char(char a);
void print_string(const char *s);
int Baud_Rate(int bound_rate);
void reset();
void init_uart0();
#endif 