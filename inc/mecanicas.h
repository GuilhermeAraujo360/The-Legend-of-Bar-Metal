#ifndef _MECANICAS_H_
#define _MECANICAS_H_

/* --------------------------------------------------------
 * Flag de derrota
 * -------------------------------------------------------- */
extern volatile bool defeat;

/* --------------------------------------------------------
 * Structs
 * -------------------------------------------------------- */
typedef struct {
    int x;
    int y;
    int hp;
    int atk;
    int def;
    int xp;
    int level;
} Player;

typedef struct {
    char nome[20];
    int  hp;
    int  atk;
    int  exp;
    const char **sprite;
    int  sprite_height;
} Monster;

/* --------------------------------------------------------
 * Variáveis globais — extern (definidas em mecanicas.c)
 * -------------------------------------------------------- */
extern Player  jogador;
extern Monster slime;
extern Monster rato;
extern Monster morcego;
extern Monster inimigo_atual;
extern Monster boss_atual;

/* Bosses */
extern Monster The_Professor;
extern Monster Nosfetaru;
extern Monster Zombie;
extern Monster Aranha;

/* --------------------------------------------------------
 * Tabela de XP por nível
 * -------------------------------------------------------- */
#define LEVEL_MAX 10

extern int xp_necessaria[LEVEL_MAX];

/* --------------------------------------------------------
 * Protótipos
 * -------------------------------------------------------- */
void    menu(void);

void    ganhar_xp(Monster inimigo);
void    verifica_level_up(void);
Monster gera_monstro(void);
Monster gerar_boss(void);

/* Turnos e batalha — versões separadas para normal e boss */
int     turno_jogador(void);
int     turno_jogador_boss(void);
void    turno_inimigo_normal(void);
void    turno_boss(void);

void    processa_fim_batalha(void);
void    processa_fim_batalha_boss(void);

/* Funções de batalha chamadas em jogo.c */
void    batalha(void);
void    batalha_boss(void);

#endif /* _MECANICAS_H_ */
