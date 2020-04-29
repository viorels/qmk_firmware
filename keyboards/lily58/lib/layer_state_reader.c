
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_QWERTY (1 << 0)
#define L_COLEMAK (1 << 1)
#define L_LOWER (1 << 2)
#define L_RAISE (1 << 3)
#define L_ADJUST (1 << 4)
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)
#define L_ADJUST_TEMP (L_ADJUST | L_LOWER)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    if (default_layer_state == L_QWERTY)
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    else if (default_layer_state == L_COLEMAK)
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
  case L_ADJUST_TEMP:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

/*
  snprintf(layer_state_str, sizeof(layer_state_str), "Layer: 00000");
  unsigned int n = layer_state;
  int i = 7; // should be sizeof(layer_state_str) - 5 - 1;
  while (n) {
    if (n & 1)
        layer_state_str[i] = '1';
    else
        layer_state_str[i] = '0';
    i++;
    n >>= 1;
  }
*/

  return layer_state_str;
}
