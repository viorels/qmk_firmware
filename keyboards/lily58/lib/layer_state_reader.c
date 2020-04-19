
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_COLEMAK 2
#define L_LOWER 4
#define L_RAISE 8
#define L_ADJUST 16
#define L_ADJUST_TRI 28

char layer_state_str[24];

const char *read_layer_state(void) {
  // get_highest_layer? https://docs.qmk.fm/#/feature_oled_driver
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    break;
  case L_COLEMAK:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
