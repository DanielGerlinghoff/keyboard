#include QMK_KEYBOARD_H

#include "heatmap.h"

#define _COLEMAK 0
#define _QWERTY 1
#define _SPEC 2
#define _NAV_NUM 3


enum custom_keycodes {
    KC_AE = SAFE_RANGE,
    KC_OE,
    KC_UE,
    KC_SS,
    KC_HEAT,
};


/* TAP DANCE DEFINITIONS */
enum {
    TD_QWERTY,
    TD_NAVNUM,
};

void navnum_finished(qk_tap_dance_state_t *state, void *user_data);
void navnum_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_QWERTY] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_Q, _QWERTY),
    [TD_NAVNUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, navnum_finished, navnum_reset),
};

typedef enum {
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else                 return TD_SINGLE_HOLD;
    }
    if (state->count == 2) return TD_DOUBLE_TAP;
    else                   return TD_UNKNOWN;
}


/* KEYBOARD LAYERS */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Colemak-DHm
    *   ,-----------------------------------------------------------------------------------------------------.
    *   | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |   =  |          |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  | Tab   |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |   [  |   ]  |    \   |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * |  Bksp  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |   '  |             |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * |  Caps  |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |  Enter  |  `  | VUp  |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  | LCtrl | LWin  | LAlt  |                      Space                   |  Fn   | RCtrl  |VMute| VDn  |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_1,          KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  _______,
        KC_TAB,  TD(TD_QWERTY), KC_W,    KC_F, KC_P, KC_B,   KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,

        // Home row
        KC_BSPC,
        TD(TD_NAVNUM),
        LT(_SPEC, KC_R),
        LSFT_T(KC_S),
        LCTL_T(KC_T),
        KC_G, KC_M,
        RCTL_T(KC_N),
        RSFT_T(KC_E),
        LT(_SPEC, KC_I),
        LT(_NAV_NUM, KC_O),
        KC_QUOT, _______,

        KC_CAPS, KC_Z,          KC_X,    KC_C, KC_D, KC_V,   KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,  KC_GRV,  KC_VOLU,
        KC_LCTL, KC_LWIN,       KC_LALT,             KC_SPC,                              KC_LCTL, _______, KC_MUTE, KC_VOLD
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
        _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, TD(TD_QWERTY), KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______, _______, _______,

        // Home row
        _______,
        TD(TD_NAVNUM),
        LT(_SPEC, KC_S),
        LSFT_T(KC_D),
        LCTL_T(KC_F),
        KC_G, KC_H,
        RCTL_T(KC_J),
        RSFT_T(KC_K),
        LT(_SPEC, KC_L),
        LT(_NAV_NUM, KC_SCLN),
        _______, _______,

        _______, KC_Z,          KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    _______, _______, _______, _______, _______, _______,
        _______, _______,       _______,                            _______,                            _______, _______, _______, _______
    ),

    /* Special characters (after Neo) and function keys
    *   ,-----------------------------------------------------------------------------------------------------.
    *   |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |          |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  |       |   ß  |   _  |   [  |   ]  |   !  |   /  |   <  |   >  |   =  |   -  |   ä  |   ö  |    ü   |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * |        |   `  |   #  |   {  |   }  |   ?  |   *  |   (  |   )  |   &  |   +  |   @  |             |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * |        |   ^  |   ~  |   |  |   $  |   \  |   :  |   %  |   "  |   '  |   ;  |         |     |      |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  |       |       |       |                                              |       |        |     |      |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_SPEC] = LAYOUT(
        _______, KC_F1,   KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,   KC_F10,    KC_F11,  KC_F12,  _______,
        _______, KC_SS,   S(KC_MINS), KC_LBRC,    KC_RBRC,    S(KC_1),    KC_SLSH,    S(KC_COMM), S(KC_DOT),  KC_EQL,  KC_MINS,   KC_AE,   KC_OE,   KC_UE,
        _______, KC_GRV,  S(KC_3),    S(KC_LBRC), S(KC_RBRC), S(KC_SLSH), S(KC_8),    S(KC_9),    S(KC_0),    S(KC_7), S(KC_EQL), S(KC_2),      _______,
        _______, S(KC_6), S(KC_GRV),  S(KC_BSLS), S(KC_4),    KC_BSLS,    S(KC_SCLN), S(KC_5),    S(KC_QUOT), KC_QUOT, KC_SCLN,   _______, _______, _______,
        _______, _______, _______,                            _______,                                                 _______,   _______, _______, _______
    ),

    /* Navigation and numpad layer
    *   ,-----------------------------------------------------------------------------------------------------.
    *   | Heat |      | DskLf|      | DskRt|      |      |   7  |   8  |   9  |      |      |      |          |
    *  ,-------+------+------+------+------+------+------+------+------+------+------+------+------+----------'
    *  |       |      | Word | ArUp | Pste | Prev |   /  |   4  |   5  |   6  |   -  |      |      |        |
    * ,--------+------+------+------+------+-------------+------+------+------+------+------+------+--------'
    * |        |      | ArLf | ArDn | ArRt |      |   *  |   1  |   2  |   3  |   +  |      |             |
    * |--------+------+------+------+------+------|------+------+------+------+------+------+--+-----+------.
    * |        | Home | Cut  | Copy | End  | Pste |   :  |   0  |      |      |      |         |     |      |
    * `--------+------++-----+-+----+------+------+------+------+------+------+------++--------+-----+------|
    *  |       |       |       |                                              |       |        |     |      |
    *  `----------------------------------------------------------------------------------------------------'
    */
    [_NAV_NUM] = LAYOUT(
        KC_HEAT, _______, C(G(KC_LEFT)), _______, C(G(KC_RGHT)), _______,    _______,    KC_7, KC_8,    KC_9,    _______,   _______, _______, _______,
        _______, _______, C(KC_RGHT),    KC_UP,   S(KC_INS),     C(KC_LEFT), KC_SLSH,    KC_4, KC_5,    KC_6,    KC_MINS,   _______, _______, _______,
        _______, _______, KC_LEFT,       KC_DOWN, KC_RGHT,       _______,    S(KC_8),    KC_1, KC_2,    KC_3,    S(KC_EQL), _______,      _______,
        _______, KC_HOME, C(KC_X),       C(KC_C), KC_END ,       C(KC_V),    S(KC_SCLN), KC_0, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______,                               _______,                                        _______,   _______, _______, _______
    ),
};


/* SPECIAL PROCESSING */
void send_umlaut(char *lower, char *upper) {
    SEND_STRING("\"");
    if (get_mods() & MOD_MASK_SHIFT)
        send_string(upper);
    else
        send_string(lower);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Enable delete key on backspace
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) {
                // Replace with KC_DEL if any shift key is pressed
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
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
            break;
        }

        // Write umlaute
        case KC_AE:
            if (record->event.pressed) send_umlaut("a", "A");
            break;

        case KC_OE:
            if (record->event.pressed) send_umlaut("o", "O");
            break;

        case KC_UE:
            if (record->event.pressed) send_umlaut("u", "U");
            break;

        case KC_SS:
            if (record->event.pressed) {
                SEND_STRING(SS_RALT("s"));
            }
            break;
    }

    // Functions for heatmap generation
    if (record->event.pressed) {
        // Update key counter for heatmap
        increment_keycount(record);

        // Dump keycount array as a Python list
        if (keycode == KC_HEAT)
            dump_keycount();
    }

    return true;
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE | TD_NAVNUM:
            // Slower tap for NavNum Lock
            return 250;
        default:
            return TAPPING_TERM;
    }
}

void navnum_finished(qk_tap_dance_state_t *state, void *user_data) {
    static bool navnum_layer_locked = false;

    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NAV_NUM);
            break;
        case TD_DOUBLE_TAP:
            if (!navnum_layer_locked) {
                layer_on(_NAV_NUM);
                navnum_layer_locked = true;
            } else {
                layer_off(_NAV_NUM);
                navnum_layer_locked = false;
            }
            break;
        default:
            break;
    }
}

void navnum_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_NAV_NUM);
            break;
        default:
            break;
    }
}
