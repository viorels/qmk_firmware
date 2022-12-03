#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

uint16_t adjust_lock_timer = 0;
uint16_t copy_paste_timer;
uint16_t idle_timer = 0;
bool is_idle = true;

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
  LCTL_GESC,
  LCTL_GBSP,
  KC_CCCV,
  BITCOIN,
  JSARROW,
};

//Tap Dance Declarations
enum {
  TD_MINS_6 = 0,
  TD_COLN_7,
  TD_LBRC_8,
  TD_RBRC_9,
  TD_LEFT,
  TD_RIGHT
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_MINS_6]  = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_6),
  [TD_COLN_7]  = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_7),
  [TD_LBRC_8]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_8),
  [TD_RBRC_9]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_9),
  [TD_LEFT] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, C(KC_LEFT)),
  [TD_RIGHT] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, C(KC_RIGHT))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CTL/GE|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |Ctrl/'|
 * |------+------+------+------+------+------|  ESC  |    | MUTE  |------+------+------+------+------+------|
 * |LShift|Alt/Z |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |Alt// |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
/*KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \*/
  LT(4,KC_TAB),KC_Q, KC_W,   KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  LCTL_GESC, KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT), \
  KC_LSFT,LALT_T(KC_Z),KC_X, KC_C,    KC_V,    KC_B, KC_GESC,   KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  LALT_T(KC_SLSH), KC_RSFT, \
                             KC_LALT, KC_LGUI, LOWER, LSFT_T(KC_SPC), LT(4, KC_ENT), RAISE, KC_BSPC, KC_RALT \
),
/* Colemak
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC/`|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CTL/GE|   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |Ctrl/'|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, \
  _______, _______, KC_R,    KC_S,    KC_T,    KC_D,                      _______, KC_N,    KC_E,    KC_I,    KC_O,    _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_K,    _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |  F1  |  F2  |  F3  |  F4  |  F5  |                    | PgUp | Home |  Up  |  End | F11  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |-------.    ,-------| PgDn | Left | Down | Right| F12  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste| Ins  |-------|    |-------| BBack| WLeft|      |WRight| Alt  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |ADJUST|BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, XXXXXXX, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                    KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_F11,  KC_DEL, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,                   KC_PGDN, TD(TD_LEFT), KC_DOWN, TD(TD_RIGHT), KC_F12, _______, \
  _______, C(KC_Z),C(KC_X),C(KC_INS),S(KC_INS), KC_WBAK,_______, XXXXXXX, KC_WBAK, C(KC_LEFT), XXXXXXX, C(KC_RIGHT), KC_LALT, _______, \
                             _______, _______, _______, _______, _______, _______, _______, KC_LALT \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |  |   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   1  |   2  |   3  |   4  |   5  |                    |   -  |   :  |   [  |   ]  |   0  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   +  |   _  |   (  |   )  |   "  |  '   |
 * |------+------+------+------+------+------|   ₿   |    |       |------+------+------+------+------+------|
 * |LShift|   ^  |   &  |  {   |   }  |   |  |-------|    |-------|   *  |   =  |   <  |   >  |Alt// | Shft |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, \
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      TD(TD_MINS_6), TD(TD_COLN_7), TD(TD_LBRC_8), TD(TD_RBRC_9), KC_0, KC_BSLS, \
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PLUS, KC_UNDS, KC_LPRN, KC_RPRN, KC_DQUO, _______, \
  _______, KC_CIRC, KC_AMPR, KC_LCBR, KC_RCBR, KC_PIPE, BITCOIN, _______, KC_ASTR, KC_EQL,  KC_LT,   KC_GT, LALT_T(KC_SLSH), _______, \
                             _______, _______, _______, _______, _______, _______,   _______, _______\
// UC(0x20bf) ₿
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |RGB P |RGB B |RGB SW|RGB K |      |                    |      |PrntSc|ScrlLk|Pause | CALC | RESET|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CTL/GE|      |   -  |   +  |   .  |      |-------.    ,-------|   +  |   4  |   5  |   6  |   0  | Ctrl |
 * |------+------+------+------+------+------| RESET |    |       |------+------+------+------+------+------|
 * | CAPS |QWERTY|Colema|PrntSc| CALC |DEBUG |-------|    |-------|   *  |   1  |   2  |   3  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |  0   |BackSP| LAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  KC_ESC,  RGB_M_P, RGB_M_B, RGB_M_SW,RGB_M_K, XXXXXXX,                   XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, KC_CALC, RESET, \
  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PMNS, \
  LCTL_GESC,XXXXXXX,KC_PMNS, KC_PPLS, KC_DOT,  XXXXXXX,                   KC_PPLS, KC_4,    KC_5,    KC_6,    KC_0,    KC_RCTL, \
  KC_CAPS, QWERTY,  COLEMAK, KC_PSCR, KC_CALC, DEBUG,   RESET,   XXXXXXX, KC_PAST, KC_1,    KC_2,    KC_3,    LALT_T(KC_PSLS), KC_RSFT, \
                             _______, _______, _______, _______, _______, KC_0,    _______, _______ \
  ),
};

void rgblight_set_hsv_and_mode(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode) {
    rgblight_sethsv_noeeprom(hue, sat, val);
    wait_us(175);  // Add a slight delay between color and mode to ensure it's processed correctly
    rgblight_mode_noeeprom(mode);
}

int RGB_current_mode;

layer_state_t layer_state_set_user(layer_state_t state) {
    // state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);  // XXX: does NOT allow direct change to _ADJUST

    switch (get_highest_layer(state)) {
        case _RAISE:
            rgblight_set_hsv_and_mode(HSV_PURPLE, RGBLIGHT_MODE_BREATHING + 3);
            break;
        case _LOWER:
            rgblight_set_hsv_and_mode(HSV_GREEN, RGBLIGHT_MODE_BREATHING + 3);
            break;
        case _ADJUST:
            rgblight_set_hsv_and_mode(HSV_RED, RGBLIGHT_MODE_KNIGHT + 2);
            break;
        default:  //  for any other layers, or the default layer
        {
            uint8_t mode = RGBLIGHT_MODE_STATIC_LIGHT;
            switch (get_highest_layer(default_layer_state)) {
                case _COLEMAK:
                    rgblight_set_hsv_and_mode(HSV_BLUE, mode);
                    break;
                default:
                    rgblight_set_hsv_and_mode(HSV_CYAN, mode);
                    break;
            }
            break;
        }
    }

    return state;
}

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
    #ifdef UNICODE_ENABLE
      set_unicode_input_mode(UC_LNX);
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
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
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

void rgb_leds_active(void) {
    idle_timer = timer_read32();
    if (is_idle) {
        is_idle = false;
        layer_state_set_user(layer_state);
    }
};

void rgb_leds_idle(void) {
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_sethsv_noeeprom(HSV_BLUE); // sets the color to blue without saving
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // sets mode to Fast breathing without saving
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  rgb_leds_active();

  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    //set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

  static uint16_t lctl_timer;

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
        adjust_lock_timer = timer_read();
      } else {
        layer_off(_RAISE);
        // temporary lock ADJUST layer on RAISE release, until LOWER is released
        if (timer_elapsed(adjust_lock_timer) > TAPPING_TERM) {
          update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
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
    case LCTL_GESC:
    case LCTL_GBSP:
      if(record->event.pressed) {
        lctl_timer = timer_read();
        register_code(KC_LCTL); // Change the key to be held here
      } else {
        unregister_code(KC_LCTL); // Change the key that was held here, too!
        if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
          if (get_mods() & MOD_BIT(KC_LGUI)) {
            tap_code(KC_GRAVE);
          } else {
            tap_code(keycode == LCTL_GESC ? KC_ESC : KC_BSPC);
          }
        }
      }
      return false; // We handled this keypress
    case KC_CCCV:  // One key copy/paste
        if (record->event.pressed) {
            copy_paste_timer = timer_read();
        } else {
            if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                tap_code16(LCTL(KC_INS));
            } else { // Tap, paste
                tap_code16(LSFT(KC_INS));
            }
        }
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
    clockwise ? tap_code(KC_BRIU) : tap_code(KC_BRID);
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
      // nothing
  }
  else {  // default layer
    // change desktop ctrl-alt-up/down (also move window with shift)
    if ((get_mods() & MOD_BIT(KC_LCTL)) && (get_mods() & MOD_BIT(KC_LALT))) {
      clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
    // alt-tab for windows, ctrl-tab for browser tabs (XOR/(!a != !b), only ONE of alt/ctrl pressed)
    else if (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI))) {
        clockwise ? tap_code(KC_TAB) : tap_code16(LSFT(KC_TAB));
    }
    // mouse wheel by default
    else {
        // volume up/down
        #ifdef EXTRAKEY_ENABLE
        clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
        #endif
        /*
        #ifdef MOUSEKEY_ENABLE
            // "MK_W_OFFSET_UNMOD 2" should already send 2 clicks, but it doesn't
            clockwise ? tap_code(KC_MS_WH_DOWN) : tap_code(KC_MS_WH_UP);
            wait_ms(MK_W_INTERVAL_UNMOD);
            clockwise ? tap_code(KC_MS_WH_DOWN) : tap_code(KC_MS_WH_UP);
        #else
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
        #endif
        */
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
    case LCTL_T(KC_BSPC):   // for slow pinky
    case LT(2, KC_TAB):
      return TAPPING_TERM + 25;
    case TD_MINS_6:
      return TAPPING_TERM + 500;
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

  rgb_leds_idle();
}

// copied from Curry

#if defined(INDICATOR_LIGHTS)

void rgblight_sethsv_default_helper(uint8_t index) { rgblight_sethsv_at(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, index); }

void set_rgb_indicators(uint8_t this_mod, uint8_t this_led, uint8_t this_osm) {
    if (get_highest_layer(layer_state) == 0) {
        if ((this_mod | this_osm) & MOD_MASK_SHIFT || this_led & (1 << USB_LED_CAPS_LOCK)) {
#    ifdef SHFT_LED1
            rgblight_sethsv_at(120, 255, 255, SHFT_LED1);
#    endif  // SHFT_LED1
#    ifdef SHFT_LED2
            rgblight_sethsv_at(120, 255, 255, SHFT_LED2);
#    endif  // SHFT_LED2
        } else {
#    ifdef SHFT_LED1
            rgblight_sethsv_default_helper(SHFT_LED1);
#    endif  // SHFT_LED1
#    ifdef SHFT_LED2
            rgblight_sethsv_default_helper(SHFT_LED2);
#    endif  // SHFT_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_CTRL) {
#    ifdef CTRL_LED1
            rgblight_sethsv_at(0, 255, 255, CTRL_LED1);
#    endif  // CTRL_LED1
#    ifdef CTRL_LED2
            rgblight_sethsv_at(0, 255, 255, CTRL_LED2);
#    endif  // CTRL_LED2
        } else {
#    ifdef CTRL_LED1
            rgblight_sethsv_default_helper(CTRL_LED1);
#    endif  // CTRL_LED1
#    ifdef CTRL_LED2
            rgblight_sethsv_default_helper(CTRL_LED2);
#    endif  // CTRL_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_GUI) {
#    ifdef GUI_LED1
            rgblight_sethsv_at(51, 255, 255, GUI_LED1);
#    endif  // GUI_LED1
#    ifdef GUI_LED2
            rgblight_sethsv_at(51, 255, 255, GUI_LED2);
#    endif  // GUI_LED2
        } else {
#    ifdef GUI_LED1
            rgblight_sethsv_default_helper(GUI_LED1);
#    endif  // GUI_LED1
#    ifdef GUI_LED2
            rgblight_sethsv_default_helper(GUI_LED2);
#    endif  // GUI_LED2
        }
        if ((this_mod | this_osm) & MOD_MASK_ALT) {
#    ifdef ALT_LED1
            rgblight_sethsv_at(240, 255, 255, ALT_LED1);
#    endif  // ALT_LED1
#    ifdef GUI_LED2
            rgblight_sethsv_at(240, 255, 255, ALT_LED2);
#    endif  // GUI_LED2
        } else {
#    ifdef GUI_LED1
            rgblight_sethsv_default_helper(ALT_LED1);
#    endif  // GUI_LED1
#    ifdef GUI_LED2
            rgblight_sethsv_default_helper(ALT_LED2);
#    endif  // GUI_LED2
        }
    }
}

#endif  // INDICATOR_LIGHTS

/* Function for the indicators */
void matrix_scan_user(void) {
    #ifdef INDICATOR_LIGHTS
    // don't handle leds when idle to avoid rainbow flickering
    if (!is_idle)
        set_rgb_indicators(get_mods(), host_keyboard_leds(), get_oneshot_mods());
    #endif

    // rainbow leds when idle
    if (!is_idle && timer_elapsed(idle_timer) > OLED_TIMEOUT) {
        is_idle = true;
        rgb_leds_idle();
    }
}
