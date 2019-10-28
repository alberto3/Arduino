/**
 * @name:			NodeID.h
 * @description:	Assign ID to the board upon setup via analog / digital pins
 * @author:			Albert Harounian
 * @since:			August 18, 2019
 */

#ifndef NODEID_H
#define NODEID_H

#include <Arduino.h>


class NodeID {

public:
    NodeID(uint8_t i_PinLSB, uint8_t i_PinMSB, uint8_t i_N=0, boolean i_UseEEPROM = true, uint8_t i_AddressEEPROM = 0);

    void Setup();

    void Setup(uint8_t i_ID, uint8_t i_N);

    uint8_t getID() const;

    uint8_t getN() const;

protected:
    static const uint16_t IdleTimeMs = 10;
    static const uint16_t AnalogValueThreshold = 1000;

    uint8_t m_PinLSB;
    uint8_t m_PinMSB;
    boolean m_UseEEPROM;
    uint8_t m_AddressEEPROM;
    uint8_t m_ID = 0;
    uint8_t m_N = 0;
};


#endif
