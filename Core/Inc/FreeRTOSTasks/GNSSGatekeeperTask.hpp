#pragma once

#include "Task.hpp"
#include "minmea.h"
#include "COMMS_Definitions.hpp"
#include "queue.h"

extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart3;

class GNSSGatekeeperTask : public Task {
public:
    /**
     * @see ParameterStatisticsService
     */
    void execute();

    const static inline uint16_t TaskStackDepth = 1200;

    StackType_t taskStack[TaskStackDepth];

    GNSSGatekeeperTask() : Task("StatisticsReporting") {
        gnssQueueHandle = xQueueCreateStatic(GNSSQueueSize, sizeof(GNSSMessage),
                                                messageQueueStorageArea,
                                                &gnssQueue);
        configASSERT(gnssQueueHandle);

        // disabling the half buffer interrupt //
        __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
        // disabling the full buffer interrupt //
        __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_TC);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, reinterpret_cast<uint8_t *>(incomingMessage.data()), TcCommandSize);
    }

    /**
     * Create freeRTOS Task
     */
    void createTask() {
        xTaskCreateStatic(vClassTask < GNSSGatekeeperTask > , this->TaskName,
                          GNSSGatekeeperTask::TaskStackDepth, this, tskIDLE_PRIORITY + 1,
                          this->taskStack, &(this->taskBuffer));
    }
private:
    /**
    * Buffer that holds the data of the DMA
    */
    typedef etl::string<MaxGNSSMessageSize> GNSSMessage;
    GNSSMessage incomingMessage;

    /**
     * Queue for incoming messages
     */
    uint8_t messageQueueStorageArea[GNSSQueueSize * sizeof(GNSSMessage)];
    StaticQueue_t gnssQueue;
    QueueHandle_t gnssQueueHandle;
};

inline std::optional<GNSSGatekeeperTask> gnssGatekeeperTask;

