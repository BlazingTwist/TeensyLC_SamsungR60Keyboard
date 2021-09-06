#include <Arduino.h>

struct PressedKeyNode {
    short pins;
    short outPinIndex;
    short inPinIndex;
    PressedKeyNode *next = nullptr;
};

struct PressedKeyList {
public:
    PressedKeyNode *first = nullptr;
    PressedKeyNode *last = nullptr;

private:
    void Initialize(short pins, short outPinIndex, short inPinIndex) {
        PressedKeyNode *node = new PressedKeyNode;
        node->pins = pins;
        node->outPinIndex = outPinIndex;
        node->inPinIndex = inPinIndex;
        first = node;
        last = node;
    }

public:
    bool IsEmpty() {
        return first == nullptr;
    }

    void AddAsLast(short pins, short outPinIndex, short inPinIndex) {
        if (first == nullptr) {
            Initialize(pins, outPinIndex, inPinIndex);
            return;
        }

        PressedKeyNode *node = new PressedKeyNode;
        node->pins = pins;
        node->outPinIndex = outPinIndex;
        node->inPinIndex = inPinIndex;
        last->next = node;
        last = node;
    }

    void Clear() {
        if (first == nullptr) {
            return;
        }

        PressedKeyNode *current = first;
        while (current->next != nullptr) {
            PressedKeyNode *temp = current->next;
            delete current;
            current = temp;
        }
        delete current;
        first = nullptr;
        last = nullptr;
    }
};