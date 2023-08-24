#include <wio_terminal.hpp>

using button_a_t = arduino::basic_button;//<WIO_KEY_A,10,true>;
using button_b_t = arduino::basic_button;//<WIO_KEY_B,10,true>;
using button_c_t = arduino::basic_button;//<WIO_KEY_C,10,true>;

using button_up_t = arduino::int_button<WIO_5S_UP,10,true>;
using button_down_t = arduino::int_button<WIO_5S_DOWN,10,true>;
using button_left_t = arduino::int_button<WIO_5S_LEFT,10,true>;
using button_right_t = arduino::int_button<WIO_5S_RIGHT,10,true>;
using button_press_t = arduino::int_button<WIO_5S_PRESS,10,true>;

lcd_t lcd;

button_a_t button_a_raw(WIO_KEY_A,10,true);
button_b_t button_b_raw(WIO_KEY_B,10,true);
button_c_t button_c_raw(WIO_KEY_C,10,true);

button_up_t button_up_raw;
button_down_t button_down_raw;
button_left_t button_left_raw;
button_right_t button_right_raw;
button_press_t button_press_raw;

arduino::multi_button button_a(button_a_raw);
arduino::multi_button button_b(button_b_raw);
arduino::multi_button button_c(button_c_raw);

arduino::multi_button button_up(button_up_raw);
arduino::multi_button button_down(button_down_raw);
arduino::multi_button button_left(button_left_raw);
arduino::multi_button button_right(button_right_raw);
arduino::multi_button button_press(button_press_raw);

void wio_initialize() {
    lcd.initialize();
    button_a.initialize();
    button_b.initialize();
    button_c.initialize();
    button_up.initialize();
    button_down.initialize();
    button_left.initialize();
    button_right.initialize();
    button_press.initialize();
}
void wio_update() {
    button_a.update();
    button_b.update();
    button_c.update();
    button_up.update();
    button_down.update();
    button_left.update();
    button_right.update();
    button_press.update();
}
