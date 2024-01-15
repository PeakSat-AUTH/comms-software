#pragma once

#include "etl/vector.h"

class GNSSMessage {
    etl::vector<uint8_t, 2> startOfSequence = {0xA0, 0xA1};
    etl::vector<uint8_t, 2> endOfSequence = {0x0D, 0x0A};
    uint16_t payloadLength = 0;

    etl::vector<uint8_t, 256> messageBody;

    static uint8_t calculateChecksum(uint8_t payloadLength, etl::vector<uint8_t, 256> payload) {
        uint8_t checksum = 0;
        for (auto byte: payload) {
            checksum ^= byte;
        }
        return checksum;
    }

public:
    GNSSMessage(uint8_t id, uint16_t payloadLength, const etl::vector<uint8_t, 256>& payload) {

        messageBody.push_back(startOfSequence[0]);
        messageBody.push_back(startOfSequence[1]);
        messageBody.push_back((payloadLength >> 8) & 0xFF);
        messageBody.push_back(payloadLength & 0xFF);
        for (uint8_t byte: payload) {
            messageBody.push_back(byte);
        }
        messageBody.push_back(calculateChecksum(payloadLength, payload));
        messageBody.push_back(endOfSequence[0]);
        messageBody.push_back(endOfSequence[1]);
    }
};