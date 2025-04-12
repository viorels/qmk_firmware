/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define GRAVE_ESC_SHIFT_OVERRIDE

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 4
#define ENCODER_DEFAULT_POS 0x3     // requires QMK update
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define UNICODE_KEY_LNX LCTL(LSFT(KC_U))

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD_PER_KEY
// #define IGNORE_MOD_TAP_INTERRUPT
// #define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 1

//#define MK_W_OFFSET_UNMOD 2
#define MK_W_INTERVAL_UNMOD 40

// Underglow
#undef RGBLIGHT_LED_COUNT
// #define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LED_COUNT 8
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_SLEEP
// #define RGBLIGHT_SPLIT
#define RGBLIGHT_LIMIT_VAL 50
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

// Curry

//#define INDICATOR_LIGHTS
#define SHFT_LED1 6
#define CTRL_LED1 7
#define ALT_LED1 0
#define GUI_LED1 1
