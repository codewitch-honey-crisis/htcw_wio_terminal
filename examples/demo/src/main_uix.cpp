#include <Arduino.h>
#include <wio_terminal.hpp>
#include <ui.hpp>

static void button_a_on_click(int clicks,void* state) {
    Serial.println("A");
}
static void button_b_on_click(int clicks,void* state) {
    Serial.println("B");
}
static void button_c_on_click(int clicks,void* state) {
    Serial.println("C");
}
static void button_up_on_click(int clicks,void* state) {
    Serial.println("Up");
}
static void button_down_on_click(int clicks,void* state) {
    Serial.println("Down");
}
static void button_left_on_click(int clicks,void* state) {
    Serial.println("Left");
}
static void button_right_on_click(int clicks,void* state) {
    Serial.println("Right");
}
static void button_press_on_click(int clicks,void* state) {
    Serial.println("Press");
}

void setup() {
    Serial.begin(115200);
    wio_initialize();
    button_a.on_click(button_a_on_click);
    button_b.on_click(button_b_on_click);
    button_c.on_click(button_c_on_click);
    button_up.on_click(button_up_on_click);
    button_down.on_click(button_down_on_click);
    button_left.on_click(button_left_on_click);
    button_right.on_click(button_right_on_click);
    button_press.on_click(button_press_on_click);
        
    main_screen_initialize();
}

void loop() {    
    // ensure the callbacks get called
    wio_update();
    main_screen.update();
}