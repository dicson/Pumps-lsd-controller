#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int WATER_RELAY{14}; // это реле, ведущее на чистую/ воду
constexpr int PUMP_RELAY{15};  // это реле, ведущее на насос
constexpr int PUMP_AMOUNT{14}; // количество зон
constexpr int SWITCH_LEVEL{0}; // реле: 1 - высокого уровня (или мосфет), 0 - низкого

constexpr int DEFAULT_GFX_BL_VALUE{80};
constexpr int DEFAULT_GFX_BL_TIME{30};
constexpr int DEFAULT_ZONE_PAUSE{0};
constexpr int DEFAULT_K_DW_TIME{100};
constexpr int DEFAULT_MINUTES{60};

constexpr int EXT_CLICK_AREA_SMALL{10};
constexpr int EXT_CLICK_AREA_LARGE{20};
constexpr int FULL_OPACITY{255};
constexpr int LOW_OPACITY{100};

constexpr const char * VERSION = "Текущая версия прошивки - 1.0";
#endif