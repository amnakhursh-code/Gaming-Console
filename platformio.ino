; Custom text display for the TENSTAR ESP32-S3-Zero + 2.8" SPI TFT (ILI9341)
; Build:  pio run          Upload:  pio run -t upload          Logs:  pio device monitor

[env:esp32-s3-zero]
platform = espressif32@6.9.0
board = esp32-s3-devkitc-1
framework = arduino
board_build.partitions = default.csv
board_build.arduino.memory_type = qio_qspi
build_flags =
  -DARDUINO_USB_CDC_ON_BOOT=1
  -DARDUINO_USB_MODE=1
  -DBOARD_HAS_PSRAM
lib_deps =
  lovyan03/LovyanGFX@1.1.16
  bblanchon/ArduinoJson@7.2.1
monitor_speed = 115200
upload_speed = 115200
extra_scripts = pre:tools/make_web.py
