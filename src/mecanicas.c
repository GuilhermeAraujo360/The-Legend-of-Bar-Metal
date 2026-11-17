#include "../inc/includes.h"


/* ============================================================
 * Definições das variáveis globais (movidas do .h para cá)
 * ============================================================ */

volatile bool defeat = false;

Player jogador = {
    .x     = 5,
    .y     = 5,
    .hp    = 200,
    .atk   = 1000,
    .def   = 200,
    .xp    = 5,
    .level = 1    
};
// monstros regulares
Monster slime   = {"Slime",   10, 2, 5,  slimes,   SLIME_HEIGHT};
Monster rato    = {"Rato",     8, 1, 4,  ratos,    RATO_HEIGHT};
Monster morcego = {"Morcego", 12, 3, 8,  morcegos, MORCEGO_HEIGHT};

Monster aaaaaah = {"esqueleto", 20, 8, 10, esqueletov2, ESQUELETOV2_HEIGHT};
Monster Empusa = {"EmpusaQueen", 30, 12, 50, empusa, EMPUSA_HEIGHT};
Monster Louva = {"Louva-Deus",10, 5, 10, inseto1, INSETO1_HEIGHT };
Monster Cell = {"Cell", 100, 2, 20, insetov2, INSETOV2_HEIGHT};

// bosses
Monster The_Professor = {"The Professor", 1200, 500, 1, chico, CHICO_HEIGHT};
Monster Nosfetaru = {"Nosfetaru", 80, 40, 800, boss_v2, BOSS_V2_HEIGHT};
Monster Zombie = {"Crimson Head",20, 10, 300, zombie, ZOMBIE_HEIGHT};
Monster Aranha = {"Carlos Gabriel", 50, 35, 250, carlos_gabriel, CARLOS_GABRIEL_HEIGHT};
Monster Fofinho = {"Sammuel, o fofinho",70, 40, 120, fofinho, FOFINHO_HEIGHT};
Monster Richard = {"Richard Kings", 100, 120, 300, richard_kings, RICHARD_KINGS_HEIGHT};

Monster inimigo_atual;
Monster boss_atual;

int xp_necessaria[LEVEL_MAX] = {
    0,    /* level 1  */
    10,   /* level 2  */
    30,   /* level 3  */
    60,   /* level 4  */
    100,  /* level 5  */
    150,  /* level 6  */
    210,  /* level 7  */
    280,  /* level 8  */
    360,  /* level 9  */
    500,  /* level 10 */
};


void menu(void)
{
    /* Reseta estado do jogo para nova partida */
    defeat = false;
    jogador.x     = 5;
    jogador.y     = 5;
    jogador.hp    = 200;
    jogador.atk   = 1000;
    jogador.def   = 200;
    jogador.xp    = 5;
    jogador.level = 1;

    /* Limpa flags de movimento que possam ter sobrado */
    left = right = up = down = false;
    press1 = false;

    print_logo();
    print_string("\n\r");
    print_string("Aperte o botao para iniciar o jogo!\n\r");

    /* Aguarda press1 */
    while (!press1);
    press1 = false;

    jogo();
}



void ganhar_xp(Monster inimigo)
{
    jogador.xp += inimigo.exp;
    verifica_level_up();
}

void verifica_level_up(void)
{
    while(jogador.level < LEVEL_MAX &&
          jogador.xp >= xp_necessaria[jogador.level])
    {
        jogador.level++;
        jogador.hp  += 5;
        jogador.atk += 2;
        jogador.def += 1;
    }
    print_string("Você elevou de nível!\n\r");
}

Monster gera_monstro(void) {

    int r = rand() % 100;

    if (r < 35)          // 35%
        return slime;

    else if (r < 60)     // 25%
        return rato;

    else if (r < 75)     // 15%
        return morcego;

    else if (r < 87)     // 12%
        return Louva;

    else if (r < 94)     // 7%
        return aaaaaah;

    else if (r < 98)     // 4%
        return Empusa;

    else                 // 2%
        return Cell;
}


Monster gerar_boss(void) {

    int k = rand() % 100;

    if (k < 30)          // 30%
        return Zombie;

    else if (k < 52)     // 22%
        return Fofinho;

    else if (k < 70)     // 18%
        return Aranha;

    else if (k < 84)     // 14%
        return Nosfetaru;

    else if (k < 95)     // 11%
        return Richard;

    else                 // 5%
        return The_Professor;
}


int turno_jogador(void)
{
    if(press1)
    {
        press1 = false;
        inimigo_atual.hp -= jogador.atk;
        return 0;
    }

    return 0;
}



void processa_fim_batalha(void)
{
    if(jogador.hp <= 0)
    {
        defeat = true;
        print_game_over();
        return;
    }

    if(inimigo_atual.hp <= 0)
    {
        ganhar_xp(inimigo_atual);
    }
}



int turno_jogador_boss(void)
{
    if (press1)
    {
        press1 = false;
        boss_atual.hp -= jogador.atk;
        return 0;
    }

    return 0;
}


void turno_inimigo_normal(void)
{
    int dano = inimigo_atual.atk - jogador.def;
    if (dano < 1) dano = 1;
    jogador.hp -= dano;
}


void turno_boss(void)
{
    int dano = boss_atual.atk - jogador.def;
    if (dano < 1) dano = 1;
    jogador.hp -= dano;
}


void processa_fim_batalha_boss(void)
{
    if (jogador.hp <= 0)
    {
        defeat = true;
        print_game_over();
        
        return;
    }

    if (boss_atual.hp <= 0)
    {
        jogador.xp += boss_atual.exp;
        verifica_level_up();
        print_string("Boss derrotado!\n\r");
    }
}
