#pragma once
#include "Task.hpp"

#ifdef STM32
extern ADC_HandleTypeDef hadc3;
#endif


/**
 * FreeRTOS task for periodically printing the value of the internal temperature sensor.
 */
class MCUTemperatureTask : public Task {
private:
    const uint16_t delayMs = 10000;

    const static inline uint16_t TaskStackDepth = 1000;

    StackType_t taskStack[TaskStackDepth];

    #ifdef STM32
        /**
         * The value tsCal1 may change based on the datasheet. For STM32H7A3ZIQ it is stored in the memory address 0x08FFF814
         * and it is provided by the manufacturer
        */
        inline static constexpr float tsCal1 = 12173.0F;
        /**
         * The value tsCal2 may change based on the datasheet. For STM32H7A3ZIQ it is stored in the memory address 0x08FFF818
         * and it is provided by the manufacturer
        */
        inline static constexpr float tsCal2 = 16120.0F;
        inline static constexpr float tsCal1Temp = 30.0F;
        inline static constexpr float tsCal2Temp = 130.0F;
        inline static constexpr uint16_t timeoutPollForConversion = 100;
        inline static constexpr uint16_t formatPrecision = 3;
    #endif

public:
    void execute();

    MCUTemperatureTask() : Task("MCUTemperatureSensor") {}

    void createTask() {
        xTaskCreateStatic(vClassTask<MCUTemperatureTask>, this->TaskName, MCUTemperatureTask::TaskStackDepth, this,
                          tskIDLE_PRIORITY + 2, this->taskStack, &(this->taskBuffer));
    }

};

inline std::optional<MCUTemperatureTask> mcuTemperatureTask;