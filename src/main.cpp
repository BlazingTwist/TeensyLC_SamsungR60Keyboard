#include <Arduino.h>
#include "PressedKeyList.cpp"
#include "KeyStateManager.cpp"
#include "KeyMapper.cpp"

KeyStateManager *keyStateManager = new KeyStateManager;
PressedKeyList *justPressedKeys = new PressedKeyList;
PressedKeyList *justReleasedKeys = new PressedKeyList;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    keyStateManager->SetupPins();

    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

void OnPinChange(short outPin, short outPinIndex, short inPin, short inPinIndex, short pinCode, bool isPressed) {
    if (isPressed) {
        justPressedKeys->AddAsLast(pinCode, outPinIndex, inPinIndex);
    } else {
        justReleasedKeys->AddAsLast(pinCode, outPinIndex, inPinIndex);
    }
}

bool capsLockActive = false;
#define CAPS_LED_ID 1
bool ledIsOn = false;

void loop() {
    if (capsLockActive ^ ((keyboard_leds >> CAPS_LED_ID) & 0b1)) {
        capsLockActive = !capsLockActive;
    }
    if ((capsLockActive || isFunctionKeyPressed) ^ ledIsOn){
        ledIsOn = !ledIsOn;
        digitalWrite(LED_BUILTIN, ledIsOn ? HIGH : LOW);
    }

    keyStateManager->CallForeachPinChange((KeyStateManager::keyPinCallback) OnPinChange);

    if (!justReleasedKeys->IsEmpty()) {
        PressedKeyNode *current = justReleasedKeys->first;
        do {
            keyStateManager->SetKeyPressed(current->outPinIndex, current->inPinIndex, false);
            HandleKeyChange(current->pins, false);
        } while ((current = current->next) != nullptr);
        justReleasedKeys->Clear();
    }

    if (!justPressedKeys->IsEmpty()) {

        int activeOutPins = 0;
        int rowedOutPins = 0;
        short activeInPins = 0;
        short rowedInPins = 0;

        PressedKeyNode *current = justPressedKeys->first;
        do {
            short outPinIndex = current->outPinIndex;
            short inPinIndex = current->inPinIndex;

            if ((activeOutPins >> outPinIndex) & 0b1) {
                rowedOutPins |= (0b1 << outPinIndex);
            } else {
                activeOutPins |= (0b1 << outPinIndex);
            }

            if ((activeInPins >> inPinIndex) & 0b1) {
                rowedInPins |= (0b1 << inPinIndex);
            } else {
                activeInPins |= (0b1 << inPinIndex);
            }
        } while ((current = current->next) != nullptr);
        keyStateManager->GetRowedPins(activeOutPins, activeInPins, rowedOutPins, rowedInPins);

        current = justPressedKeys->first;
        do {
            short outPinIndex = current->outPinIndex;
            short inPinIndex = current->inPinIndex;

            // if the key has at least one non-rowed pin -> trigger, otherwise block (do nothing)
            if (!((rowedOutPins >> outPinIndex) & 0b1) || !((rowedInPins >> inPinIndex) & 0b1)) {
                keyStateManager->SetKeyPressed(outPinIndex, inPinIndex, true);
                HandleKeyChange(current->pins, true);
            }
        } while ((current = current->next) != nullptr);

        justPressedKeys->Clear();
    }

    delay(16);
}