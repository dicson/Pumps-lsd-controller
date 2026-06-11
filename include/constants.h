#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int WATER_RELAY{14}; // это реле, ведущее на чистую/ воду
constexpr int PUMP_RELAY{15};  // это реле, ведущее на насос
constexpr int PUMP_AMOUNT{30}; // количество зон
constexpr int SWITCH_LEVEL{0}; // реле: 1 - высокого уровня (или мосфет), 0 - низкого
constexpr int MINIMAL_CURRENT{2}; // минимальный ток

constexpr int DEFAULT_GFX_BL_VALUE{80};
constexpr int DEFAULT_GFX_BL_TIME{30};
constexpr int DEFAULT_ZONE_PAUSE{0};
constexpr int DEFAULT_K_DW_TIME{100};
constexpr int DEFAULT_MINUTES{60};
constexpr int EXT_CLICK_AREA_SMALL{10};
constexpr int EXT_CLICK_AREA_LARGE{20};
constexpr int FULL_OPACITY{255};
constexpr int LOW_OPACITY{100};

static constexpr uint32_t MS_PER_SECOND = 1000;
static constexpr uint16_t MIN_K_DW_TIME = 50;
static constexpr uint16_t MAX_K_DW_TIME = 200;
static constexpr uint16_t K_DW_STEP = 10;
static constexpr uint16_t MIN_GFX_BL_TIME = 10;
static constexpr uint16_t SCREEN_ANIM_DURATION_MS = 1000;

constexpr uint32_t ZONE_BAR_COLOR_DW = 0x0000CB; // тёмно-синий (грязная вода)
constexpr const char *VERSION = "Текущая версия прошивки - 2.0";
#endif