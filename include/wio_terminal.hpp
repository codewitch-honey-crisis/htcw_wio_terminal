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

using button_up_t = arduino::int_button<WIO_5S_UP,10,true>;
using button_down_t = arduino::int_button<WIO_5S_DOWN,10,true>;
using button_left_t = arduino::int_button<WIO_5S_LEFT,10,true>;
using button_right_t = arduino::int_button<WIO_5S_RIGHT,10,true>;
using button_press_t = arduino::int_button<WIO_5S_PRESS,10,true>;

extern button_up_t button_up_raw;
extern button_down_t button_down_raw;
extern button_left_t button_left_raw;
extern button_right_t button_right_raw;
extern button_press_t button_press_raw;

extern arduino::multi_button button_up;
extern arduino::multi_button button_down;
extern arduino::multi_button button_left;
extern arduino::multi_button button_right;
extern arduino::multi_button button_press;

using namespace gfx;

extern void wio_initialize();
extern void wio_update();
