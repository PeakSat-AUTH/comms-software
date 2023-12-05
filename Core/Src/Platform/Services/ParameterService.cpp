#include "ECSS_Configuration.hpp"
#include "PeakSatParameters.hpp"
#include "Services/ParameterService.hpp"

#ifdef SERVICE_PARAMETER

void ParameterService::initializeParameterMap() {
    parameters = {{PeakSatParameters::ReportParametersUnusedStack,     PeakSatParameters::reportParametersUnusedStack},
                  {PeakSatParameters::AvailableHeap,                   PeakSatParameters::availableHeap},

                  {PeakSatParameters::AntennaDeploymentStatus,         PeakSatParameters::antennaDeploymentStatus},
                  {PeakSatParameters::SampleRateUHFTX,                 PeakSatParameters::sampleRateUHFTX},
                  {PeakSatParameters::SymbolRateSBandTX,               PeakSatParameters::symbolRateSBandTX},
                  {PeakSatParameters::SampleRateSBandTX,               PeakSatParameters::sampleRateSBandTX},
                  {PeakSatParameters::SymbolRateUHFTX,                 PeakSatParameters::symbolRateUHFBandTX},
                  {PeakSatParameters::CWInterval,                      PeakSatParameters::cwInterval},

                  {PeakSatParameters::GMSKBeaconInterval,              PeakSatParameters::gmskBeaconInterval},
                  {PeakSatParameters::ChannelNumberUHF,                PeakSatParameters::channelNumberUHF},
                  {PeakSatParameters::ChannelNumberSBand,              PeakSatParameters::channelNumberSBand},
                  {PeakSatParameters::PowerAmplifierUHF,               PeakSatParameters::powerAmplifierUHF},
                  {PeakSatParameters::PowerAmplifierS,                 PeakSatParameters::powerAmplifierS},
                  {PeakSatParameters::VariableGainAmplifier,           PeakSatParameters::variableGainAmplifier},
                  {PeakSatParameters::ReceivedSignalStrengthIndicator, PeakSatParameters::receivedSignalStrengthIndicator},
                  {PeakSatParameters::UHFBandTX,                       PeakSatParameters::uhfBandTX},

                  {PeakSatParameters::SBandTX,                         PeakSatParameters::sBandTX},
                  {PeakSatParameters::NumberOfPackagesRejected,        PeakSatParameters::numberOfPackagesRejected},
                  {PeakSatParameters::InvalidHMAC,                     PeakSatParameters::invalidHMAC},

                  {PeakSatParameters::InvalidPacketStructure,          PeakSatParameters::invalidPacketStructure},
                  {PeakSatParameters::InvalidSpacecraftID,             PeakSatParameters::invalidSpacecraftID},
                  {PeakSatParameters::TCFrameSequenceCounter,          PeakSatParameters::tcFrameSequenceCounter},
                  {PeakSatParameters::COMMSPCBTemperature1,            PeakSatParameters::commsPCBTemperature1},
                  {PeakSatParameters::COMMSPCBTemperature2,            PeakSatParameters::commsPCBTemperature2},
                  {PeakSatParameters::COMMSMCUTemperature,             PeakSatParameters::commsMCUTemperature},
                  {PeakSatParameters::COMMSMCUInputVoltage,            PeakSatParameters::commsMCUInputVoltage},
                  {PeakSatParameters::COMMSMCUBootCounter,             PeakSatParameters::commsMCUBootCounter},

                  {PeakSatParameters::OnBoardTime,                     PeakSatParameters::onBoardTime},
                  {PeakSatParameters::NANDUsedMemoryPartition,         PeakSatParameters::nandUsedMemoryPartition},
                  {PeakSatParameters::LastFailedEvent,                 PeakSatParameters::lastFailedEvent},
                  {PeakSatParameters::COMMSMCUSystick,                 PeakSatParameters::commsMCUSystick},
                  {PeakSatParameters::COMMSFLASHInt,                   PeakSatParameters::commsFlashInt},
                  {PeakSatParameters::COMMSSRAMInt,                    PeakSatParameters::commsSRAMInt},
    };
}
#endif
