#include <EEPROM.h>
#include "NodeID.h"

NodeID::NodeID(uint8_t i_PinLSB, uint8_t i_PinMSB, uint8_t i_N, boolean i_UseEEPROM, uint8_t i_AddressEEPROM) {
    m_PinLSB = i_PinLSB;
    m_PinMSB = i_PinMSB;
    m_N = i_N;
    m_UseEEPROM = i_UseEEPROM;
    m_AddressEEPROM = i_AddressEEPROM;
}

void NodeID::Setup() {
    delay(IdleTimeMs);

    uint8_t range = m_PinMSB - m_PinLSB + 1;
    uint8_t len = m_N == 0 ? range >> 1u : range;
    uint8_t number = 0;

    /*
    for (uint8_t i = 0; i < range; ++i) {
        uint8_t pin = m_PinMSB - i;

        number <<= 1u;

        pinMode(pin, INPUT_PULLUP);

        if (pin >= A0 && pin <= A7) {
            uint16_t val = analogRead(pin);
            number |= (val == 0 ? 0x1u : 0x0u);
        } else {
            uint8_t val = digitalRead(pin) == LOW ? 0x1u : 0x0u;
            number |= val;
        }
    }
    */

    if (m_UseEEPROM) {
        if (number > 0) {
            EEPROM.update(m_AddressEEPROM, number);
        } else {
            number = EEPROM[m_AddressEEPROM];
        }
    }

    if (number > 0) {
        unsigned int maxID = 1u << len;

        if (m_N == 0) {
            m_ID = number & (maxID - 1);
            m_N = number >> len;

            if (m_ID >= maxID || m_N >= maxID) {
                m_ID = m_N = 0;
            }
        } else if (number < maxID) {
            m_ID = number;
        } else {
            m_ID = 0;
        }
    }
}

void NodeID::Setup(uint8_t i_ID, uint8_t i_N) {
    m_ID = i_ID;
    m_N = i_N;
}

uint8_t NodeID::getID() const {
    return m_ID;
}

uint8_t NodeID::getN() const {
    return m_N;
}
