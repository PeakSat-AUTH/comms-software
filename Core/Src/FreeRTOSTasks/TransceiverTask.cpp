#include "TransceiverTask.hpp"
using namespace AT86RF215;

AT86RF215::At86rf215 TransceiverTask::transceiver = AT86RF215::At86rf215(&hspi4, AT86RF215::AT86RF215Configuration());

uint8_t TransceiverTask::checkTheSPI() {
    uint8_t error_t = 0;
    DevicePartNumber dpn = transceiver.get_part_number(error);
    switch (dpn) {
        case DevicePartNumber::AT86RF215:
            LOG_DEBUG << "Part Number : AT86RF215" ;
            break;
        case DevicePartNumber::AT86RF215IQ:
            LOG_DEBUG << "Part Number : AT86RF215IQ" ;
            break;
        case DevicePartNumber::AT86RF215M:
            LOG_DEBUG << "Part Number : AT86RF215M" ;
            break;
        case DevicePartNumber::AT86RF215_INVALID:
            LOG_DEBUG << "Invalid";
            error_t = 1;
            break;
    }
    if(error != NO_ERRORS){
        error_t = 1;
        switch (error) {
            case FAILED_READING_FROM_REGISTER:
                LOG_DEBUG << "Failed reading from register" ;
                break;
            default:
                LOG_DEBUG << "some other error";
        }
    }
    if(error_t == 1)
        transceiver.chip_reset(error);
    return error_t;
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
    CustomConfig.transmitterCutOffFrequency09 = AT86RF215::TransmitterCutOffFrequency::RF_FLC80KHZ;
    CustomConfig.transceiverSampleRate09 = AT86RF215::TransmitterSampleRate::FS_400;
    transceiver.config = CustomConfig;
}

void TransceiverTask::receiverConfig(){
    transceiver.setup_rx_frontend(AT86RF215::RF09,
                                  false,
                                  false,
                                  AT86RF215::ReceiverBandwidth::RF_BW160KHZ_IF250KHZ,
                                  AT86RF215::RxRelativeCutoffFrequency::FCUT_0375,
                                  AT86RF215::ReceiverSampleRate::FS_400,
                                  true,
                                  AT86RF215::AverageTimeNumberSamples::AVGS_8,
                                  true,
                                  AT86RF215::AutomaticGainTarget::DB42,
                                  0,
                                  error);


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

void  TransceiverTask::directModConfigAndPreEmphasisFilter(bool enableDM, bool enablePE){
    if(enableDM){
        transceiver.set_direct_modulation(RF09, enableDM, error);
        uint8_t temp = (transceiver.spi_read_8(BBC0_FSKDM, error)) & 0b11111110;
        // enable direct modulation in the BaseBand core
        transceiver.spi_write_8(BBC0_FSKDM, temp | 0b00000001, error);
        if(enablePE){
            transceiver.spi_write_8(BBC0_FSKDM, temp | 0b00000011, error);
            // pre-emphasis filter settings //
            transceiver.spi_write_8(BBC0_FSKPE0, 0x2, error);
            transceiver.spi_write_8(BBC0_FSKPE1, 0x3, error);
            transceiver.spi_write_8(BBC0_FSKPE2, 0xFC, error);
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
    Error err;
    // BT = 1 , MIDXS = 1, MIDX = 1, MOR = B-FSK
    transceiver.spi_write_8(BBC0_FSKC0, 86, err);
    directModConfigAndPreEmphasisFilter(true,true);
}

void TransceiverTask::execute() {
    while(checkTheSPI() != 0);
    setConfiguration(calculatePllChannelFrequency09(FrequencyUHF), calculatePllChannelNumber09(FrequencyUHF));
    transceiver.chip_reset(error);
    transceiver.setup(error);
    uint16_t currentPacketLength = 16;
    PacketType packet = createRandomPacket(currentPacketLength);

    modulationConfig();
    uint8_t option = 1;
    transceiver.transmitBasebandPacketsRx(AT86RF215::RF09, error);
    while(true){

        if(option == 0)
        {
            transceiver.transmitBasebandPacketsTx(AT86RF215::RF09, packet.data(), currentPacketLength, error);
            LOG_DEBUG << "signal transmitted";
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        else{
            for(int i = 0 ; i < 2047; i++)
                if(transceiver.received_packet[i] != 0)
                    LOG_DEBUG <<transceiver.received_packet[i];
            //LOG_DEBUG << transceiver.get_receiver_energy_detection(AT86RF215::RF09, error);
            /*
            if(transceiver.get_rssi(AT86RF215::RF09, error) > min && < max )
            {
                // then read the packet
                if(my packet is mine)
                {
                    // read it and print the packet
                }
                else{
                    // print wrong packet
                }
            }
            else{
                // clear the received packet variable and store this packet to another variable for post processing
            }
            */


        }

    }
}
