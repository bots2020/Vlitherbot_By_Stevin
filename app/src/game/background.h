#ifndef BACKGROUND_H
#define BACKGROUND_H

typedef struct game game;

#define BG_COUNT 6

#define BG_CLASSIC 0
#define BG_BLACK 1
#define BG_BG45 2
#define BG_GRID 3
#define BG_METALGRID 4
#define BG_NOISE 5

void backgrounds_init(game* g);
void backgrounds_destroy(game* g);
void backgrounds_apply(game* g, int index);
void backgrounds_cycle(game* g);
const char* backgrounds_label(int index);
bool backgrounds_is_black(int index);

#endif
