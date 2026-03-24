# Project: Pumps-lsd-controller

## Project Overview
An ESP32S3-based automated pump control system with a 7-inch LCD display (800x480). It features a graphical user interface (GUI) built with **LVGL 9.x**, utilizing the **Arduino_GFX** library and **TAMC_GT911** for touch input. The system manages multiple pump zones with timing logic and supports remote control via **ESP-NOW**.

### Architecture
- **Framework:** Arduino (Espressif32)
- **UI:** LVGL (v9.5) with EEZ Studio integration (`src/ui/`)
- **Communication:** ESP-NOW for relay control and remote pult interaction
- **Logic:** `src/auto_pumps.cpp` handles the scheduling and state of pumps
- **OS:** FreeRTOS (integrated into ESP32 Arduino) for task management

## Building and Running
The project uses **PlatformIO**.

### Key Commands
- **Build:** `pio run`
- **Upload:** `pio run --target upload`
- **Monitor:** `pio device monitor`
- **Clean:** `pio run --target clean`

### Dependencies (managed via platformio.ini)
- `lvgl/lvgl@^9.5`
- `tamctec/TAMC_GT911@^1.0.2`
- `moononournation/GFX Library for Arduino@^1.6.5`
- `ayushsharma82/ElegantOTA@^3.1.7`

## Development Conventions

### Hardware Interface
- **Pumps/Relays:** Controlled via ESP-NOW to remote relay modules.
- **Display:** ESP32S3 RGB Panel (DE, VSYNC, HSYNC, PCLK, and 16-bit RGB pins).
- **Touch:** I2C-based GT911.

### UI Logic
- LVGL objects and screens are defined in `src/ui/`.
- UI interactions (button clicks, value changes) are handled in `src/actions.cpp`.
- `loop_display()` in `src/display.cpp` manages the LVGL task handler and backlight dimming.

### Pump Control Logic
- `periodTick()` and `flowTick()` in `src/auto_pumps.cpp` are the core loops for pump timing.
- Supports both "dirty water" (`dw_time`) and "clear water" (`cw_time`) phases for each zone.
- `minutes` factor (1 or 60) used for debug vs. real-time operation.

### Safety & Error Handling
- `system_error_state` flag stops pump logic if ESP-NOW communication fails.
- Backlight is automatically dimmed after inactivity to save power/screen life.

### Code Quality
- Prefer `constexpr` for constants (see `include/constants.h`).
- Use `Preferences` library for persistent settings (`src/settings.cpp`).
- UI-related strings are often Russian (Cyrillic), ensure proper UTF-8 handling..


- Use 4 spaces for indentation.