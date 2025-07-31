#include QMK_KEYBOARD_H
#include <stdio.h>

#include "keymap_german.h"
#include "sendstring_german.h"

/* keymap_dvorak_programmer.h	sendstring_dvorak_programmer.h */
/* keymap_dvorak.h	sendstring_dvorak.h */

/*----------------------------------------------------------------------------------------------------------------------*/
typedef union {
  uint32_t raw;
  struct {
    bool     capsword :1;
    bool     oneshot :1;
    bool     autocorrect :1;
    bool     autoshift :1;
  };
} user_config_t;

user_config_t user_config;

// TODO: OLED_ENABLE is not really respected, maybe fix that!
// TODO: maybe set these:
// these are the keycodes, some collide with predefined; what to do???
// maybe we just add the bind for programmable keys too and use these
#define LAUNCH1 0x0094
#define LAUNCH2 0x0095
#define LAUNCH3 0x00CA
#define LAUNCH4 0x00CB

/*----------------------------------------------------------------------------------------------------------------------*/

enum my_keycodes {
  MY_OSON = SAFE_RANGE, // on/off for OneShot
  MY_OSOF,
  MY_ASON, // on/off for AutoShift
  MY_ASOF,
  MY_ACON, // on/off for AutoCorrect
  MY_ACOF,
  MY_CWON, // on/off for CapsWord
  MY_CWOF,
  MY_PRVT, // toggle private mode
  DSP_PLS, // OLED DiSPlay brighter
  DSP_MNS, // OLED DiSPlay darker
  DSP_OFF, // OLED off
  DSP_ON, // OLED on
};

/*----------------------------------------------------------------------------------------------------------------------*/

enum layer_number {
  _DVORAK = 0,
  _QWERTY,
  _QWERTZ,
  _BOTTOM,
  _TOP,
  _FN,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define BOTTOM TG(_BOTTOM)
#define TOP TG(_TOP)

// why does it not work with the pdf? maybe make own keycode and call set_single_persistent_default_layer(layer)!
#define PERM_QWERTZ DF(_QWERTZ)
#define PERM_QWERTY DF(_QWERTY)
#define PERM_DVORAK DF(_DVORAK)

/*----------------------------------------------------------------------------------------------------------------------*/

enum {
    TD_LSFT_CAPS,
    TD_RSFT_CAPS,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

/*----------------------------------------------------------------------------------------------------------------------*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |OsLCTL|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |'_CTRL|
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LSftTD|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSftTD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | OsAlt| /Space  /       \Enter \  |BackSP|OsALGR|RAISE |
 *                   |      |      |      |/       /         \      \ | Del  |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
          KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
          KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
   OSM(MOD_LCTL),   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
TD(TD_LSFT_CAPS),   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  TD(TD_RSFT_CAPS),
                             LOWER, KC_LGUI,  OSM(MOD_LALT), KC_SPC,   KC_ENT,   KC_BSPC, OSM(MOD_RALT), RAISE
),
/* QWERTZ
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ^   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  ß   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |OsLCTL|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ö  |ä_CTRL|
 * |------+------+------+------+------+------|   ü   |    |    +  |------+------+------+------+------+------|
 * |LSftTD|   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RSftTD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | OsAlt| /Space  /       \Enter \  |BackSP|OsALGR|RAISE |
 *                   |      |      |      |/       /         \      \ | Del  |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_QWERTZ] = LAYOUT(
          KC_ESC,   DE_1,   DE_2,    DE_3,    DE_4,    DE_5,                     DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_CIRC,
          KC_TAB,   DE_Q,   DE_W,    DE_E,    DE_R,    DE_T,                     DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_SS,
   OSM(MOD_LCTL),   DE_A,   DE_S,    DE_D,    DE_F,    DE_G,                     DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA, RCTL_T(DE_ADIA),
TD(TD_LSFT_CAPS),   DE_Y,   DE_X,    DE_C,    DE_V,    DE_B, DE_UDIA,  DE_PLUS,  DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS, TD(TD_RSFT_CAPS),
                             LOWER, KC_LGUI,  OSM(MOD_LALT), KC_SPC,   KC_ENT,   KC_BSPC, OSM(MOD_RALT), RAISE
),
/* DVORAK TODO: make it really dvorak
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ~   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |OsLCTL|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |'_CTRL|
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LSftTD|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSftTD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | OsAlt| /Space  /       \Enter \  |BackSP|OsALGR|RAISE |
 *                   |      |      |      |/       /         \      \ | Del  |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

 [_DVORAK] = LAYOUT(
          KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
          KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
   OSM(MOD_LCTL),   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
TD(TD_LSFT_CAPS),   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  TD(TD_RSFT_CAPS),
                             LOWER, KC_LGUI,  OSM(MOD_LALT), KC_SPC,   KC_ENT,   KC_BSPC, OSM(MOD_RALT), RAISE
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |      |                    |      |      |      |      |      |  ´   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|   <   |    |    #  |------+------+------+------+------+------|
 * |LSftTD|      |      |ShCopy|SPaste|      |-------|    |-------|   |  |   `  |   +  |   {  |   }  |RSftTD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | OsAlt| /Space  /       \Enter \  |BackSP|OsALGR|RAISE |
 *                   |      |      |      |/       /         \      \ | Del  |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______,    _______,    _______,                   _______, _______, _______, _______, _______, DE_ACUT,
  _______, KC_EXLM, KC_AT,   KC_HASH,    KC_DLR,     KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, KC_1,    KC_2,    KC_3,       KC_4,       KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, _______, _______, C(S(KC_C)), C(S(KC_V)), _______, DE_LABK, DE_HASH, KC_PIPE, KC_GRAVE,KC_PLUS, KC_LCBR, KC_RCBR, _______,
                             _______,    _______,    _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |Leader|      | Break| Ins  | Print| Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  F6  |  F7  |  F8  |  F9  |  F10 |                    | Home |PgDown| PgUp |  End |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |  F11 |  F12 |  F13 |  F14 |  F15 |-------.    ,-------| Left | Down |  Up  |Right |      | RCTRL|
 * |------+------+------+------+------+------|   <   |    |   #   |------+------+------+------+------+------|
 * |LSftTD|  F16 |  F17 |  F18 |  F19 |  F20 |-------|    |-------|ProgB1|ProgB2|ProgB3|ProgB4|ProgB5|RSftTD|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | OsAlt| /Space  /       \Enter \  |BackSP|OsALGR|RAISE |
 *                   |      |      |      |/       /         \      \ | Del  |      |      |
 *                   `-------------------''-------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       QK_LEAD, XXXXXXX, KC_BRK,  KC_INS,  KC_PSCR, KC_DEL,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_RCTL,
  _______, KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,   DE_LABK, DE_HASH,  PB_1,    PB_2,    PB_3,    PB_4,    PB_5,    _______,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |BootLd|ReBoot|      |      |Leader|                    |Leader|      |PwrDwn|Sleep | Wake |KeyLck|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |Mute  |Vol Up|Play/P|      |Bright|                    |      |CapsLk|NumLck|ScrlLk|Privat|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |OsLCTL|Prev M|Vol Do|Next M|      |Darker|-------.    ,-------|ProgB1|ProgB2|ProgB3|ProgB4|ProgB5| RCTL |
 * |------+------+------+------+------+------| Bottom|    |  Top  |------+------+------+------+------+------|
 * |AltRep|ProgB6|ProgB7|ProgB8|ProgB9|Calc  |-------|    |-------|ReqMk1|ReqMk2|      |RunMk1|RunMk2|Repeat|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| ALGR |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
        _______, QK_BOOT, QK_RBT,  XXXXXXX, XXXXXXX, QK_LEAD,                   QK_LEAD, XXXXXXX, KC_PWR,  KC_SLEP, KC_WAKE, QK_LOCK,
        _______, KC_MUTE, KC_VOLU, KC_MPLY, XXXXXXX, KC_BRIU,                   XXXXXXX, KC_CAPS, KC_NUM,  KC_SCRL, MY_PRVT, XXXXXXX,
        _______, KC_MPRV, KC_VOLD, KC_MNXT, XXXXXXX, KC_BRID,                   PB_1,    PB_2,    PB_3,    PB_4,    PB_5,    KC_RCTL,
        QK_AREP, PB_6,    PB_7,    PB_8,    PB_9,    KC_CALC, BOTTOM,  TOP,     DM_REC1, DM_REC2, XXXXXXX, DM_PLY1, DM_PLY2, QK_REP,
                                   _______, _______, _______, _______, _______, _______, _______, _______
  ),


/* BOTTOM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |      |      |Leader|                    |      |NumLck|  7   |  8   |  9   |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |  Up  |      |PageUp|      |                    |   =  |  /   |  4   |  5   |  6   |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCtlOs| Left | Down | Right|PageDn|      |-------.    ,-------|   .  |  *   |  1   |  2   |  3   |KP Ent|
 * |------+------+------+------+------+------| Bottom|    | Top   |------+------+------+------+------+------|
 * |LSftTD| Home |      | End  |      |      |-------|    |-------|      |  -   |  0   |  0   |  ,   |KP Ent|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| ALGR |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_BOTTOM] = LAYOUT(
           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LEAD,                   XXXXXXX, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
           _______, XXXXXXX, KC_UP,   XXXXXXX, KC_PGUP, XXXXXXX,                   KC_PEQL, KC_PSLS, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
           _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,                   KC_PDOT, KC_PAST, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  TD(TD_LSFT_CAPS), KC_HOME, XXXXXXX, KC_END,  XXXXXXX, XXXXXXX, BOTTOM,  TOP,     XXXXXXX, KC_PMNS, KC_P0,   KC_P0,   KC_PCMM, KC_PENT,
                                      _______, _______, _______, _______, _______,  _______, _______, _______
  ),

// TODO: make this the mouse layer
/* TOP
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| Bottom|    | Top   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| ALGR |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_TOP] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BOTTOM,  TOP,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),

/* FN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | CW On|AC On |AS On |OS On |      |                    |OLED 1|      |      |      |      |DVORAK|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |AS Up |      |      |                    |OLED +|      |      |      |      |QWERTY|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RPT AS|      |      |ASDown|      |      |-------.    ,-------|OLED -|      |      |      |      |QWERTZ|
 * |------+------+------+------+------+------| Bottom|    | Top   |------+------+------+------+------+------|
 * |      |CW Off|AC Off|AS Off|OS Off|      |-------|    |-------|OLED 0|      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |LOWER | LGUI | Alt  | /Space  /       \Enter \  |BackSP| ALGR |RAISE |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_FN] = LAYOUT(
  XXXXXXX, MY_CWON, MY_ACON, MY_ASON, MY_OSON, XXXXXXX,                   DSP_ON,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PERM_DVORAK,
  XXXXXXX, XXXXXXX, XXXXXXX, AS_UP,   XXXXXXX, XXXXXXX,                   DSP_PLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PERM_QWERTY,
  AS_RPT,  XXXXXXX, XXXXXXX, AS_DOWN, XXXXXXX, XXXXXXX,                   DSP_MNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PERM_QWERTZ,
  XXXXXXX, MY_CWOF, MY_ACOF, MY_ASOF, MY_OSOF, XXXXXXX, BOTTOM,  TOP,     DSP_OFF, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};
const char PROGMEM help_string[] = "this is as teststring and should be repaced!";

#ifdef OLED_ENABLE

/*--| in render.c |-----------------------------------------------------------------------------------------------------*/
extern void render_lock(int *x, int *y);

extern void render_line(int *x, int *y, const char PROGMEM *logo, int size);
extern void render_empty(int *x, int *y);
extern void render_halffull(int *x, int *y);
extern void render_full(int *x, int *y);

extern void render_layout(int *x, int *y);

extern void render_empty_SQ(int *x, int *y);

extern void render_MOD(int *x, int *y, const char PROGMEM *line1, int size1, const char PROGMEM *line2, int size2);
extern void render_MOD_caps(int *x, int *y);
extern void render_MOD_numlock(int *x, int *y);
extern void render_MOD_capsword(int *x, int *y);
extern void render_MOD_scrolllock(int *x, int *y);
extern void render_MOD_win(int *x, int *y);
extern void render_MOD_shift(int *x, int *y);
extern void render_MOD_alt(int *x, int *y);
extern void render_MOD_ctrl(int *x, int *y);
extern void render_MOD_altgr(int *x, int *y);
extern void render_MODS(int *x, int *y);

extern void render_OS_left(int *x, int *y);
extern void render_OS_right(int *x, int *y);
extern void render_OS_leftLock(int *x, int *y);
extern void render_OS_rightLock(int *x, int *y);
extern bool render_OS(int *x, int *y);

extern void render_makro_sym(int *x, int *y, const char PROGMEM *logo);
extern void render_makros_and_state(int *x, int *y);

extern void render_leader(int *x, int *y);

extern void render_4x4y_anim(int *x, int *y);

extern void render_layer_logo(int *x, int *y);


/*----------------------------------------------------------------------------------------------------------------------*/


bool pressed = false;

bool oneshot_enabled = true;
bool autoshift_enabled = false;
bool autocorrect_enabled = false;
bool capsword_enabled = true;
bool capsword_active = false;

os_variant_t detected_os = OS_UNSURE;

char keylog_str[8] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

bool caps = false;
bool numlock = false;
bool scrolllock = false;

bool makroReq1 = false;
bool makroReq2 = false;
bool makroPly1 = false;
bool makroPly2 = false;

bool leader = false;
bool leader_done = false;
bool leader_cancel = false;

bool os_rctrl = false;
bool os_lctrl = false;
bool os_rctrl_lock = false;
bool os_lctrl_lock = false;
bool os_ralt = false;
bool os_lalt = false;
bool os_ralt_lock = false;
bool os_lalt_lock = false;

bool privMode = true;

layer_state_t default_layer_state;
bool is_qwertz;
bool is_dvorak;

bool keylock_active = false;
bool keylock_watching = false;

char keylog1[] = "     ";
char keylog2[] = "     ";
char keylog3[] = "     ";
char keylog4[] = "     ";

char *keylogger[] = {
    keylog1,
    keylog2,
    keylog3,
    keylog4,
};

char *keylog_write_buffer = keylog4;
int keylog_write_buffer_char = 0;

int layer_type = 0;

/*----------------------------------------------------------------------------------------------------------------------*/

/* void keylogScrollLine () { */
/*     char *newWriteBuffer = keylogger[0]; */
/*     for (int i = 0; i <= 2; i++) { */
/*         keylogger[i] = keylogger[i + 1]; */
/*     } */
/*     keylogger[3] = newWriteBuffer; */
/*  */
/*     keylog_write_buffer = newWriteBuffer; */
/*     keylog_write_buffer_char = 0; */
/*     for (int i = 0; i <= 4; i++) { */
/*         newWriteBuffer[i] = ' '; */
/*     } */
/* } */
/*  */
/* // TODO: linebreaks for special chars: */
/* void keylogAddTwoChars(char first, char second) { */
/*     if (keylog_write_buffer_char >= 4) { */
/*         keylogScrollLine(); */
/*     } */
/*  */
/*     keylog_write_buffer[keylog_write_buffer_char] = first; */
/*     keylog_write_buffer_char++; */
/*     keylog_write_buffer[keylog_write_buffer_char] = second; */
/*     keylog_write_buffer_char++; */
/*  */
/* } */
/*  */
/* void keylogAddChar(char newChar) { */
/*     if (keylog_write_buffer_char >= 5) { */
/*         keylogScrollLine(); */
/*     } */
/*  */
/*     keylog_write_buffer[keylog_write_buffer_char] = newChar; */
/*     keylog_write_buffer_char++; */
/* } */
/*  */
/* // TODO: we could use the two pixel columns for more info */
/* void keylog_print() { */
/*     for (int i = 0; i<= 3; i++) { */
/*         oled_write(keylog[i]); */
/*     } */
/* } */

/*----------------------------------------------------------------------------------------------------------------------*/

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    state = update_tri_layer_state(state, _TOP, _BOTTOM, _FN);
    return state;
}

bool process_detected_host_os_user(os_variant_t os) {
    detected_os = os;
    switch(os) {
        case OS_MACOS:
        case OS_IOS:
            tap_code16(CG_SWAP);
        default:
            tap_code16(CG_NORM);
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------*/

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "k%2d : %c",
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}

/*----------------------------------------------------------------------------------------------------------------------*/

bool led_update_user(led_t led_state) {
    caps = led_state.caps_lock;
    numlock = led_state.num_lock;
    scrolllock = led_state.scroll_lock;
    return false;
}


/*----------------------------------------------------------------------------------------------------------------------*/

static void enterPrivMode(void) {
    privMode = true;
}

static void leavePrivMode (void) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
    privMode = false;
}

static void togglePrivate(void) {
    if (privMode) {
        leavePrivMode();
    }
    else {
        enterPrivMode();
    }
}

/*----------------------------------------------------------------------------------------------------------------------*/

bool dynamic_macro_record_start_user(int8_t direction) {
    if (direction == 1) {
        makroReq1 = true;
    }
    else if (direction == -1) {
        makroReq2 = true;
    }
    return false;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    if (direction == 1) {
        makroReq1 = false;
    }
    else if (direction == -1) {
        makroReq2 = false;
    }
    return false;
}

bool dynamic_macro_play_user(int8_t direction) {
    if (direction == 1) {
        makroPly1 = true;
    }
    else if (direction == -1) {
        makroPly2 = true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------*/

void leader_start_user(void) {
    leader = true;
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_P)) {
        togglePrivate();
        leader_done = true;
        leader = false;
        return;
    }
    else if (leader_sequence_one_key(KC_I)) {
        /* SEND_STRING("Moritz Schwärzler"); */
        /* SEND_STRING("Moritz Schw¨arzler"); */
        SEND_STRING("Moritz Schwaerzler");
        leader_done = true;
        leader = false;
        return;
    }
    else if (leader_sequence_one_key(KC_M)) {
        SEND_STRING("12214330");
        leader_done = true;
        leader = false;
        return;
    }
    else if (leader_sequence_one_key(KC_L)) {
        enterPrivMode();
        SEND_STRING(SS_LGUI("l"));
        leader_done = true;
        leader = false;
        return;
    }
    else if (leader_sequence_one_key(KC_H)) {
        /* SEND_STRING(help_string); */
        send_string_with_delay_P(help_string, 10);
        leader_done = true;
        leader = false;
        return;
    }
    /* if (leader_sequence_one_key(KC_F)) { */
    /*     // Leader, f => Types the below string */
    /*     SEND_STRING("QMK is awesome."); */
    /* } else if (leader_sequence_two_keys(KC_D, KC_D)) { */
    /*     // Leader, d, d => Ctrl+A, Ctrl+C */
    /*     SEND_STRING(SS_LCTL("a") SS_LCTL("c")); */
    /* } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) { */
    /*     // Leader, d, d, s => Types the below string */
    /*     SEND_STRING("https://start.duckduckgo.com\n"); */
    /* } else if (leader_sequence_two_keys(KC_A, KC_S)) { */
    /*     // Leader, a, s => GUI+S */
    /*     tap_code16(LGUI(KC_S)); */
    /* } */
    leader = false;
    leader_cancel = true;
}

/*----------------------------------------------------------------------------------------------------------------------*/

void oneshot_mods_changed_user(uint8_t mods) {
    os_lalt = mods & MOD_BIT(KC_LALT);
    os_ralt = mods & MOD_BIT(KC_RALT);
    os_lctrl = mods & MOD_BIT(KC_LCTL);
    os_rctrl = mods & MOD_BIT(KC_RCTL);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
    os_lalt_lock = mods & MOD_BIT(KC_LALT);
    os_ralt_lock = mods & MOD_BIT(KC_RALT);
    os_lctrl_lock = mods & MOD_BIT(KC_LCTL);
    os_rctrl_lock = mods & MOD_BIT(KC_RCTL);
}

/*----------------------------------------------------------------------------------------------------------------------*/

layer_state_t default_layer_state_set_user(layer_state_t state) {
    default_layer_state = state;
    if (default_layer_state == _QWERTZ) {
        is_qwertz = true;
        is_dvorak = false;
    }
    else if (default_layer_state == _DVORAK) {
        is_qwertz = false;
        is_dvorak = true;
    }
    else {
        is_qwertz = false;
        is_dvorak = false;
    }
    return state;
}

/*----------------------------------------------------------------------------------------------------------------------*/

void caps_word_set_user(bool active) {
    capsword_active = active;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case DE_MINS:
        case DE_DOT:
        case DE_ADIA:
        case DE_ODIA:
        case DE_UDIA:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

/*----------------------------------------------------------------------------------------------------------------------*/

void key_lock_changed_user(bool on) {
    keylock_active = on;
}

void key_lock_watching_changed_user(bool on) {
    keylock_watching = on;
}

/*----------------------------------------------------------------------------------------------------------------------*/

bool oled_task_user(void) {
    int cur_x = 0;
    int cur_y = 0;

  /* if (is_keyboard_master()) { */
    // Host Keyboard Layer Status
    /* oled_write_P(PSTR("Layer: "), false); */

    /* oled_clear(); */

    if ((leader || leader_done || leader_cancel) && is_keyboard_master()) {
        render_leader(&cur_x, &cur_y);
    }
    else {
        switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _QWERTZ:
        case _DVORAK:
            render_empty(&cur_x, &cur_y);
            render_empty(&cur_x, &cur_y);
            layer_type = 0;
            break;
        case _TOP:
            render_full(&cur_x, &cur_y);
            render_empty(&cur_x, &cur_y);
            layer_type = 5;
            break;
        case _BOTTOM:
            render_empty(&cur_x, &cur_y);
            render_full(&cur_x, &cur_y);
            layer_type = 4;
            break;
        case _RAISE:
            render_halffull(&cur_x, &cur_y);
            render_empty(&cur_x, &cur_y);
            pressed = true;
            layer_type = 2;
            break;
        case _LOWER:
            render_empty(&cur_x, &cur_y);
            render_halffull(&cur_x, &cur_y);
            pressed = true;
            layer_type = 1;
            break;
        case _ADJUST:
            render_halffull(&cur_x, &cur_y);
            render_halffull(&cur_x, &cur_y);
            pressed = true;
            layer_type = 3;
            break;
        case _FN:
            render_full(&cur_x, &cur_y);
            render_full(&cur_x, &cur_y);
            layer_type = 6;
            break;
        default:
            oled_write_ln_P(PSTR("UNKWN"), true);
            cur_y += 2;
        }
    }

    if (is_keyboard_master()) {
        render_makros_and_state(&cur_x, &cur_y);
    }
    else {
      render_layout(&cur_x, &cur_y);
    }

  if (is_keyboard_master()) {
    bool overscroll = render_OS(&cur_x, &cur_y);

    /* if (cur_y <= (15 - 6)) { */
    /*     cur_y = 15 - 6; */
    /*     cur_x = 0; */
    /*     oled_set_cursor(cur_x, cur_y); */
    /*     render_status(&cur_x, &cur_y, oneshot_enabled, 'O', 'S'); */
    /*     oled_write_char(' ', false); */
    /*     render_status(&cur_x, &cur_y, autoshift_enabled, 'A', 'S'); */
    /*     render_status(&cur_x, &cur_y, autocorrect_enabled, 'A', 'C'); //TODO: some menu for selection? */
    /*     cur_y += 2; */
    /*     oled_set_cursor(cur_x, cur_y); */
    /* } */

    if (overscroll) {

    }else{

    }
    cur_y = 15 - 4;
    cur_x = 0;
    oled_set_cursor(cur_x, cur_y);
    /* oled_write_ln(read_keylog(), false); */
    if (privMode) {
        render_lock(&cur_x, &cur_y);
    }
    else {
        oled_write_ln(read_keylogs(), false);
    }
  }
  else {
    render_MODS(&cur_x, &cur_y);

    cur_y = 15 - 4;
    cur_x = 0;
    oled_set_cursor(cur_x, cur_y);
    render_4x4y_anim(&cur_x, &cur_y);
  }
  /* } else { */
  /* } */
    return false;
}


#endif // OLED_ENABLE

void setOneShot(bool on, bool safe_user_config) {
    oneshot_enabled = on;
    if(on) {
        tap_code16(OS_ON);
    }
    else {
        tap_code16(OS_OFF);
    }
    if(safe_user_config) {
        user_config.oneshot = on;
        eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    }
}

void setAutoShift(bool on, bool safe_user_config) {
    autoshift_enabled = on;
    if(on) {
        tap_code16(AS_ON);
    }
    else {
        tap_code16(AS_OFF);
    }
    if(safe_user_config) {
        user_config.autoshift = on;
        eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    }
}

void setAutoCorrect(bool on, bool safe_user_config) {
    autocorrect_enabled = on;
    if(on) {
        tap_code16(AC_ON);
    }
    else {
        tap_code16(AC_OFF);
    }
    if(safe_user_config) {
        user_config.autocorrect = on;
        eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    }
}

void setCapsWord(bool on, bool safe_user_config) {
    capsword_enabled = on;
    if(on) {
        caps_word_on();
    }
    else {
        caps_word_off();
    }
    if(safe_user_config) {
        user_config.capsword = on;
        eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
    }
}


uint8_t mod_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  if (record->event.pressed) {
      if (!privMode) {
            set_keylog(keycode, record);
      }
  }
#endif
  mod_state = get_mods();
    switch (keycode) {
    case MY_OSON:
        {
            if (!record->event.pressed) {
                setOneShot(true, true);
            }
            return false;
        }
    case MY_OSOF:
        {
            if (!record->event.pressed) {
                setOneShot(false, true);
            }
            return false;
        }
    case MY_ASON:
        {
            if (!record->event.pressed) {
                setAutoShift(true, true);
            }
            return false;
        }
    case MY_ASOF:
        {
            if (!record->event.pressed) {
                setAutoShift(false, true);
            }
            return false;
        }
    case MY_ACON:
        {
            if (!record->event.pressed) {
                setAutoCorrect(true, true);
            }
            return false;
        }
    case MY_ACOF:
        {
            if (!record->event.pressed) {
                setAutoCorrect(false, true);
            }
            return false;
        }
    case MY_CWON:
        {
            if (!record->event.pressed) {
                setCapsWord(true, true);
            }
            return false;
        }
    case MY_CWOF:
        {
            if (!record->event.pressed) {
                setCapsWord(false, true);
            }
            return false;
        }
    case MY_PRVT:
        {
            if (!record->event.pressed) {
                togglePrivate();
            }
            return false;
        }
    case DSP_ON:
        {
            if (!record->event.pressed) {
                oled_on();
            }
            return false;
        }
    case DSP_OFF:
        {
            if (!record->event.pressed) {
                oled_off();
            }
            return false;
        }
    case DSP_PLS:
        {
            /* if (!record->event.pressed) { */
                uint8_t b = oled_get_brightness();
                if (b < 0xff) {
                    b++;
                    oled_set_brightness(b);
                }
            /* } */
            return false;
        }
    case DSP_MNS:
        {
            /* if (!record->event.pressed) { */
                uint8_t b = oled_get_brightness();
                if (b > 0x1) {
                    b--;
                    oled_set_brightness(b);
                }
            /* } */
            return false;
        }
    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

        /* SEND_STRING("Mority Schwaeryler"); */
    }

  return true;
}

/*----------------------------------------------------------------------------------------------------------------------*/
void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  capsword_enabled = user_config.capsword;
  oneshot_enabled = user_config.oneshot;
  autocorrect_enabled = user_config.autocorrect;
  autoshift_enabled = user_config.autoshift;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;

  user_config.capsword = true;
  user_config.oneshot = true;
  user_config.autocorrect = false;
  user_config.autoshift = false;

  capsword_enabled = user_config.capsword;
  oneshot_enabled = user_config.oneshot;
  autocorrect_enabled = user_config.autocorrect;
  autoshift_enabled = user_config.autoshift;

  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  setCapsWord(user_config.capsword, false);
  setAutoShift(user_config.autoshift, false);
  setAutoCorrect(user_config.autocorrect, false);
  setOneShot(user_config.oneshot, false);
}
/*----------------------------------------------------------------------------------------------------------------------*/
