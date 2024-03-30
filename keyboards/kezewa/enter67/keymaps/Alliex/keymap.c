/* Copyright 2022 LXF-YZP(yuezp)
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

enum custom_keycodes {
    REFWKND = SAFE_RANGE,
	PCST,
	LSTR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case REFWKND:
        if (record->event.pressed) {
            // when keycode REFWKND is pressed
            SEND_STRING("This has been cleaned up and will refresh fully over the weekend.");
        } else {
            // when keycode REFWKND is released
        }
        break;
	
	case PCST:
        if (record->event.pressed) {
            // when keycode REFWKND is pressed
            SEND_STRING("7767");
        } else {
            // when keycode REFWKND is released
        }
        break;
	
	case LSTR:
        if (record->event.pressed) {
            // when keycode REFWKND is pressed
            SEND_STRING("");
        } else {
            // when keycode REFWKND is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0]=LAYOUT_65_ansi_blocker(
    KC_ESC,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
    KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
    KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    MO(1),   KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

[1]=LAYOUT_65_ansi_blocker(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,          KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,    MO(2),                            KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

[2]=LAYOUT_65_ansi_blocker(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, REFWKND, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, PCST,    KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSTR, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS)

};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, HSV_PURPLE);
                }
            }
        }
    }
    return false;
}

/*
const rgblight_segment_t PROGMEM my_code_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GREEN},
	{13, 1, HSV_ORANGE},
    {45, 1, HSV_RED},
    {46, 2, HSV_BLUE},
    {48, 2, HSV_PURPLE},
    {50, 2, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_dummy_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_GOLD},
    {25, 1, HSV_SPRINGGREEN},
	{39, 1, HSV_TURQUOISE},
	{53, 1, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_code_layer,
    my_dummy_layer     // last layter Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
	rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    return state;
}*/
