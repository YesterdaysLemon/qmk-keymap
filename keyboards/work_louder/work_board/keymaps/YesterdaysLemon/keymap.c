// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file keymap.c
 * @brief Pascal's keymap for the ZSA Voyager.
 *
 * This file defines what keycode is performed by each key position. See also
 * getreuer.c for definitions of macros, etc. used in my keymap.
 */

#include QMK_KEYBOARD_H

#include "work_board.h"
#include "layout.h"
#include "getreuer_lemon.c"

enum tap_dances {
    ENC_TAP,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_LR(  // Base layer: Magic Sturdy.
    KC_GRV , KC_V     , KC_M   , KC_L   , KC_C   , KC_P   ,
    KC_TAB , HOME_S   , HOME_T , HOME_R , HOME_D , KC_Y   ,
    KC_BSPC, HOME_X   , KC_K   , KC_J   , NUM_G  , KC_W   ,
    WIN_COL, G(KC_TAB), KC_DOWN, KC_UP  , KC_UNDS, KC_SPC ,

                        KC_B   , MAGIC  , KC_U   , KC_O   , KC_Q   , KC_SLSH, TD(ENC_TAP),
                        KC_F   , HOME_N , HOME_E , HOME_A , HOME_I , KC_QUOT,
                        KC_Z   , KC_H   , KC_COMM, KC_DOT , HOME_SC, KC_ENT ,
                                 QK_REP , KC_ESC , KC_LEFT, KC_RGHT, KC_DEL 
  ),

  [SYM] = LAYOUT_LR(  // Symbol layer.
    TMUXESC, MO(FUN), KC_LABK, KC_RABK, KC_BSLS, KC_GRV ,
    C(KC_Z), KC_EXLM, KC_MINS, KC_PLUS, KC_EQL , KC_HASH,
    _______, _______, KC_SLSH, KC_ASTR, KC_CIRC, USRNAME,
    _______, _______, _______, C(KC_Z), C(KC_C), C(KC_V),

                      KC_AMPR, ARROW  , KC_LBRC, KC_RBRC, SRCHSEL, _______, _______,
                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC, _______,
                      KC_TILD, KC_DLR , KC_LCBR, KC_RCBR, _______, _______,
                               C(KC_X), KC_PGDN, KC_PGUP, _______, KC_MUTE 
  ),

  [NUM] = LAYOUT_LR(  // Number layer.
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX,
    _______, KC_LGUI, XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______,TO(BASE), LLOCK  ,

                      KC_TAB , KC_8   , KC_9   , KC_4   , KC_PLUS, KC_SLSH, _______,
                      KC_COLN, KC_1   , KC_2   , KC_3   , KC_MINS, KC_ASTR,
                      KC_COMM, KC_7   , KC_6   , KC_5   , KC_DOT , _______,
                               KC_0   , _______, _______, _______, _______
  ),

  [WIN] = LAYOUT_LR(  // Window management layer.
    RGB_TOG, RGB_DEF, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI  ,
    XXXXXXX, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX  ,
    XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  ,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, G(KC_SPC),

                      G(KC_TAB)    , G(KC_8), G(KC_9), G(KC_4), XXXXXXX      , XXXXXXX,  XXXXXXX,
                      G(S(KC_LEFT)), G(KC_1), G(KC_2), G(KC_3), G(S(KC_RGHT)), XXXXXXX,
                      XXXXXXX      , G(KC_7), G(KC_6), G(KC_5), KC_VOLD      , KC_VOLU,
                                     QK_REP , XXXXXXX, XXXXXXX, XXXXXXX      , XXXXXXX
  ),

  [FUN] = LAYOUT_LR(  // Funky fun layer.
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
    _______, XXXXXXX, KC_LALT, KC_LSFT, KC_LCTL , XXXXXXX,
    _______, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX,
    _______, _______, _______, _______, TO(BASE), LLOCK  ,

                      XXXXXXX, KC_F8  , KC_F9  , KC_F4  , KC_F10 , QK_BOOT, _______,
                      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F11 , XXXXXXX,
                      XXXXXXX, KC_F7  , KC_F6  , KC_F5  , KC_F12 , XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

void dance_enc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_MPLY);
    } else if (state->count == 2) {
        register_code(KC_MNXT);
    } else {
        register_code(KC_MPRV);
    }
}

void dance_enc_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_MPLY);
    } else if (state->count == 2) {
        unregister_code(KC_MNXT);
    } else {
        unregister_code(KC_MPRV);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [ENC_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_enc_finished, dance_enc_reset),
};