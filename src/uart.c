#include "../inc/uart.h"
#include "../inc/hw_types.h"
#include "../inc/soc_AM335x.h"

void reset() {
    
    HWREG(uart_base + SYSC) |= (1 << 1);
    

    while (!(HWREG(uart_base + SYSS) & (1 << 0)));
}

void init_uart0() {
    //  clock + pinmux
    HWREG(base_wkup + uart0) = 0x2;
    HWREG(SOC_CONTROL_REGS + uart0_RXD) = 0x30;
    HWREG(SOC_CONTROL_REGS + uart0_TXD) = 0x10;

    // desabilita UART antes de configurar
    HWREG(uart_base + MDR1) = 0x7; // 111 

    //  reset
    reset();

    //  modo config B acessa EFR
    HWREG(uart_base + uart0_LCR) = 0xBF; // 10111111
    // habilita escrita em MCR, FCR e IER 
    HWREG(uart_base + EFR) |= (1 << 4);  

    //  modo config A  acessa MCR
    HWREG(uart_base + uart0_LCR) = 0x80; // 10000000
    HWREG(uart_base + MCR) |= (1 << 6);    // TCR e TLR enable

    //  configura FIFO
    HWREG(uart_base + uart0_FCR) = 0x07; // // 111

    // baund rate 
    HWREG(uart_base + uart0_LCR) = 0x83;   // 10000011
    HWREG(uart_base + uart0_DLL) = 26;     // 115200 baud
    HWREG(uart_base + uart0_DLH) = 0;     // parte 0x0 de 0x001A

    //  tamanho a ser transmitido 
    HWREG(uart_base + uart0_LCR) = 0x03;

    // ligando uart novamente
    HWREG(uart_base + MDR1) = 0x0;
}

void Is_Transmiting() {
    while (!(LSR & (1 << 5)));
}

void Is_Receiving() {
    while (!((LSR) & (1 << 0)));
}

void print_char(char c) {
    Is_Transmiting(); // Espera até THR Empty = 1
    THR = c;                   // Escreve o caractere no buffer de transmissão
}

//string
void print_string(const char *s) {
    while (*s) print_char(*s++);           // Envia cada caractere até encontrar '\0'
}
