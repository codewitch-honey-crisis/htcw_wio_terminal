#include <wio_terminal.hpp>

lcd_t lcd;

button_up_t button_up_raw;
button_down_t button_down_raw;
button_left_t button_left_raw;
button_right_t button_right_raw;
button_press_t button_press_raw;

arduino::multi_button button_up(button_up_raw);
arduino::multi_button button_down(button_down_raw);
arduino::multi_button button_left(button_left_raw);
arduino::multi_button button_right(button_right_raw);
arduino::multi_button button_press(button_press_raw);

void wio_initialize() {
    lcd.initialize();
    button_up.initialize();
    button_down.initialize();
    button_left.initialize();
    button_right.initialize();
    button_press.initialize();
}
void wio_update() {
    button_up.update();
    button_down.update();
    button_left.update();
    button_right.update();
    button_press.update();
}
