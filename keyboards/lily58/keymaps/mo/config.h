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

#define QUICK_TAP_TERM 100
#define TAPPING_TERM 175

#define VIAL_KEYBOARD_UID {0x7E, 0xFD, 0xFC, 0x5B, 0x7D, 0x39, 0x48, 0x06}

/* VIAL secure unlock keystroke - currently both big keys (typ. SPACE/ENTER) */
#define VIAL_UNLOCK_COMBO_ROWS {4, 9}
#define VIAL_UNLOCK_COMBO_COLS {4, 4}

/* #define DYNAMIC_KEYMAP_LAYER_COUNT 6 */
/* #define VIAL_TAP_DANCE_ENTRIES 4 */
/* #undef LOCKING_SUPPORT_ENABLE */
/* #undef LOCKING_RESYNC_ENABLE */
/* #define NO_ACTION_ONESHOT */

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
#define LEADER_NO_TIMEOUT
#define LEADER_KEY_STRICT_KEY_PROCESSING

#define MASTER_RIGHT
/* #define MASTER_LEFT */
#define USE_SERIAL_PD2

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000

/* #define SPLIT_TRANSPORT_MIRROR */
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_WPM_ENABLE

#ifdef OLED_FONT_H
#undef OLED_FONT_H
#define OLED_FONT_H "myfont.c"
#else
#define OLED_FONT_H "myfont.c"
#endif
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 12

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT

/* #define AUTO_SHIFT_TIMEOUT 220 */
/* #define AUTO_SHIFT_MODIFIERS */
/* #define AUTO_SHIFT_REPEAT */
/* #define SENDSTRING_BELL */

