#include "CAN/Driver.hpp"
#include "CAN/Frame.hpp"
#include "CANGatekeeperTask.hpp"


CANGatekeeperTask::CANGatekeeperTask() : Task("CANGatekeeperTask") {
    CAN::initialize();

    outgoingQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), outgoingQueueStorageArea,
                                       &outgoingQueueBuffer);
    vQueueAddToRegistry(outgoingQueue, "CAN Outgoing");

    incomingSFQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), incomingSFQueueStorageArea,
                                       &incomingSFQueueBuffer);
    vQueueAddToRegistry(incomingSFQueue, "CAN Incoming SF");

    incomingMFQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), incomingSFQueueStorageArea,
                                         &incomingMFQueueBuffer);
    vQueueAddToRegistry(incomingSFQueue, "CAN Incoming MF");
}

static uint32_t thread_notification;

void CANGatekeeperTask::execute() {
    CAN::Frame out_message = {};
    CAN::Frame in_message = {};

    taskHandle = xTaskGetCurrentTaskHandle();

    uint32_t ulNotifiedValue;

    while (true) {

        xTaskNotifyWait(0, 0, &ulNotifiedValue, portMAX_DELAY);

        if(getIncomingSFMessagesCount()){
            xQueueReceive(incomingSFQueue, &in_message, portMAX_DELAY);
            CAN::TPProtocol::processSingleFrame(in_message);
        }
        CAN::TPProtocol::processMultipleFrames();

        if(uxQueueMessagesWaiting(outgoingQueue)){
            xQueueReceive(outgoingQueue, &out_message, portMAX_DELAY);
            CAN::send(out_message, ActiveBus);
        }
    }
}
