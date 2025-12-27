// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐       ┌───┐
     * │ < │|| │ > │       │ M │
     * └───┴───┴───┘       └───┘
     * 
     * ┌───┬───┬───┬───┬───┬───┐
     * │F13│F14│F15│F16│F17│F18│
     * ├───┼───┼───┼───┼───┼───┤
     * │F19│F20│F21│F22│F23│F24│
     * └───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_MPRV,   KCMPLY,   KC_MNXT,   KC_AUDIO_MUTE,
        KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,
        KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_F24,
    )
}
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTION] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;  // or OLED_ROTATION_180, etc.
}
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(HSV_CYAN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0: rgblight_sethsv_noeeprom(HSV_CYAN);   break;
        case 1: rgblight_sethsv_noeeprom(HSV_PURPLE); break;
        default: rgblight_sethsv_noeeprom(HSV_RED);   break;
    }
    return state;
}

bool oled_task_user(void) {
    oled_write_ln_P(PSTR("Hello OLED"), false);
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0: oled_write_ln_P(PSTR("0"), false); break;
        case 1: oled_write_ln_P(PSTR("1"), false); break;
        default: oled_write_ln_P(PSTR("?"), false); break;
    }
    return false;
}
