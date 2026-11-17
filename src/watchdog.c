#include "../inc/watchdog.h"
#include "../inc/soc_AM335x.h"
#include "../inc/hw_types.h"

void chocolate(){
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0xAAAA;
	while(HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1 << 4));
	HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0x5555;
	while(HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1 << 4));
}
