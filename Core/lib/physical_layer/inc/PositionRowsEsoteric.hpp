#pragma once

#include <stdint.h>

static constexpr uint8_t generatorRowsEsoteric = 32;

static constexpr uint8_t generatorColumnsEsoteric = 8;

static constexpr uint16_t totalQuasiCyclicMatricesEsoteric = generatorColumnsEsoteric * generatorRowsEsoteric;

inline static const uint16_t positionRowsEsoteric[totalQuasiCyclicMatricesEsoteric] = {
    0,     63,    128,   194,   266,   336,   388,   444,   508,   572,   639,   708,   764,
    822,   884,   948,   1006,  1072,  1140,  1199,  1274,  1340,  1402,  1464,  1530,  1593,
    1653,  1721,  1786,  1856,  1916,  1974,  2032,  2102,  2170,  2233,  2298,  2361,  2429,
    2489,  2550,  2613,  2675,  2745,  2810,  2869,  2938,  3004,  3076,  3137,  3206,  3258,
    3324,  3382,  3453,  3518,  3574,  3640,  3703,  3768,  3832,  3900,  3960,  4027,  4084,
    4147,  4218,  4276,  4342,  4404,  4472,  4538,  4606,  4670,  4735,  4806,  4876,  4942,
    4988,  5048,  5116,  5180,  5250,  5301,  5372,  5432,  5488,  5554,  5618,  5671,  5731,
    5799,  5866,  5932,  5992,  6058,  6114,  6176,  6239,  6306,  6360,  6428,  6501,  6555,
    6620,  6684,  6746,  6817,  6884,  6945,  7005,  7074,  7138,  7209,  7287,  7349,  7402,
    7456,  7503,  7567,  7622,  7687,  7746,  7818,  7880,  7943,  7999,  8056,  8118,  8187,
    8256,  8322,  8394,  8466,  8532,  8598,  8664,  8714,  8773,  8836,  8904,  8970,  9044,
    9100,  9162,  9228,  9298,  9359,  9428,  9494,  9558,  9616,  9676,  9739,  9807,  9873,
    9948,  10014, 10080, 10138, 10202, 10257, 10319, 10387, 10452, 10514, 10572, 10638, 10696,
    10751, 10812, 10878, 10944, 11006, 11072, 11128, 11194, 11258, 11315, 11382, 11442, 11502,
    11566, 11626, 11694, 11756, 11812, 11883, 11936, 11992, 12056, 12126, 12198, 12270, 12334,
    12405, 12466, 12536, 12593, 12668, 12740, 12797, 12853, 12913, 12972, 13038, 13094, 13163,
    13226, 13281, 13346, 13416, 13472, 13541, 13611, 13685, 13756, 13814, 13885, 13950, 14016,
    14079, 14144, 14208, 14262, 14332, 14396, 14462, 14526, 14598, 14657, 14716, 14783, 14847,
    14917, 14981, 15057, 15120, 15172, 15239, 15306, 15362, 15426, 15494, 15566, 15633, 15700,
    15760, 15821, 15897, 15957, 16021, 16087, 16154, 16229, 16298};
