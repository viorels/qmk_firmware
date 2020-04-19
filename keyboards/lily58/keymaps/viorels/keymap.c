#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space/3/       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  LCTL_T(KC_BSPC), KC_A, KC_S, KC_D,  KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                             KC_LGUI, KC_LALT,LOWER, LT(_ADJUST, KC_SPC), KC_ENT,  RAISE,   KC_BSPC, KC_RALT \
),
/* Colemak
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space/3/       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
  _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_K,    KC_M,    _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   [  |   ]  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |   _  |   +  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |MOUSE |      |      |-------|    |-------|      |   -  |   =  |   {  |   }  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE | DEL  | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_F12, \
  _______, _______, KC_MS_BTN2, KC_MS_UP, KC_MS_BTN1, KC_MS_WH_UP,                   XXXXXXX, KC_UNDS, KC_PLUS,KC_LPRN, KC_RPRN, KC_PIPE,\
  _______, KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN, _______, _______, XXXXXXX, KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, RSFT_T(KC_BSLS), \
                             _______, _______, _______, _______, _______,  _______, KC_DEL, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |PrintS|Scroll|Pause |Insert|                    | PgUp | Home |  Up  |  End |  Del |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| PgDn | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste|      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  XXXXXXX, \
  _______, _______, _______, _______, _______, _______,                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, \
  _______, LCTL(KC_Z), LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V), _______,  _______, _______,  _______, _______, _______,  _______, _______, _______, \
                             _______, _______, _______,  _______, _______,  _______, KC_BSPC, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |QWERTY|Colema|      |      |      |                    |   /  |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | VAL+ | SAT+ | HUE+ |RGB ON|      |-------.    ,-------|   *  |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | CAPS | VAL- | SAT- | HUE- | MODE |      |-------|    |-------| CALC |   1  |   2  |   3  |   .  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |  0   |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, QWERTY,  COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS, XXXXXXX, \
  XXXXXXX, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, XXXXXXX,                   KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS, XXXXXXX, \
  KC_CAPS, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, KC_1,    KC_2,    KC_3,    KC_DOT,  XXXXXXX, \
                             _______, _______, _______, _______, _______, KC_0,    _______, _______ \
  ),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
  // switch(biton32(layer_state)) {
  if (IS_LAYER_ON(_LOWER)) {
    // undo/redo
    register_code(KC_LCTL);
    if (clockwise) {
      register_code(KC_LSFT);
      tap_code(KC_Z);
      unregister_code(KC_LSFT);
    }
    else {
      tap_code(KC_Z);
    }
    unregister_code(KC_LCTL);
  }
  else if (IS_LAYER_ON(_RAISE)) {
    // nothing on RAISE layer, unconfortable to use
  }
  else if (IS_LAYER_ON(_ADJUST)) {
    // volume up/down
    #ifdef EXTRAKEY_ENABLE
    clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
    #endif
  }
  else {  // default layer
    // change desktop ctrl-alt-up/down (also move window with shift)
    if ((get_mods() & MOD_BIT(KC_LCTL)) && (get_mods() & MOD_BIT(KC_LALT))) {
      clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
    // alt-tab for windows, ctrl-tab for browser tabs (XOR/(!a != !b), only ONE of alt/ctrl pressed)
    else if (!(get_mods() & MOD_BIT(KC_LCTL)) != !(get_mods() & MOD_BIT(KC_LALT))) {
      if (clockwise) {
          tap_code(KC_TAB);
      } else {
          register_code(KC_LSFT);
          tap_code(KC_TAB);
          unregister_code(KC_LSFT);
      }
    }
    // super-tab changes between windows of the same app
    else if (get_mods() & MOD_BIT(KC_LGUI)) {
      if (clockwise) {
          tap_code(KC_GRAVE);
      } else {
          register_code(KC_LSFT);
          tap_code(KC_GRAVE);
          unregister_code(KC_LSFT);
      }
    }
    // mouse wheel by default
    else {
      if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_DOWN);
        #else
          tap_code(KC_PGDN);
        #endif
      } else {
        #ifdef MOUSEKEY_ENABLE
          tap_code(KC_MS_WH_UP);
        #else
          tap_code(KC_PGUP);
        #endif
      }
    }
  }
}
#endif