#include <Arduino.h>
#include <wio_terminal.hpp>
// downloaded from fontsquirrel.com and header generated with 
// https://honeythecodewitch.com/gfx/generator
#define TELEGRAMA_IMPLEMENTATION
#include <fonts/Telegrama.hpp>
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
    // reset the dimmer
    Serial.println("Press");
}
void setup() {
    Serial.begin(115200);
    wio_initialize();
    // set the button callbacks
    button_up.on_click(button_up_on_click);
    button_down.on_click(button_down_on_click);
    button_left.on_click(button_left_on_click);
    button_right.on_click(button_right_on_click);
    button_press.on_click(button_press_on_click);
    
    draw::filled_rectangle(lcd,lcd.bounds(),color_t::purple);
    open_text_info oti;
    oti.font = &Telegrama;
    oti.text = "Wio Terminal";
    oti.scale = oti.font->scale(35);
    oti.transparent_background = false;
    srect16 txtr = oti.font->measure_text(ssize16::max(),spoint16::zero(),oti.text,oti.scale).bounds();
    txtr.center_inplace((srect16)lcd.bounds());
    draw::text(lcd,txtr,oti,color_t::white,color_t::purple);
}

void loop() {
    wio_update();
}