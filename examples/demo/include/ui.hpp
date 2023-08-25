#pragma once
#include <wio_terminal.hpp>
#include <gfx.hpp>
#include <uix.hpp>

// X11 color enumeration in RGB565 format (same as the LCD)
// now you can retrieve a color using ex: color_t::white
using color_t = gfx::color<typename lcd_t::pixel_type>;

// define a screen type using the native resolution and pixel type
using screen_t = uix::screen<320,240,typename lcd_t::pixel_type>;

// define a label control type for our screen_t
using label_t = uix::label<typename screen_t::control_surface_type>;

// define a canvas control type for our screen_t
using canvas_t = uix::canvas<typename screen_t::control_surface_type>;

// our screen
extern screen_t main_screen;
// our label - we'll draw the title text with it
extern label_t title_label;
// our canvas. we'll draw the buttons on it
extern canvas_t buttons_canvas;

// to set up all the controls on the main_screen
extern void main_screen_initialize();
