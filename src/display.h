// LovyanGFX setup for the TENSTAR ESP32-S3-Zer0 + 2.8" SPI TFT:
// Pins from LILYGO's pin_config.h.
#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#define PIN_POWER_ON -1
#define PIN_BL       -1
#define PIN_BTN_A    -1
#define PIN_BTN_B    -1
#define PIN_BAT      -1

// Give easy name to GPIO numbers from Animation Schematic. 
#define TFT_CS 1  //Screen CS -> ESP#2 GPIO 1
#define TFT_DC 2 //Screen DC -> ESP#2 GPIO 2
#define TFT_MOSI 3 //Screen MOSI -> ESP#2 GPIO 3
#define TFT_SCLK 4 //Screen SCK -> ESP32 GPIO 4
#define TFT_RST 5 //Screen RST -> ESP32 GPIO 5


//Custom screen profile named LGFX, main.cpp uses the draw
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel;
  lgfx::Bus_SPI       _bus; // Dont need to put anything here since bus_spi is customized to math kicad schematic
  // lgfx::Light_PWM _light; // dont need this since I wired pin 8 to power through the switch, meaning it goes to fll brightness

 public:
  LGFX() {
    { //SPI Bus Configuration
      auto cfg = _bus.config();

      cfg.spi_host = SPI2_HOST;

      cfg.spi_mode = 0;                  
      cfg.freq_write = 40000000;        
      cfg.freq_read = 16000000;         
      cfg.spi_3wire = false; //separate MOSI and DC wires and not one wire          
      cfg.use_lock = true;          
      cfg.dma_channel = SPI_DMA_CH_AUTO;  

      cfg.pin_sclk = TFT_SCLK; 
      cfg.pin_mosi = TFT_MOSI;
      cfg.pin_miso = -1; 
      cfg.pin_dc = TFT_DC;  

      _bus.config(cfg);
      _panel.setBus(&_bus);
    }

    { // Display Panel COnfiguration (240x320)
      auto cfg = _panel.config();
      cfg.pin_cs = TFT_CS; // Screen CS ESP32 Pin 14 (GPIO 1)
      cfg.pin_rst = TFT_RST; // Screen RST ESP32 GPIO 5
      cfg.pin_busy = -1; // turned off
      cfg.panel_width = 240; //240 from the screen I chose, 240x320
      cfg.panel_height = 320;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.dummy_read_pixel = 8
      cfg.dummy_read_bits = 1
      cfg.readable = false
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = false;

      _panel.config(cfg);
    }

    setPanel(&_panel_instance);
  }
