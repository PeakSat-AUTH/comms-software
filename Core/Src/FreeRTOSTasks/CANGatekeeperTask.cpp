#include "CAN/Driver.hpp"
#include "CAN/Frame.hpp"
#include "CANGatekeeperTask.hpp"


CANGatekeeperTask::CANGatekeeperTask() : Task("CANGatekeeperTask") {
    CAN::initialize();

    outgoingQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), outgoingQueueStorageArea,
                                       &outgoingQueueBuffer);
    vQueueAddToRegistry(outgoingQueue, "CAN Outgoing");

    incomingQueue = xQueueCreateStatic(CAN::FrameQueueSize, sizeof(CAN::Frame), incomingQueueStorageArea,
                                       &incomingQueueBuffer);
    vQueueAddToRegistry(incomingQueue, "CAN Incoming");
}

void CANGatekeeperTask::execute() {
    CAN::Frame out_message = {};
    CAN::Frame in_message = {};

    while (true) {
        xQueueReceive(outgoingQueue, &out_message, portMAX_DELAY);
        CAN::send(out_message);

        if(uxQueueMessagesWaiting(incomingQueue) > 1){
            CAN::TPProtocol::processMultipleFrames();
        }else{
            if(xQueueReceive(incomingQueue, &in_message, portMAX_DELAY) == pdTRUE){
                CAN::TPProtocol::processSingleFrame(in_message);
            }
        }

    }
}
