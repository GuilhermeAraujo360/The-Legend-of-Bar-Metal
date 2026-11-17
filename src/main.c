#include "../inc/includes.h"

int main(void) {

init_all();

// ==================== LEDS INTERNOS ===========================
set_gpio(CONF_GPMC_A5);
set_gpio(CONF_GPMC_A6);
set_gpio(CONF_GPMC_A7);
set_gpio(CONF_GPMC_A8);

set_output(SOC_GPIO_1_REGS, GPIO_OE, 21);
set_output(SOC_GPIO_1_REGS, GPIO_OE, 22);
set_output(SOC_GPIO_1_REGS, GPIO_OE, 23);
set_output(SOC_GPIO_1_REGS, GPIO_OE, 24);
// ===============================================================

while (1) {
    menu();
}

return 0;

//     tftp 0x80000000 download.bin && go 0x80000000                   
}
