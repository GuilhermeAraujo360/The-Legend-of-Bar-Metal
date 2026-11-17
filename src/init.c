#include "../inc/includes.h"

/*==========================================================================*/
/* CONFIGURAÇÕES GERAIS */
void init_all() {
    chocolate();
    print_string("the dog is gone\n\r");
    ckmSetCLKModuleRegister();
    print_string("o timer ligou\n\r");
    set_module1();
    set_module3();
    set_module2();
    init_uart0();
    print_string("clock e uart ok\n\r");
    IntAINTCInit();
    print_string("AINTC ok\r\n");
    interrupt_enable_GPIO1(98);
    interrupt_enable_GPIO1(99);
    interrupt_enable_GPIO3(62);
    print_string("gpio ok");
    habilitar_interrupcao_GPIO1_b1();
    habilitar_interrupcao_GPIO1_b2();
    srand_init();

    print_string("HABILITAR OK");
    print_string("GPIO3 ok\r\n");
    print_string("depois\n");
    interrupt_enable_timer7();
    print_string("Timer7 ok\r\n");
  //  conf_button();
    
    conf_led();

    print_string("This party is getting crazy!\r\n");
    print_string("LETS ROCK!\n\r");
}
/*============================================================================*/
