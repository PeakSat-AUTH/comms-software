#include "MCUTemperatureTask.hpp"

void MCUTemperatureTask::execute() {
    #ifdef STM32
    #else
    AFEC0_ConversionStart();
    #endif

    while (true) {
        #ifdef STM32
        HAL_ADC_Start(&hadc3);
        HAL_ADC_PollForConversion(&hadc3, timeoutPollForConversion);
        uint16_t adcValue = HAL_ADC_GetValue(&hadc3);
        float avgSlope = (tsCal2Temp - tsCal1Temp) / (tsCal2 - tsCal1);
        float temperature = avgSlope * (static_cast<float>(adcValue) - tsCal1) + tsCal1Temp;
        Logger::format.precision(formatPrecision);
        LOG_DEBUG << "MCU Internal Temperature is " << temperature;
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        HAL_ADC_Stop(&hadc3);
        #else
        AFEC0_ConversionStart();
        vTaskDelay(pdMS_TO_TICKS(1));
        uint16_t ADCconversion = AFEC0_ChannelResultGet(AFEC_CH11);
        float voltageConversion = static_cast<float>(ADCconversion) * PositiveVoltageReference / MaxADCValue;
        const float MCUtemperature =
                (voltageConversion - TypicalVoltageAt25) / TemperatureSensitivity + ReferenceTemperature;
        LOG_DEBUG << "The temperature of the MCU is: " << MCUtemperature << " degrees Celsius";
        CommonParameters::mcuTemperature.setValue(MCUtemperature);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        #endif

    }
}