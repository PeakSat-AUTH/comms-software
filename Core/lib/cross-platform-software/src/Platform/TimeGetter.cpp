#include "Helpers/TimeGetter.hpp"
#include "CommonParameters.hpp"
#include "Parameters.hpp"

UTCTimestamp TimeGetter::getCurrentTimeUTC() {
    return getCurrentTimeDefaultCUC().toUTCtimestamp();
}

Time::DefaultCUC TimeGetter::getCurrentTimeDefaultCUC() {
    return CommonParameters::time.getValue();
}
