#include "TransceiverTask.hpp"

using namespace AT86RF215;

AT86RF215::At86rf215 TransceiverTask::transceiver = AT86RF215::At86rf215(&hspi4, AT86RF215::AT86RF215Configuration());

uint8_t TransceiverTask::checkTheSPI() {
    uint8_t spi_error = 0;
    DevicePartNumber dpn = transceiver.get_part_number(error);
    if(dpn == DevicePartNumber::AT86RF215)
        LOG_DEBUG << "SPI OK" ;
    else{
        spi_error = 1;
        LOG_DEBUG << "SPI ERROR" ;
        transceiver.chip_reset(error);
    }
    return spi_error;
}

TransceiverTask::PacketType TransceiverTask::createRandomPacket(uint16_t length) {
    PacketType packet;
    for (std::size_t i = 0; i < length; i++) {
        packet[i] = i;
    }
    return packet;
}

void TransceiverTask::setConfiguration(uint16_t pllFrequency09, uint8_t pllChannelNumber09) {
    CustomConfig.pllFrequency09 = pllFrequency09;
    CustomConfig.pllChannelNumber09 = pllChannelNumber09;
    CustomConfig.pllChannelMode09 = AT86RF215::PLLChannelMode::FineResolution450;
    CustomConfig.powerAmplifierRampTime09 = AT86RF215::PowerAmplifierRampTime::RF_PARAMP32U;
    CustomConfig.transmitterCutOffFrequency09 = AT86RF215::TransmitterCutOffFrequency::RF_FLC100KHZ;
    CustomConfig.transceiverSampleRate09 = AT86RF215::TransmitterSampleRate::FS_400;
    CustomConfig.continuousTransmit09 = false;
    CustomConfig.baseBandEnable09 = true;
    CustomConfig.physicalLayerType09 = PhysicalLayerType::BB_MRFSK;
    CustomConfig. frameCheckSequenceType09 = FrameCheckSequenceType::FCS_16;
    transceiver.config = CustomConfig;
}

void TransceiverTask::receiverConfig(bool agc_enable){
    transceiver.setup_rx_frontend(AT86RF215::RF09,
                                  false,
                                  false,
                                  AT86RF215::ReceiverBandwidth::RF_BW200KHZ_IF250KHZ,
                                  AT86RF215::RxRelativeCutoffFrequency::FCUT_0375,
                                  AT86RF215::ReceiverSampleRate::FS_400,
                                  false,
                                  AT86RF215::AverageTimeNumberSamples::AVGS_8,
                                  false,
                                  AT86RF215::AutomaticGainTarget::DB30,
                                  23,
                                  error);
    // ENABLE AGC
    RegisterAddress regagcc = AT86RF215::RF09_AGCC;
    uint8_t reg = transceiver.spi_read_8(regagcc, error);
    reg = reg | (static_cast<uint8_t>(agc_enable));
    transceiver.spi_write_8(regagcc, reg, error);

    transceiver.setup_rssi(AT86RF215::RF09,
                           AT86RF215::EnergyDetectionMode::RF_EDAUTO,
                           16, // default value
                           AT86RF215::EnergyDetectionTimeBasis::RF_8MS,
                           error);
}

/*
* The frequency cannot be lower than 377000 as specified in section 6.3.2. The frequency range related
* to Fine Resolution Channel Scheme CNM.CM=1 is from 389.5MHz to 510MHz
*/
uint16_t TransceiverTask::calculatePllChannelFrequency09(uint32_t frequency) {
    uint32_t N = (frequency - 377000) * 65536 / 6500;
    return N >> 8;
}

/*
* The frequency cannot be lower than 377000 as specified in section 6.3.2. The frequency range related
* to Fine Resolution Channel Scheme CNM.CM = 1 is from 389.5MHz to 510MHz
*/
uint8_t TransceiverTask::calculatePllChannelNumber09(uint32_t frequency) {
    uint32_t N = (frequency - 377000) * 65536 / 6500;
    return N & 0xFF;
}

void  TransceiverTask::directModConfigAndPreEmphasisFilter(bool enableDM, bool enablePE, bool recommended){
    if(enableDM){
        transceiver.set_direct_modulation(RF09, enableDM, error);
        uint8_t temp = (transceiver.spi_read_8(BBC0_FSKDM, error)) & 0b11111110;
        // enable direct modulation in the BaseBand core
        transceiver.spi_write_8(BBC0_FSKDM, temp | 0b00000001, error);

        if(enablePE){
            transceiver.spi_write_8(BBC0_FSKDM, temp | 0b00000011, error);
            if(recommended){
                transceiver.spi_write_8(BBC0_FSKPE0, 0x2, error);
                transceiver.spi_write_8(BBC0_FSKPE1, 0x3, error);
                transceiver.spi_write_8(BBC0_FSKPE2, 0xFC, error);
            }
        }
    }
}

void TransceiverTask::txSRandTxFilter() {
    AT86RF215::RegisterAddress  regtxdfe;
    regtxdfe = AT86RF215::RF09_TXDFE;

    uint8_t reg = transceiver.spi_read_8(regtxdfe,error);
    // RCUT CONFIG
    transceiver.spi_write_8(regtxdfe, reg | (static_cast<uint8_t>(0x01) << 5), error);
    // SR Config
    reg = transceiver.spi_read_8(regtxdfe,error);
    transceiver.spi_write_8(regtxdfe, reg | (static_cast<uint8_t>(0xA)), error);
}

void TransceiverTask::txAnalogFrontEnd() {
    AT86RF215::RegisterAddress regtxcutc;
    regtxcutc = AT86RF215::RF09_TXCUTC;

    uint8_t reg = transceiver.spi_read_8(regtxcutc, error);
    // PARAMP Config
    transceiver.spi_write_8(regtxcutc, reg | (static_cast<uint8_t>(AT86RF215::PowerAmplifierRampTime::RF_PARAMP32U) << 6), error);
    // LPFCUT Config
    transceiver.spi_write_8(regtxcutc, reg | (static_cast<uint8_t>(AT86RF215::TransmitterCutOffFrequency::RF_FLC80KHZ)), error);
}

void TransceiverTask::modulationConfig(){
    // BT = 1 , MIDXS = 1, MIDX = 1, MOR = B-FSK
    transceiver.spi_write_8(BBC0_FSKC0, 86, error);
    directModConfigAndPreEmphasisFilter(true,false, false);
}

void TransceiverTask::execute() {
    while (checkTheSPI() != 0);
    setConfiguration(calculatePllChannelFrequency09(FrequencyUHF), calculatePllChannelNumber09(FrequencyUHF));
    transceiver.chip_reset(error);
    transceiver.setup(error);
    txAnalogFrontEnd();
    txSRandTxFilter();
    modulationConfig();
    receiverConfig(true);

    uint16_t currentPacketLength = 64;
    PacketType packet = createRandomPacket(currentPacketLength);

    if(transceiverTask->txrx_bool){
        transceiver.set_state(AT86RF215::RF09, State::RF_TXPREP, error);
        vTaskDelay(pdMS_TO_TICKS(10));
        transceiver.set_state(AT86RF215::RF09, State::RF_RX, error);
        if (transceiver.get_state(AT86RF215::RF09, error) == (AT86RF215::State::RF_RX))
            LOG_DEBUG << " state = RX ";
    }
    else{
        transceiver.TransmitterFrameEnd_flag = true;
        transceiver.TransceiverReady_flag = true;
    }

    uint32_t timer = 0;
    bool timer_flag = false;
    uint8_t error_flag = 0;

    while(true) {
        timer++;
        if(timer == 1000000)
            timer_flag = true;

        if(transceiverTask->txrx_bool && transceiver.ReceiverFrameEnd_flag)
        {
            LOG_DEBUG << "receiver frame end";
            transceiver.ReceiverFrameEnd_flag = false;
            transceiver.set_state(AT86RF215::RF09, State::RF_TXPREP, error);
            //uint8_t length = (transceiver.spi_read_8(AT86RF215::BBC0_TXFLH, error) << 8) | static_cast<uint16_t>(transceiver.spi_read_8(AT86RF215::BBC0_TXFLH, error)) ;
            //LOG_DEBUG << "LENGTH = " << length ;
            vTaskDelay(pdMS_TO_TICKS(10));
            transceiver.set_state(AT86RF215::RF09, State::RF_RX, error);

        }
        else{
            if(transceiver.TransceiverReady_flag && transceiver.TransmitterFrameEnd_flag) {
                transceiver.transmitBasebandPacketsTx(AT86RF215::RF09, packet.data(), currentPacketLength, error);
                transceiver.TransmitterFrameEnd_flag = false;
                transceiver.TransceiverReady_flag = false;
                LOG_DEBUG << "SENT" ;
                timer_flag = false;
                timer = 0;
            }
        }
    }
}