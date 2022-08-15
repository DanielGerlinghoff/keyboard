#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _QWERTY 1
#define _NUM 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Colemak-DHm
    *   ,-----------------------------------------------------------------------------------------------------.
    *   | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |   Bksp   |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  | Tab   |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |   [  |   ]  |    \   |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * | Caps   |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |   '  |    Enter    |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * | LShft  |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |  RShft  |  `  | VUp  |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  | LCtrl | LWin  | LAlt  |                      Space                   |  Fn   | RCtrl  |VMute| VDn  |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E,    KC_I,   KC_O,     KC_QUOT,      KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT, KC_GRV,  KC_VOLU,
        KC_LCTL, KC_LWIN, KC_LALT,             KC_SPC,                      TG(_NUM), KC_LCTL, KC_MUTE, KC_VOLD
    ),

    /* QWERTY
    *   ,-----------------------------------------------------------------------------------------------------.
    *   |      |      |      |      |      |      |      |      |      |      |      |      |      |          |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  |       |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |      |      |        |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * |        |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |      |             |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * |        |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |      |      |      |         |     |      |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  |       |       |       |                                              |       |        |     |      |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______, _______, _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,      _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

	/* Numpad
    *   ,-----------------------------------------------------------------------------------------------------.
    *   |      |      |      |      |      |      |      |   7  |   8  |   9  |      |      |      |          |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  |       |      |      |      |      |      |      |   4  |   5  |   6  |      |      |      |        |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * |        |      |      |      |      |      |      |   1  |   2  |   3  |      |      |             |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * |        |      |      |      |      |      |      |   0  |   0  |      |      |         |     |      |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  |       |       |       |                                              |       |        |     |      |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5, KC_6,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3,    _______, _______,      _______,
        _______, _______, _______, _______, _______, _______, _______, KC_0, KC_0, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                               _______, _______, _______, _______
    ),
};
