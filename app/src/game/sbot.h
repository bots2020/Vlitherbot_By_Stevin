#ifndef SBOT_H
#define SBOT_H

#include <stdbool.h>

// Implementation of Saya's bot: https://github.com/saya-0x0efe/Slither.io-bot
// Ported from vlither 2.5

typedef struct game game;

typedef struct sbot {
  struct {
    float xm;
    float ym;
    bool accel;
  } output;
} sbot;

void sbot_init(game* g);
void sbot_go(game* g);
void sbot_destroy(game* g);

#endif
