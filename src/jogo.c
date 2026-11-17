#include "../inc/includes.h"

void jogo(void) {


    mapa_print();
    while (1) {
        while (!(left || right || up || down));

        move_player_from_joystick();

        char tile = mapa[jogador.y][jogador.x];

        if (tile == ';') {
            batalha();

            /* Limpa flags que possam ter sobrado da batalha */
            left = right = up = down = false;
            press1 = false;

            /* Verifica derrota ANTES de redesenhar o mapa */
            if (defeat)
                return;

            mapa_print();

        } else if (tile == '$') {
            batalha_boss();

            /* Limpa flags que possam ter sobrado da batalha */
            left = right = up = down = false;
            press1 = false;

            /* Verifica derrota ANTES de redesenhar o mapa */
            if (defeat)
                return;

            mapa_print();

        }
    }
}


/* ============================================================
 * Batalha normal 
 * ============================================================ */
void batalha(void) {
    
    inimigo_atual = gera_monstro();
    hp_led_normal();

    int fugiu = 0;

    while (jogador.hp > 0 && inimigo_atual.hp > 0)
    {
        print_string("\033[2J\033[H");
        draw_sprite(inimigo_atual.sprite, inimigo_atual.sprite_height);
        print_string("\n\r");
        print_string(inimigo_atual.nome);
        print_string("\n\r");
        print_string("1 -> ATACAR\n\r");

        while (!press1);

        fugiu = turno_jogador();

        if (fugiu)
            return;

        if (inimigo_atual.hp <= 0)
            break;

        turno_inimigo_normal();
    }
    led_off();
    processa_fim_batalha();
}


/* ============================================================
 * Batalha de boss 
 * ============================================================ */
void batalha_boss(void) {

    boss_atual = gerar_boss();
    hp_led_boss();

    int fugiu = 0;

    while (jogador.hp > 0 && boss_atual.hp > 0)
    {
        print_string("\033[2J\033[H");
        draw_sprite(boss_atual.sprite, boss_atual.sprite_height);
        print_string("\n\r");
        print_string(boss_atual.nome);
        print_string("\n\r");
        print_string("1 -> ATACAR\n\r");

        while (!press1);

        fugiu = turno_jogador_boss();

        if (fugiu)
            return;

        if (boss_atual.hp <= 0)
            break;

        turno_boss();
    }
    led_off();
    processa_fim_batalha_boss();
}
