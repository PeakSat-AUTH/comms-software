#include "UARTGatekeeperTask.hpp"

UARTGatekeeperTask::UARTGatekeeperTask() : Task("UARTGatekeeperTask") {
    xUartQueue = xQueueCreateStatic(UARTQueueSize, sizeof(etl::string<LOGGER_MAX_MESSAGE_SIZE>), ucQueueStorageArea, &xStaticQueue);
}

void UARTGatekeeperTask::execute() {
    etl::string<LOGGER_MAX_MESSAGE_SIZE> output;
    while (true) {
        xQueueReceive(xUartQueue, &output, portMAX_DELAY);
        #ifndef STM32
        const void *txRegisterAddress = const_cast<void *>(reinterpret_cast<volatile void *>(&USART1_REGS->US_THR));
        XDMAC_ChannelTransfer(XDMAC_CHANNEL_0, output.data(), txRegisterAddress, output.size());
        #else
        extern UART_HandleTypeDef huart3;
        HAL_UART_Transmit(&huart3, reinterpret_cast<const uint8_t *>(output.data()), output.size(), 100);
        #endif
    }
}
