#include "Helpers/TimeGetter.hpp"
#include "../../../../../../../nucleo-h743-software/Core/Inc/Platform/Parameters/CommonParameters.hpp"
#include "../../../../../../../nucleo-h743-software/Core/Inc/Platform/Parameters/Parameters.hpp"

UTCTimestamp TimeGetter::getCurrentTimeUTC() {
    return getCurrentTimeDefaultCUC().toUTCtimestamp();
}

Time::DefaultCUC TimeGetter::getCurrentTimeDefaultCUC() {
    return CommonParameters::time.getValue();
}
