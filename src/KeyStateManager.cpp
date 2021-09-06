#include <Arduino.h>

#define outPinCount 16
#define inPinCount 8

#define OutPins const short outPins[] = {1, 2, 3, 4, 6, 7, 11, 12, 14, 19, 20, 21, 22, 23, 24, 26};

#define InPins const short inPins[] = {5, 8, 9, 10, 15, 16, 17, 18};

#define OutToInPinMapping const bool outToInPinMapping[outPinCount][inPinCount] = { \
{1, 0, 1, 1, 0, 0, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{0, 0, 1, 0, 0, 0, 0, 0},\
{0, 1, 1, 1, 1, 1, 1, 1},\
{0, 1, 0, 0, 1, 0, 0, 0},\
{1, 0, 0, 0, 0, 0, 0, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 1, 1, 1, 1, 1, 1},\
{1, 1, 0, 0, 1, 1, 1, 1},\
{1, 1, 0, 0, 1, 1, 1, 1},\
{0, 0, 1, 0, 0, 0, 0, 0},\
{0, 0, 0, 0, 0, 1, 1, 0},\
};

struct KeyStateManager {

private:
    unsigned long keyStates[4];

public:
    typedef void (*keyPinCallback)(short outPin, short outPinIndex, short inPin, short inPinIndex, short pinCode, bool isPressed);

private:
    void PrepareOutPin(short outPin) {
        pinMode(outPin, OUTPUT);
        delayMicroseconds(20);
        digitalWrite(outPin, HIGH);
        delayMicroseconds(20);
    }

    void ResetOutPin(short outPin) {
        digitalWrite(outPin, LOW);
        delayMicroseconds(20);
        pinMode(outPin, INPUT_DISABLE);
        delayMicroseconds(20);
    }

    bool IsPinConnected(short inPin) {
        return digitalRead(inPin) == HIGH;
    }

public:

    void SetupPins() {
        keyStates[0] = 0;
        keyStates[1] = 0;
        keyStates[2] = 0;
        keyStates[3] = 0;

        OutPins
        for (const auto &item: outPins) {
            pinMode(item, INPUT_DISABLE);
        }

        InPins
        for (const auto &item: inPins) {
            pinMode(item, INPUT_PULLDOWN);
        }
    }

    void CallForeachPinChange(keyPinCallback callback) {
        OutPins
        InPins
        OutToInPinMapping

        short keyStateIndex = 0;
        unsigned long *targetKeyState = &keyStates[0];
        short modifierShiftCount = 0;
        long modifierValue = 0b1;

        short outPinIndex = -1;
        for (const auto &outPin: outPins) {
            outPinIndex++;
            PrepareOutPin(outPin);
            short outPinCode = outPin << 5;

            short inPinIndex = -1;
            for (const auto &inPin: inPins) {
                inPinIndex++;

                if (outToInPinMapping[outPinIndex][inPinIndex]) {
                    short pinCode = outPinCode + inPin;

                    bool isStatePressed = ((*targetKeyState) & modifierValue) > 0;
                    bool isPinConnected = IsPinConnected(inPin);
                    if (isStatePressed ^ isPinConnected) {
                        callback(outPin, outPinIndex, inPin, inPinIndex, pinCode, isPinConnected);
                    }
                }

                modifierShiftCount++;
                modifierValue <<= 1;
                if (modifierShiftCount == 32) {
                    modifierShiftCount = 0;
                    keyStateIndex++;
                    targetKeyState = &keyStates[keyStateIndex];
                    modifierValue = 0b1;
                }
            }

            ResetOutPin(outPin);
        }
    }

    void SetKeyPressed(short outPinIndex, short inPinIndex, bool isPressed) {
        short pinStateIndex = outPinIndex / 4;
        short outPinShiftAmount = (outPinIndex % 4) * 8;
        long keyStateModifier = (0b1 << (outPinShiftAmount + inPinIndex));
        unsigned long targetKeyState = keyStates[pinStateIndex];
        bool isStatePressed = (targetKeyState & keyStateModifier) > 0;
        if (isStatePressed ^ isPressed) {
            keyStates[pinStateIndex] ^= keyStateModifier;
        }
    }

    bool GetAnyKeyPressed_out(byte outPinIndex) {
        // return true if any key involving this outPinIndex is pressed
        byte pinStateIndex = outPinIndex / 4;
        byte outPinShiftAmount = (outPinIndex % 4) * 8;
        byte relevantBits = (keyStates[pinStateIndex] >> outPinShiftAmount) & 0b11111111;
        return relevantBits > 0;
    }

    bool GetAnyKeyPressed_in(byte inPinIndex) {
        // return true if any key involving this inPinIndex is pressed
        for (const auto &keyState: keyStates) {
            unsigned long adjustedKeyState = keyState >> inPinIndex;
            if ((adjustedKeyState & 0x01010101) > 0) { // 1 on every 8th bit
                return true;
            }
        }
        return false;
    }

    void GetRowedPins(int activeOutPins, short activeInPins, int &rowedOutPins, short &rowedInPins) {
        for (byte i = 0; i < 16; ++i, activeOutPins >>= 1) {
            if ((rowedOutPins >> i) & 0b1) {
                continue; // pin already marked as row-pin.
            }
            if (activeOutPins & 0b1) {
                // outPinIndex i is active -> if any pressedState for this pin, mark as rowedPin
                if (GetAnyKeyPressed_out(i)) {
                    rowedOutPins |= (0b1 << i);
                }
            }
        }
        for (byte i = 0; i < 8; ++i, activeInPins >>= 1) {
            if ((rowedInPins >> i) & 0b1) {
                continue; // pin already marked as row-pin.
            }
            if (activeInPins & 0b1) {
                // inPinIndex i is active -> if any pressedState for this pin, mark as rowedPin
                if (GetAnyKeyPressed_in(i)) {
                    rowedInPins |= (0b1 << i);
                }
            }
        }
    }

};