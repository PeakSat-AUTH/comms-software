#include "CAN.hpp"
#include "CAN/ApplicationLayer.hpp"
#include "CANGatekeeperTask.hpp"

void CANTestTask::execute() {

    CAN::CANBuffer_t message = {};
    /**
     * Simple 64 byte message sending
     */

    for (uint8_t idx = 0; idx < CAN::Frame::MaxDataLength; idx++) {
        message.push_back(idx);
    }
    String<ECSSMaxMessageSize> testPayload("Hello World! 1");
    while (true) {
        CAN::Application::createLogMessage(CAN::NodeIDs::OBC, false, testPayload.data(), false);
        xTaskNotify(canGatekeeperTask->taskHandle, 0, eNoAction);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}