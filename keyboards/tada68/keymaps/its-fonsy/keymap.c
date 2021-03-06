#include QMK_KEYBOARD_H
#include <keymap_italian.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _IT 0
#define _FL 1
#define _SL 2 // shifted layer
#define _US 3

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

//Tap dance enums
enum {
  ALT_OSL1 = 0
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _IT: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
     * |----------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
	 * KC_SCLN = ;
     */
    [_IT] = LAYOUT_65_ansi(
        KC_ESC,  IT_1,    IT_2,    IT_3,    IT_4,    IT_5,    IT_6,    IT_7,    IT_8,    IT_9,    IT_0,     IT_MINS,   IT_EQL,    KC_BSPC, RALT(KC_MINS),
        KC_TAB,  IT_Q,    IT_W,    IT_E,    IT_R,    IT_T,    IT_Y,    IT_U,    IT_I,    IT_O,    IT_P,     IT_LBRC,   IT_RBRC,   IT_BSLS, KC_DEL,
        KC_CAPS, IT_A,    IT_S,    IT_D,    IT_F,    IT_G,    IT_H,    IT_J,    IT_K,    IT_L,    IT_SCLN,	IT_QUOT,              KC_ENT,  KC_PGUP,
        MO(_SL),          IT_Z,    IT_X,    IT_C,    IT_V,    IT_B,    IT_N,    IT_M,    IT_COMM, IT_DOT,  	IT_SLSH,   MO(_SL),   KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, TD(ALT_OSL1),                       KC_SPC,                    KC_RALT, MO(_FL), 	KC_RCTL,   KC_LEFT,   KC_DOWN, KC_RGHT
    ),

    /* Keymap _FL: Function Layer
     * ,----------------------------------------------------------------.
     * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
     * |----------------------------------------------------------------|
     * |L=IT |   |   |è  |   |   |   |ù  |ì  |ò  |   |   |   |     |Hme |
     * |----------------------------------------------------------------|
     * |L=US  |à  |   |   |   |   |   |   |   |   |   |   |        |End |
     * |----------------------------------------------------------------|
     * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |      |   |    |
     * |----------------------------------------------------------------|
     * |    |    |    |                       |   |   |    |   |   |    |
     * `----------------------------------------------------------------'
     */
    [_FL] = LAYOUT_65_ansi(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______,  _______, _______, IT_EGRV, _______, _______, _______, IT_UGRV, IT_IGRV, IT_OGRV, _______, _______, _______, _______, KC_HOME,
        _______,  IT_AGRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_END,
        KC_LSFT,           _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, DF(_US),
        _______, _______, _______,                            _______,                    _______, _______, _______, _______, _______, _______
    ),

    [_SL] = LAYOUT_65_ansi(
        S(KC_ESC),  IT_EXLM, IT_AT,    IT_HASH,  IT_DLR,   IT_PERC,  IT_CIRC,  IT_AMPR,  IT_ASTR,  IT_LPRN,  IT_RPRN,     IT_UNDS,    IT_PLUS,    S(KC_BSPC),  RALT(KC_EQL),
        S(KC_TAB),  S(KC_Q), S(KC_W),  S(KC_E),  S(KC_R),  S(KC_T),  S(KC_Y),  S(KC_U),  S(KC_I),  S(KC_O),  S(KC_P),     IT_LCBR,    IT_RCBR,    IT_PIPE,     S(KC_DEL),
        S(KC_CAPS), S(KC_A), S(KC_S),  S(KC_D),  S(KC_F),  S(KC_G),  S(KC_H),  S(KC_J),  S(KC_K),  S(KC_L),  IT_COLN,     IT_DQUO,                S(KC_ENT),   S(KC_PGUP),
        _______,             S(KC_Z),  S(KC_X),  S(KC_C),  S(KC_V),  S(KC_B),  S(KC_N),  S(KC_M),  IT_LABK,  S(IT_LABK),  IT_QUES,    S(KC_RSFT), S(KC_UP),    S(KC_PGDN),
        S(KC_LCTL), S(KC_LGUI), _______,                       S(KC_SPC),                S(KC_RALT), _______, S(KC_RCTL), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)
	),
	    /* Keymap _US: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
     * |----------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [_US] = LAYOUT_65_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(1); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case RESET:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()){
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    default:
      return true;
  }
  return true;
}
