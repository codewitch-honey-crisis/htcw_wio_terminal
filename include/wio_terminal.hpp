#pragma once
#include <Arduino.h>
#include <tft_io.hpp>
#include <ili9341.hpp>
#include <button.hpp>
#include <gfx.hpp>

using namespace arduino;

using bus_t = tft_spi_ex<3,LCD_SS_PIN,SPI_MODE0>;
using lcd_t = ili9341<LCD_DC,LCD_RESET,LCD_BACKLIGHT,bus_t,3,true,400,200>;
using color_t = gfx::color<typename lcd_t::pixel_type>;

extern lcd_t lcd;

extern multi_button button_a;
extern multi_button button_b;
extern multi_button button_c;

extern multi_button button_up;
extern multi_button button_down;
extern multi_button button_left;
extern multi_button button_right;
extern multi_button button_press;

using namespace gfx;

extern void wio_initialize();
extern void wio_update();
