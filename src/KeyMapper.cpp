#include <Arduino.h>

#define escape_pins (short)(19 << 5) + 5
#define f1_pins (short)(19 << 5) + 18
#define f2_pins (short)(4 << 5) + 5
#define f3_pins (short)(4 << 5) + 18
#define f4_pins (short)(4 << 5) + 17
#define f5_pins (short)(20 << 5) + 5
#define f6_pins (short)(20 << 5) + 18
#define f7_pins (short)(3 << 5) + 5
#define f8_pins (short)(3 << 5) + 18
#define f9_pins (short)(21 << 5) + 5
#define f10_pins (short)(21 << 5) + 18
#define f11_pins (short)(2 << 5) + 5
#define f12_pins (short)(2 << 5) + 18
#define print_pins (short)(22 << 5) + 5
#define pause_pins (short)(1 << 5) + 5
#define insert_pins (short)(23 << 5) + 18
#define delete_pins (short)(1 << 5) + 18
#define cFlex_pins (short)(19 << 5) + 17
#define alpha1_pins (short)(19 << 5) + 16
#define alpha2_pins (short)(4 << 5) + 16
#define alpha3_pins (short)(4 << 5) + 8
#define alpha4_pins (short)(20 << 5) + 17
#define alpha5_pins (short)(20 << 5) + 16
#define alpha6_pins (short)(3 << 5) + 17
#define alpha7_pins (short)(3 << 5) + 16
#define alpha8_pins (short)(21 << 5) + 17
#define alpha9_pins (short)(21 << 5) + 16
#define alpha0_pins (short)(2 << 5) + 17
#define eszett_pins (short)(2 << 5) + 16
#define accent_pins (short)(22 << 5) + 18
#define backspace_pins (short)(23 << 5) + 5
#define pos1_pins (short)(1 << 5) + 17
#define tab_pins (short)(7 << 5) + 16
#define q_pins (short)(7 << 5) + 17
#define w_pins (short)(7 << 5) + 18
#define e_pins (short)(20 << 5) + 9
#define r_pins (short)(20 << 5) + 10
#define t_pins (short)(19 << 5) + 8
#define z_pins (short)(20 << 5) + 15
#define u_pins (short)(20 << 5) + 8
#define i_pins (short)(3 << 5) + 8
#define o_pins (short)(21 << 5) + 8
#define p_pins (short)(2 << 5) + 15
#define umlautU_pins (short)(2 << 5) + 8
#define plus_pins (short)(22 << 5) + 17
#define enter_pins (short)(3 << 5) + 10
#define pUp_pins (short)(23 << 5) + 17
#define caps_pins (short)(14 << 5) + 16
#define a_pins (short)(14 << 5) + 17
#define s_pins (short)(14 << 5) + 18
#define d_pins (short)(7 << 5) + 8
#define f_pins (short)(7 << 5) + 15
#define g_pins (short)(4 << 5) + 9
#define h_pins (short)(19 << 5) + 15
#define j_pins (short)(19 << 5) + 9
#define k_pins (short)(3 << 5) + 15
#define l_pins (short)(21 << 5) + 15
#define umlautO_pins (short)(2 << 5) + 9
#define umlautA_pins (short)(22 << 5) + 16
#define hash_pins (short)(14 << 5) + 5
#define pDown_pins (short)(4 << 5) + 15
#define leftShift_pins (short)(12 << 5) + 5
#define lessThan_pins (short)(22 << 5) + 15
#define y_pins (short)(14 << 5) + 8
#define x_pins (short)(14 << 5) + 15
#define c_pins (short)(14 << 5) + 9
#define v_pins (short)(7 << 5) + 10
#define b_pins (short)(7 << 5) + 9
#define n_pins (short)(19 << 5) + 10
#define m_pins (short)(3 << 5) + 9
#define comma_pins (short)(2 << 5) + 10
#define dot_pins (short)(21 << 5) + 9
#define dash_pins (short)(22 << 5) + 8
#define rightShift_pins (short)(12 << 5) + 18
#define end_pins (short)(23 << 5) + 16
#define function_pins (short)(14 << 5) + 10
#define leftControl_pins (short)(26 << 5) + 17
#define windows_pins (short)(24 << 5) + 9
#define alt_pins (short)(11 << 5) + 8
#define space_pins (short)(4 << 5) + 10
#define altRight_pins (short)(11 << 5) + 15
#define context_pins (short)(6 << 5) + 9
#define rightControl_pins (short)(26 << 5) + 16
#define house_pins (short)(21 << 5) + 10
#define arrowUp_pins (short)(1 << 5) + 10
#define arrowLeft_pins (short)(23 << 5) + 15
#define arrowDown_pins (short)(1 << 5) + 9
#define arrowRight_pins (short)(23 << 5) + 8

bool isFunctionKeyPressed = false;

void PressOrReleaseKey(int keyCode, bool isPressed) {
    if (isPressed) {
        Keyboard.press(keyCode);
    } else {
        Keyboard.release(keyCode);
    }
}

void HandleKeyChange(short pinCode, bool isPressed) {
    switch (pinCode) {
        case escape_pins:
            if (isPressed) {
                if (isFunctionKeyPressed) {
                    PressOrReleaseKey(KEY_SYSTEM_SLEEP, true);
                } else {
                    PressOrReleaseKey(KEY_ESC, true);
                }
            }else{
                PressOrReleaseKey(KEY_SYSTEM_SLEEP, false);
                PressOrReleaseKey(KEY_ESC, false);
            }
            break;
        case f1_pins:
            PressOrReleaseKey(KEY_F1, isPressed);
            break;
        case f2_pins:
            PressOrReleaseKey(KEY_F2, isPressed);
            break;
        case f3_pins:
            PressOrReleaseKey(KEY_F3, isPressed);
            break;
        case f4_pins:
            PressOrReleaseKey(KEY_F4, isPressed);
            break;
        case f5_pins:
            PressOrReleaseKey(KEY_F5, isPressed);
            break;
        case f6_pins:
            if (isPressed) {
                if (isFunctionKeyPressed) {
                    PressOrReleaseKey(KEY_MEDIA_MUTE, true);
                } else {
                    PressOrReleaseKey(KEY_F6, true);
                }
            }else{
                PressOrReleaseKey(KEY_MEDIA_MUTE, false);
                PressOrReleaseKey(KEY_F6, false);
            }
            break;
        case f7_pins:
            PressOrReleaseKey(KEY_F7, isPressed);
            break;
        case f8_pins:
            PressOrReleaseKey(KEY_F8, isPressed);
            break;
        case f9_pins:
            PressOrReleaseKey(KEY_F9, isPressed);
            break;
        case f10_pins:
            PressOrReleaseKey(KEY_F10, isPressed);
            break;
        case f11_pins:
            PressOrReleaseKey(KEY_F11, isPressed);
            break;
        case f12_pins:
            PressOrReleaseKey(KEY_F12, isPressed);
            break;
        case print_pins:
            PressOrReleaseKey(KEY_PRINTSCREEN, isPressed);
            break;
        case pause_pins:
            PressOrReleaseKey(KEY_PAUSE, isPressed);
            break;
        case insert_pins:
            PressOrReleaseKey(KEY_INSERT, isPressed);
            break;
        case delete_pins:
            PressOrReleaseKey(KEY_DELETE, isPressed);
            break;
        case cFlex_pins:
            PressOrReleaseKey(KEY_TILDE, isPressed);
            break;
        case alpha1_pins:
            PressOrReleaseKey(KEY_1, isPressed);
            break;
        case alpha2_pins:
            PressOrReleaseKey(KEY_2, isPressed);
            break;
        case alpha3_pins:
            PressOrReleaseKey(KEY_3, isPressed);
            break;
        case alpha4_pins:
            PressOrReleaseKey(KEY_4, isPressed);
            break;
        case alpha5_pins:
            PressOrReleaseKey(KEY_5, isPressed);
            break;
        case alpha6_pins:
            PressOrReleaseKey(KEY_6, isPressed);
            break;
        case alpha7_pins:
            PressOrReleaseKey(KEY_7, isPressed);
            break;
        case alpha8_pins:
            PressOrReleaseKey(KEY_8, isPressed);
            break;
        case alpha9_pins:
            PressOrReleaseKey(KEY_9, isPressed);
            break;
        case alpha0_pins:
            PressOrReleaseKey(KEY_0, isPressed);
            break;
        case eszett_pins:
            PressOrReleaseKey(KEY_MINUS, isPressed);
            break;
        case accent_pins:
            PressOrReleaseKey(KEY_EQUAL, isPressed);
            break;
        case backspace_pins:
            PressOrReleaseKey(KEY_BACKSPACE, isPressed);
            break;
        case pos1_pins:
            PressOrReleaseKey(KEY_HOME, isPressed);
            break;
        case tab_pins:
            PressOrReleaseKey(KEY_TAB, isPressed);
            break;
        case q_pins:
            PressOrReleaseKey(KEY_Q, isPressed);
            break;
        case w_pins:
            PressOrReleaseKey(KEY_W, isPressed);
            break;
        case e_pins:
            PressOrReleaseKey(KEY_E, isPressed);
            break;
        case r_pins:
            PressOrReleaseKey(KEY_R, isPressed);
            break;
        case t_pins:
            PressOrReleaseKey(KEY_T, isPressed);
            break;
        case z_pins:
            PressOrReleaseKey(KEY_Y, isPressed); // german layout is weird.
            break;
        case u_pins:
            PressOrReleaseKey(KEY_U, isPressed);
            break;
        case i_pins:
            PressOrReleaseKey(KEY_I, isPressed);
            break;
        case o_pins:
            PressOrReleaseKey(KEY_O, isPressed);
            break;
        case p_pins:
            PressOrReleaseKey(KEY_P, isPressed);
            break;
        case umlautU_pins:
            PressOrReleaseKey(KEY_LEFT_BRACE, isPressed);
            break;
        case plus_pins:
            PressOrReleaseKey(KEY_RIGHT_BRACE, isPressed);
            break;
        case enter_pins:
            PressOrReleaseKey(KEY_RETURN, isPressed);
            break;
        case pUp_pins:
            PressOrReleaseKey(KEY_PAGE_UP, isPressed);
            break;
        case caps_pins:
            PressOrReleaseKey(KEY_CAPS_LOCK, isPressed);
            break;
        case a_pins:
            PressOrReleaseKey(KEY_A, isPressed);
            break;
        case s_pins:
            PressOrReleaseKey(KEY_S, isPressed);
            break;
        case d_pins:
            PressOrReleaseKey(KEY_D, isPressed);
            break;
        case f_pins:
            PressOrReleaseKey(KEY_F, isPressed);
            break;
        case g_pins:
            PressOrReleaseKey(KEY_G, isPressed);
            break;
        case h_pins:
            PressOrReleaseKey(KEY_H, isPressed);
            break;
        case j_pins:
            PressOrReleaseKey(KEY_J, isPressed);
            break;
        case k_pins:
            PressOrReleaseKey(KEY_K, isPressed);
            break;
        case l_pins:
            PressOrReleaseKey(KEY_L, isPressed);
            break;
        case umlautO_pins:
            PressOrReleaseKey(KEY_SEMICOLON, isPressed);
            break;
        case umlautA_pins:
            PressOrReleaseKey(KEY_QUOTE, isPressed);
            break;
        case hash_pins:
            PressOrReleaseKey(KEY_BACKSLASH, isPressed);
            break;
        case pDown_pins:
            PressOrReleaseKey(KEY_PAGE_DOWN, isPressed);
            break;
        case leftShift_pins:
            PressOrReleaseKey(KEY_LEFT_SHIFT, isPressed);
            break;
        case lessThan_pins:
            PressOrReleaseKey(KEY_NON_US_BS, isPressed);
            break;
        case y_pins:
            PressOrReleaseKey(KEY_Z, isPressed); // german layout is weird.
            break;
        case x_pins:
            PressOrReleaseKey(KEY_X, isPressed);
            break;
        case c_pins:
            PressOrReleaseKey(KEY_C, isPressed);
            break;
        case v_pins:
            PressOrReleaseKey(KEY_V, isPressed);
            break;
        case b_pins:
            PressOrReleaseKey(KEY_B, isPressed);
            break;
        case n_pins:
            PressOrReleaseKey(KEY_N, isPressed);
            break;
        case m_pins:
            PressOrReleaseKey(KEY_M, isPressed);
            break;
        case comma_pins:
            PressOrReleaseKey(KEY_COMMA, isPressed);
            break;
        case dot_pins:
            PressOrReleaseKey(KEY_PERIOD, isPressed);
            break;
        case dash_pins:
            PressOrReleaseKey(KEY_SLASH, isPressed);
            break;
        case rightShift_pins:
            PressOrReleaseKey(KEY_RIGHT_SHIFT, isPressed);
            break;
        case end_pins:
            PressOrReleaseKey(KEY_END, isPressed);
            break;
        case function_pins:
            isFunctionKeyPressed = isPressed;
            // function key: is pressed, trigger different key
            // on release: release all relevant keys
            break;
        case leftControl_pins:
            PressOrReleaseKey(KEY_LEFT_CTRL, isPressed);
            break;
        case windows_pins:
            PressOrReleaseKey(KEY_LEFT_GUI, isPressed);
            break;
        case alt_pins:
            PressOrReleaseKey(KEY_LEFT_ALT, isPressed);
            break;
        case space_pins:
            PressOrReleaseKey(KEY_SPACE, isPressed);
            break;
        case altRight_pins:
            PressOrReleaseKey(KEY_RIGHT_ALT, isPressed);
            break;
        case context_pins:
            PressOrReleaseKey(KEY_MENU, isPressed);
            break;
        case rightControl_pins:
            PressOrReleaseKey(KEY_RIGHT_CTRL, isPressed);
            break;
        case house_pins:
            PressOrReleaseKey(KEY_HOME, isPressed);
            break;
        case arrowUp_pins:
            PressOrReleaseKey(KEY_UP_ARROW, isPressed);
            break;
        case arrowLeft_pins:
            if (isPressed) {
                if (isFunctionKeyPressed) {
                    PressOrReleaseKey(KEY_MEDIA_VOLUME_DEC, true);
                } else {
                    PressOrReleaseKey(KEY_LEFT_ARROW, true);
                }
            }else{
                PressOrReleaseKey(KEY_MEDIA_VOLUME_DEC, false);
                PressOrReleaseKey(KEY_LEFT_ARROW, false);
            }
            break;
        case arrowDown_pins:
            PressOrReleaseKey(KEY_DOWN_ARROW, isPressed);
            break;
        case arrowRight_pins:
            if (isPressed) {
                if (isFunctionKeyPressed) {
                    PressOrReleaseKey(KEY_MEDIA_VOLUME_INC, true);
                } else {
                    PressOrReleaseKey(KEY_RIGHT_ARROW, true);
                }
            }else{
                PressOrReleaseKey(KEY_MEDIA_VOLUME_INC, false);
                PressOrReleaseKey(KEY_RIGHT_ARROW, false);
            }
            break;
    }
}