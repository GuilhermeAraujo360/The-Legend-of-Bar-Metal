#include "../inc/set_clock.h"
#include "../inc/soc_AM335x.h"
#include "../inc/hw_types.h"

void set_module1() {
    HWREG(SOC_CM_PER_REGS + module1 ) |= (1<<18) | (0x2 << 0);
}

void set_module2() {
    HWREG(SOC_CM_PER_REGS + module2 ) |= (1<<18) | (0x2 << 0);
}

void set_module3() {
    HWREG(SOC_CM_PER_REGS + module3 ) |= (1<<18) | (0x2 << 0);
}
