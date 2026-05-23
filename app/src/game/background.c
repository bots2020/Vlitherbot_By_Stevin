#include "background.h"
#include "game.h"
#include "../rendering/sprite_renderer.h"

static const char* const BG_PATHS[BG_COUNT] = {
    [BG_CLASSIC] = "app/res/textures/background.jpg",
    [BG_BLACK] = NULL,
    [BG_BG45] = "app/res/textures/backgrounds/bg45.jpg",
    [BG_GRID] = "app/res/textures/backgrounds/grid.jpg",
    [BG_METALGRID] = "app/res/textures/backgrounds/metalgrid.jpg",
    [BG_NOISE] = "app/res/textures/backgrounds/noise.jpg",
};

static const char* const BG_LABELS[BG_COUNT] = {
    "Classic",
    "Black",
    "BG45",
    "Grid",
    "Metal grid",
    "Noise",
};

const char* backgrounds_label(int index) {
  if (index < 0 || index >= BG_COUNT) return BG_LABELS[0];
  return BG_LABELS[index];
}

bool backgrounds_is_black(int index) { return index == BG_BLACK; }

void backgrounds_apply(game* g, int index) {
  if (index < 0) index = 0;
  if (index >= BG_COUNT) index = BG_COUNT - 1;
  g->settings_instance.bg_index = index;

  if (backgrounds_is_black(index)) {
    g->bg_tex = g->bg_textures[BG_CLASSIC];
    return;
  }

  ig_texture* tex = g->bg_textures[index];
  if (!tex && BG_PATHS[index]) {
    g->bg_textures[index] =
        ig_context_texture_create_from_file(g->icontext, BG_PATHS[index]);
    tex = g->bg_textures[index];
  }
  if (!tex) tex = g->bg_textures[BG_CLASSIC];
  g->bg_tex = tex;
  sprite_renderer_set_texture(g->renderer->bg_renderer, tex, g->icontext);
}

void backgrounds_cycle(game* g) {
  int next = g->settings_instance.bg_index + 1;
  if (next >= BG_COUNT) next = 0;
  backgrounds_apply(g, next);
}

void backgrounds_init(game* g) {
  for (int i = 0; i < BG_COUNT; i++) {
    if (i == BG_BLACK || g->bg_textures[i] || !BG_PATHS[i]) continue;
    g->bg_textures[i] =
        ig_context_texture_create_from_file(g->icontext, BG_PATHS[i]);
  }
  if (!g->bg_textures[BG_CLASSIC])
    g->bg_textures[BG_CLASSIC] = ig_context_texture_create_from_file(
        g->icontext, "app/res/textures/background.jpg");

  int idx = g->settings_instance.bg_index;
  if (idx < 0 || idx >= BG_COUNT) idx = BG_CLASSIC;
  backgrounds_apply(g, idx);
}

void backgrounds_destroy(game* g) {
  for (int i = 0; i < BG_COUNT; i++) {
    if (!g->bg_textures[i]) continue;
    ig_context_texture_destroy(g->icontext, g->bg_textures[i]);
    g->bg_textures[i] = NULL;
  }
  g->bg_tex = NULL;
}
