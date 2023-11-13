#pragma once
#include "Task.hpp"
#ifndef STM32
#include "MCP9808.hpp"


/**
 * FreeRTOS task for periodically printing the value of the MCP9808 external temperature sensor.
 */
class AmbientTemperatureTask : public Task {
private:
    const uint16_t DelayMs = 1000;

    /**
     * The driver for the MCP9808 temperature sensor
     */
    MCP9808 sensor;

    /**
     * The value of the temperature, measured in Celsius
     */
    float ambientTemperature;

    const static inline uint16_t TaskStackDepth = 2000;

    StackType_t taskStack[TaskStackDepth];

public:
    void execute();

    AmbientTemperatureTask() : Task("ExternalTemperatureSensor") {}

    void createTask() {
        xTaskCreateStatic(vClassTask<AmbientTemperatureTask>, this->TaskName,
                          AmbientTemperatureTask::TaskStackDepth, this, tskIDLE_PRIORITY + 2, this->taskStack,
                          &(this->taskBuffer));
    }

};

inline std::optional<AmbientTemperatureTask> ambientTemperatureTask;

#endif