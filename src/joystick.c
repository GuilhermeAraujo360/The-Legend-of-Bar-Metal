#include "../inc/includes.h"

volatile bool left   = false;
volatile bool right  = false;
volatile bool up     = false;
volatile bool down   = false;
volatile bool press1 = false;


int hp_inicial_normal = 0;
int hp_inicial_boss   = 0;

void conf_led(void) {
    /* Verdes */
    set_gpio(CONF_GPMC_AD13);
    set_output(SOC_GPIO_1_REGS, GPIO_OE, 13);

    set_gpio(CONF_GPMC_AD15);
    set_output(SOC_GPIO_1_REGS, GPIO_OE, 15);

    /* Amarelos */
    set_gpio(CONF_GPMC_CSN0);
    set_output(SOC_GPIO_1_REGS, GPIO_OE, 29);

    set_gpio(conf_gpmc_a0);
    set_output(SOC_GPIO_1_REGS, GPIO_OE, 16);

    /* Vermelhos */
    set_gpio(conf_gpmc_clk);
    set_output(SOC_GPIO_2_REGS, GPIO_OE, 1);

    set_gpio(CONF_GPMC_AD14);
    set_output(SOC_GPIO_1_REGS, GPIO_OE, 14);
}


void hp_led_normal(void) {
    if (hp_inicial_normal == 0)
        hp_inicial_normal = inimigo_atual.hp;

    int hp  = inimigo_atual.hp;
    int max = hp_inicial_normal;

    /* Acende tudo */
    on(SOC_GPIO_1_REGS, 13);
    on(SOC_GPIO_1_REGS, 15);
    on(SOC_GPIO_1_REGS, 29);
    on(SOC_GPIO_1_REGS, 16);
    on(SOC_GPIO_2_REGS, 1);
    on(SOC_GPIO_1_REGS, 14);

    if (hp <= 0) {
        /* Apaga tudo */
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
        off(SOC_GPIO_1_REGS, 29);
        off(SOC_GPIO_1_REGS, 16);
        off(SOC_GPIO_2_REGS, 1);
        off(SOC_GPIO_1_REGS, 14);
    } else if (hp * 3 <= max) {
        /* HP <= 33%: apaga verdes + amarelos */
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
        off(SOC_GPIO_1_REGS, 29);
        off(SOC_GPIO_1_REGS, 16);
    } else if (hp * 3 <= max * 2) {
        /* HP <= 66%: apaga só verdes */
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
    }
}

void hp_led_boss(void) {
    if (hp_inicial_boss == 0)
        hp_inicial_boss = boss_atual.hp;

    int hp  = boss_atual.hp;
    int max = hp_inicial_boss;

    on(SOC_GPIO_1_REGS, 13);
    on(SOC_GPIO_1_REGS, 15);
    on(SOC_GPIO_1_REGS, 29);
    on(SOC_GPIO_1_REGS, 16);
    on(SOC_GPIO_2_REGS, 1);
    on(SOC_GPIO_1_REGS, 14);

    if (hp <= 0) {
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
        off(SOC_GPIO_1_REGS, 29);
        off(SOC_GPIO_1_REGS, 16);
        off(SOC_GPIO_2_REGS, 1);
        off(SOC_GPIO_1_REGS, 14);
    } else if (hp * 3 <= max) {
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
        off(SOC_GPIO_1_REGS, 29);
        off(SOC_GPIO_1_REGS, 16);
    } else if (hp * 3 <= max * 2) {
        off(SOC_GPIO_1_REGS, 13);
        off(SOC_GPIO_1_REGS, 15);
    }
}


void led_off(void) {
    off(SOC_GPIO_1_REGS, 13);
    off(SOC_GPIO_1_REGS, 15);
    off(SOC_GPIO_1_REGS, 29);
    off(SOC_GPIO_1_REGS, 16);
    off(SOC_GPIO_2_REGS, 1);
    off(SOC_GPIO_1_REGS, 14);
}

void habilitar_interrupcao_GPIO1_b1(void) {

    /* --- GPIO1_28 : LEFT --- */
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE)  |= (1 << 28);
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCINGTIME)  = 0xFF;
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT)   |= (1 << 28);
    HWREG(SOC_GPIO_1_REGS + GPIO_FALLINGDETECT)  &= ~(1 << 28);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0)     = (1 << 28); /* limpa pending */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0)|= (1 << 28);
    

    /* --- GPIO1_17 : B1 --- */
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE)  |= (1 << 17);
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCINGTIME)  = 0xFF;
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT)   |= (1 << 17);
    HWREG(SOC_GPIO_1_REGS + GPIO_FALLINGDETECT)  &= ~(1 << 17);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0)     = (1 << 17);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0)|= (1 << 17);

    HWREG(SOC_AINTC_REGS + CLEAR3) = (1 << 2);


    /* --- GPIO3_19 : UP --- */
     HWREG(SOC_GPIO_3_REGS + GPIO_DEBOUNCENABLE)  |= (1 << 19);
    HWREG(SOC_GPIO_3_REGS + GPIO_DEBOUNCINGTIME)  = 0xFF;
    HWREG(SOC_GPIO_3_REGS + GPIO_RISINGDETECT)   |= (1 << 19);
    HWREG(SOC_GPIO_3_REGS + GPIO_FALLINGDETECT)  &= ~(1 << 19);
    HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_0)     = (1 << 19);
    HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_SET_0)|= (1 << 19);

    /* --- GPIO3_21 : DOWN --- */
    HWREG(SOC_GPIO_3_REGS + GPIO_DEBOUNCENABLE)  |= (1 << 21);
    HWREG(SOC_GPIO_3_REGS + GPIO_DEBOUNCINGTIME)  = 0xFF;
    HWREG(SOC_GPIO_3_REGS + GPIO_RISINGDETECT)   |= (1 << 21);
    HWREG(SOC_GPIO_3_REGS + GPIO_FALLINGDETECT)  &= ~(1 << 21);
    HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_0)     = (1 << 21);
    HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_SET_0)|= (1 << 21);

    
    HWREG(SOC_AINTC_REGS + CLEAR1) = (1 << 30);
}


void habilitar_interrupcao_GPIO1_b2(void) {
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE)  |= (1 << 12);
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCINGTIME)  = 0xFF;
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT)   |= (1 << 12);
    HWREG(SOC_GPIO_1_REGS + GPIO_FALLINGDETECT)  &= ~(1 << 12);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_1)     = (1 << 12); /* limpa pending */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_1)|= (1 << 12);
    HWREG(SOC_AINTC_REGS + CLEAR3) = (1 << 3);
}


void gpioIsr1(void)
{
    unsigned int status1 = HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0);
    unsigned int status3 = HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_0);

    /* Limpa todos os pending antes de processar (write-1-to-clear) */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = status1;
    HWREG(SOC_GPIO_3_REGS + GPIO_IRQSTATUS_0) = status3;

    if (status1 & (1 << 28)) left   = true;  /* GPIO1_28 → LEFT  */
    if (status1 & (1 << 17)) press1 = true;  /* GPIO1_17 → B1    */
    if (status3 & (1 << 19)) up     = true;  /* GPIO3_19 → UP    */
    if (status3 & (1 << 21)) down   = true;  /* GPIO3_21 → DOWN  */
}


void gpioIsr2(void)
{
    unsigned int status1b = HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_1);
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_1) = status1b; /* limpa */

    if (status1b & (1 << 12)) right = true; /* GPIO1_12 → RIGHT */
}
