#include <Arduino.h>
#include <wio_terminal.hpp>
// downloaded from fontsquirrel.com and header generated with 
// https://honeythecodewitch.com/gfx/generator
#define TELEGRAMA_IMPLEMENTATION
#include <fonts/Telegrama.hpp>

static void draw_buttons() {
    viewport<lcd_t> vp(lcd);
    vp.center({9,9});
    vp.rotation(0);
    vp.offset({0,0});
    spoint16 up_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 up_path(sizeof(up_points)/sizeof(spoint16),up_points);
    vp.rotation(90);
    spoint16 right_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 right_path(sizeof(right_points)/sizeof(spoint16),right_points);
    vp.rotation(180);
    spoint16 down_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 down_path(sizeof(down_points)/sizeof(spoint16),down_points);
    vp.rotation(270);
    spoint16 left_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 left_path(sizeof(left_points)/sizeof(spoint16),left_points);
    
    srect16 middle_rect(0,9,8,17);

    srect16 button_rect(0,0,17,7);

    spoint16 org = up_path.bounds().center((srect16)lcd.bounds()).offset(0,10).top_left();
    up_path.offset_inplace(org);
    draw::filled_polygon(lcd,up_path,button_up.pressed()?color_t::blue:color_t::white);
    right_path.offset_inplace(org.offset(0,9));
    draw::filled_polygon(lcd,right_path,button_right.pressed()?color_t::blue:color_t::white);
    down_path.offset_inplace(org.offset(-9,9));
    draw::filled_polygon(lcd,down_path,button_down.pressed()?color_t::blue:color_t::white);
    left_path.offset_inplace(org.offset(-9,0));
    draw::filled_polygon(lcd,left_path,button_left.pressed()?color_t::blue:color_t::white);
    middle_rect.offset_inplace(org);
    draw::filled_rectangle(lcd,middle_rect,button_press.pressed()?color_t::blue:color_t::white);
    button_rect.offset_inplace((lcd.dimensions().width-((button_rect.width()+4)*3))/2,org.y+50);
    draw::filled_rounded_rectangle(lcd,button_rect,.5,button_c.pressed()?color_t::blue:color_t::white);
    button_rect.offset_inplace(button_rect.width()+4,0);
    draw::filled_rounded_rectangle(lcd,button_rect,.5,button_b.pressed()?color_t::blue:color_t::white);
    button_rect.offset_inplace(button_rect.width()+4,0);
    draw::filled_rounded_rectangle(lcd,button_rect,.5,button_a.pressed()?color_t::blue:color_t::white);
}
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
    
    // set the button callbacks
    button_a.on_click(button_a_on_click);
    button_b.on_click(button_b_on_click);
    button_c.on_click(button_c_on_click);
    button_up.on_click(button_up_on_click);
    button_down.on_click(button_down_on_click);
    button_left.on_click(button_left_on_click);
    button_right.on_click(button_right_on_click);
    button_press.on_click(button_press_on_click);
    
    draw::filled_rectangle(lcd,lcd.bounds(),color_t::black);
    open_text_info oti;
    oti.font = &Telegrama;
    oti.text = "Wio Terminal";
    oti.scale = oti.font->scale(35);
    oti.transparent_background = false;
    srect16 txtr = oti.font->measure_text(ssize16::max(),spoint16::zero(),oti.text,oti.scale).bounds();
    txtr.center_inplace((srect16)lcd.bounds());
    txtr.offset_inplace(0,-25);
    auto bmp = create_bitmap_from(lcd,(size16)txtr.dimensions());
    if(bmp.begin()) {
        draw::text(bmp,bmp.bounds(),oti,color_t::white);
        draw::bitmap(lcd,txtr,bmp,bmp.bounds());
        free(bmp.begin());
    }
}

void loop() {
    wio_update();
    static uint32_t update_ts = 0;
    if(millis()>update_ts+250) {
        update_ts = millis();
        draw_buttons();
    }
}