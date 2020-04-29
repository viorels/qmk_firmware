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
  ADJUST,
  BITCOIN,
  JSARROW
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Ctrl/B|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |Ctrl/'|
 * |------+------+------+------+------+------|LOWER-L|    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  LCTL_T(KC_BSPC), KC_A, KC_S, KC_D,  KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT), \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, TT(_LOWER), XXXXXXX, KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                             KC_LGUI, KC_LALT, LOWER, LSFT_T(KC_SPC), KC_ENT, RAISE, KC_BSPC, KC_RALT \
),
/* Colemak
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Ctrl/B|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |Ctrl/'|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RAlt |
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
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | W_UP | Home |  Up  |  End | PgUp |                    | PgUp | Home |  Up  |  End |  Del | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | W_DN | Left | Down | Right| PgDn |-------.    ,-------| PgDn | Left | Down | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste|      |-------|    |-------|      | WLeft|      |WRight|      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |ADJUST|BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
  _______, KC_WH_U, KC_HOME, KC_UP,   KC_END,  KC_PGUP,                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  KC_F12, \
  _______, KC_WH_D, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN,                    KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, _______, \
  _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,  _______, _______,  XXXXXXX, C(KC_LEFT), XXXXXXX, C(KC_RIGHT), XXXXXXX, _______, \
                             _______, _______, _______,  _______, _______,  TT(_ADJUST), _______, KC_LALT \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |  |   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Ctrl/B|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   :  |   _  |   =  |   (  |   )  |  "   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   ^  |   &  |  {   |   }  |   ₿  |-------|    |-------|   *  |   +  |   -  |   [  |   ]  |Shft/\|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_COLN, KC_UNDS, KC_EQL,  KC_LPRN, KC_RPRN, KC_DQUO, \
  _______, KC_CIRC, KC_AMPR, KC_LCBR, KC_RCBR, BITCOIN, JSARROW, _______, KC_ASTR, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, RSFT_T(KC_BSLS), \
                             _______, _______, _______, _______, _______, RAISE,   _______, _______\
// UC(0x20bf) ₿
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | INS  |PrntSc|ScrlLk|Pause | CALC |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |QWERTY|Colema|      |      |      |                    |   /  |   7  |   8  |   9  |   -  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |BackSP| VAL+ | SAT+ | HUE+ |RGB ON| DEBUG|-------.    ,-------|   *  |   4  |   5  |   6  |   +  |      |
 * |------+------+------+------+------+------|       |    | MUTE  |------+------+------+------+------+------|
 * | CAPS | VAL- | SAT- | HUE- | MODE |      |-------|    |-------|      |   1  |   2  |   3  |   .  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |  0   |BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_INS,  KC_PSCR, KC_SLCK, KC_PAUS, KC_CALC, XXXXXXX, \
  KC_TAB,  QWERTY,  COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_PSLS, KC_7,    KC_8,    KC_9,    KC_PMNS, XXXXXXX, \
  _______, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG, DEBUG,                     KC_PAST, KC_4,    KC_5,    KC_6,    KC_PPLS, XXXXXXX, \
  KC_CAPS, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD, XXXXXXX, _______, KC_MUTE, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_DOT,  XXXXXXX, \
                             _______, _______, _______, _______, _______, KC_0,    _______, _______ \
  ),
};

int RGB_current_mode;

/*
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);  // XXX: does NOT allow direct change to _ADJUST
    return state;
}
*/

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
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

#define WITHOUT_MODS(...) \
  do { \
    uint8_t _real_mods = get_mods(); \
    clear_mods(); \
    { __VA_ARGS__ } \
    set_mods(_real_mods); \
  } while (0)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

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
    case BITCOIN:
        if (record->event.pressed) {
            tap_code16(UNICODE_KEY_LNX);
            tap_code(KC_2);
            tap_code(KC_0);
            tap_code(KC_B);
            tap_code(KC_F);
            tap_code(KC_SPACE);
        }
        break;
    case JSARROW:
        if (record->event.pressed) {
            tap_code(KC_EQL);
            tap_code16(KC_GT);
        }
        break;
  }
  return true;
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
  // switch(biton32(layer_state)) {
  if (IS_LAYER_ON(_ADJUST)) {
    // volume up/down
    #ifdef EXTRAKEY_ENABLE
    clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
    #endif
  }
  else if (IS_LAYER_ON(_LOWER)) {
    // undo/redo
    if (get_mods() & MOD_BIT(KC_LSHIFT)) {  // use shift-z for redo
        if (clockwise) {
            tap_code16(LCTL(KC_Z));         // shift is already pressed
        } else {
            WITHOUT_MODS({
                tap_code16(LCTL(KC_Z));
            });
        }
    }
    else {                                  // use ctrl-y for redo
      clockwise ? tap_code16(LCTL(KC_Y)) : tap_code16(LCTL(KC_Z));
    }
  }
  else if (IS_LAYER_ON(_RAISE)) {
    // nothing on RAISE layer, unconfortable to use
  }
  else {  // default layer
    // change desktop ctrl-alt-up/down (also move window with shift)
    if ((get_mods() & MOD_BIT(KC_LCTL)) && (get_mods() & MOD_BIT(KC_LALT))) {
      clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
    // alt-tab for windows, ctrl-tab for browser tabs (XOR/(!a != !b), only ONE of alt/ctrl pressed)
    else if (!(get_mods() & MOD_BIT(KC_LCTL)) != !(get_mods() & MOD_BIT(KC_LALT))) {
        clockwise ? tap_code(KC_TAB) : tap_code16(LSFT(KC_TAB));
    }
    // super-tab changes between windows of the same app
    else if (get_mods() & MOD_BIT(KC_LGUI)) {
        clockwise ? tap_code(KC_GRAVE) : tap_code16(LSFT(KC_GRAVE));
    }
    // mouse wheel by default
    else {
        #ifdef MOUSEKEY_ENABLE
            clockwise ? tap_code(KC_MS_WH_DOWN) : tap_code(KC_MS_WH_UP);
        #else
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
        #endif
    }
  }
}
#endif

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LSFT_T(KC_SPC):
      return true;
    default:
      return false;
  }
}

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    // case SFT_T(KC_SPC):
    //   return TAPPING_TERM + 1250;
    // case LT(1, KC_GRV):
    //   return 130;
    case LCTL_T(KC_BSPC):
      return TAPPING_TERM + 25;
    default:
      return TAPPING_TERM;
  }
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
