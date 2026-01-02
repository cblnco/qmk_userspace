/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#ifdef AUDIO_ENABLE
  #include "muse.h"
  #include "audio/songs.h"
#endif

enum planck_layers {
  _QWERTY,
  _MOBILITY,
  _SYMBOLS,
  _NUMBERS,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  MOBILITY,
  SYMBOLS,
  NUMBERS,
  ADJUST,
  WIN,
  MAC,
  OS_GUI,
  OS_CTL
};

enum tap_dance {
  TD_SYMBOL
};

#define MOBILITY MO(_MOBILITY)
#define NUMBERS MO(_NUMBERS)
#define SYMBOLS MO(_SYMBOLS)
#define TD_FN_SYMBOL TD(TD_SYMBOL)

static bool type_os_key_events(uint8_t keycode, bool is_pressed);
void td_lsft_finished(tap_dance_state_t *state, void *user_data);
void td_lsft_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
  [TD_SYMBOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lsft_finished, td_lsft_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |  A   |  S   |  D   |  F   |  G   |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |  Z   |  X   |  C   |  V   |  B   |  N   |  M   |  ,   |  .   |  /   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSft | LAlt | GUI  | Ctrl |Sym/Fn|    Space    |MOBIL |RCtrl |RAlt  |RGUI  |RSft  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,         KC_T,   KC_Y,   KC_U,     KC_I,     KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,         KC_G,   KC_H,   KC_J,     KC_K,     KC_L,    KC_SCLN, KC_QUOT,
    KC_CAPS, KC_Z,    KC_X,    KC_C,   KC_V,         KC_B,   KC_N,   KC_M,     KC_COMM,  KC_DOT,  KC_SLSH, KC_ENT,
    KC_LSFT, KC_LALT, OS_GUI,  OS_CTL, TD_FN_SYMBOL, KC_SPC, KC_SPC, MOBILITY, KC_RCTL, KC_RALT, KC_RGUI, KC_RSFT
),


/* Mobility
 * ,-----------------------------------------------------------------------------------.
 * |      |      |VolD  | Up   |VolU  |      |      |Home  | Up   | End  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |Left  |Down  |Rght  |      |      |Left  |Down  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |Mute  |      |      |      |      |      |      | Del  | Ins  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOBILITY] = LAYOUT_planck_grid(
    _______, _______, KC_VOLD, KC_UP,   KC_VOLU,  _______, _______, KC_HOME, KC_UP,   KC_END,   _______, _______,
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
    _______, _______, KC_MUTE, _______, _______,  _______, _______, _______, KC_DEL,  KC_INS,   _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______, _______
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |Grv   |  !   |  @   |  #   |  $   |      |  &   |  *   |  (   |  )   |  -   |Bspc  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  %   |  ^   |  {   |  }   |  [   |  ]   | \    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_planck_grid(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  KC_BSPC,
    _______, _______, _______, _______, _______, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Numbers / Functions
 * ,-----------------------------------------------------------------------------------.
 * |      | F1  | F2   | F3    | F4   |      |  1   |  2   |  3   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | F5  | F6   | F7    | F8   |      |  4   |  5   |  6   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | F9  | F10  | F11   | F12  |  0   |  7   |  8   |  9   |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_1,    KC_2,    KC_3,    _______, _______, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_4,    KC_5,    KC_6,    _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_0,    KC_7,    KC_8,    KC_9,    _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * Swap GUI keys (Win/macOS)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | WIN  |      |      |      |      |             |      |      |      |      | MAC  |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    WIN,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MAC
)

};

#ifdef AUDIO_ENABLE
float adjust_song[][2]   = ADJUST_SONG;
float caps_on_song[][2]  = CAPSLOCK_ON_SONG;
float caps_off_song[][2] = CAPSLOCK_OFF_SONG;
float win_song[][2]      = WIN_SONG;
float mac_song[][2]      = MAC_SONG;
#endif

static bool is_capslock_on = false;
static bool is_mac = false;
uint8_t keycode_os_gui = KC_LGUI;
uint8_t keycode_os_ctl = KC_LCTL;


void td_lsft_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_on(2);
  }
  else {
    layer_on(3);
  }
}

void td_lsft_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(2);
  }
  else {
    layer_off(3);
  }
}

bool type_os_key_events(uint8_t keycode, bool is_pressed) {
  if (is_pressed) {
    register_code(keycode);
  }
  else {
    unregister_code(keycode);
  }

  return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  static bool is_adjust_on = false;
  layer_state_t newState = update_tri_layer_state(state, _SYMBOLS, _MOBILITY, _ADJUST);

  is_adjust_on = layer_state_cmp(newState, _ADJUST);

  if (is_adjust_on) {
    #ifdef AUDIO_ENABLE
      PLAY_SONG(adjust_song);
    #endif
  }

  return newState;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        is_capslock_on = !is_capslock_on;

        if (is_capslock_on) {
          #ifdef AUDIO_ENABLE
            PLAY_SONG(caps_on_song);
          #endif
        } else {
          #ifdef AUDIO_ENABLE
            PLAY_SONG(caps_off_song);
          #endif
        }
      }
      return true;
      break;
    case OS_GUI:
      keycode_os_gui = is_mac ? KC_LCTL : KC_LGUI;
      type_os_key_events(keycode_os_gui, record->event.pressed);
      break;
    case OS_CTL:
      keycode_os_ctl = is_mac ? KC_LGUI : KC_LCTL;
      type_os_key_events(keycode_os_ctl, record->event.pressed);
      break;
    case WIN:
      if (record->event.pressed) {
        is_mac = false;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(win_song);
        #endif
      }
      return false;
      break;
    case MAC:
      if (record->event.pressed) {
        is_mac = true;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(mac_song);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
