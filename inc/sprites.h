#ifndef _SPRITES_H_
#define _SPRITES_H_

extern const char *boss_v2[];
extern const char *chico[];
extern const char *carlos_gabriel[];
extern const char *zombie[];
extern const char *game_over[];
extern const char *richard_kings[];
extern const char *fofinho[];

extern const char *slimes[];
extern const char *ratos[];
extern const char *morcegos[];
extern const char *esqueletov2[];
extern const char *empusa[];
extern const char *inseto1[];
extern const char *insetov2[];

extern const char *logo[];


#define BOSS_V2_HEIGHT        31
#define CHICO_HEIGHT          61
#define CARLOS_GABRIEL_HEIGHT 22
#define ZOMBIE_HEIGHT         42
#define SLIME_HEIGHT           5
#define RATO_HEIGHT            5
#define MORCEGO_HEIGHT         5
#define LOGO_HEIGHT            9
#define GAME_OVER_SIZE        47
#define RICHARD_KINGS_HEIGHT  47
#define FOFINHO_HEIGHT 47
#define ESQUELETOV2_HEIGHT 29
#define EMPUSA_HEIGHT 44
#define INSETO1_HEIGHT 30
#define INSETOV2_HEIGHT 43
void draw_sprite(const char *sprite[], int height);
void print_game_over(void);
void print_logo(void);

#endif 
