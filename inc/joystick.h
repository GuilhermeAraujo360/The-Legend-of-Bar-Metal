#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdbool.h>

/* Flags de movimento — setadas pelas ISRs */
extern volatile bool left;
extern volatile bool right;
extern volatile bool up;
extern volatile bool down;
extern volatile bool press1;

/* HP inicial dos inimigos — para cálculo percentual dos LEDs */
extern int hp_inicial_normal;
extern int hp_inicial_boss;

/* Configuração de hardware */
void conf_button(void);
void conf_led(void);

/* Visualização de HP via LEDs */
void hp_led_normal(void);
void hp_led_boss(void);
void led_off(void);
/* Habilitação de interrupções GPIO */
void habilitar_interrupcao_GPIO1_b1(void);
void habilitar_interrupcao_GPIO1_b2(void);

/* ISRs */
void gpioIsr1(void);
void gpioIsr2(void);

#endif /* _JOYSTICK_H_ */
