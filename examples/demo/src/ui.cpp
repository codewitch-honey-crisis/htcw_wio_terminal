#include <ui.hpp>
// downloaded from fontsquirrel.com and header generated with 
// https://honeythecodewitch.com/gfx/generator
#define TELEGRAMA_IMPLEMENTATION
#include <fonts/Telegrama.hpp>

using namespace gfx;
using namespace uix;


// set up our LCD transfer buffer for UIX
constexpr const size_t lcd_buffer_size = 32*1024;
static uint8_t lcd_buffer[lcd_buffer_size];

// for the controls, which use RGBA8888
using color32_t = color<rgba_pixel<32>>;

// it helps to declare a transparent color for our controls
// this has the alpha channel set to 0 (transparent - RGBA8888)
constexpr const gfx::rgba_pixel<32> transparent(0,0,0,0);

screen_t main_screen({320,240},lcd_buffer_size,lcd_buffer);
label_t title_label(main_screen);
canvas_t buttons_canvas(main_screen);

static void buttons_canvas_on_paint(canvas_t::control_surface_type& destination, const srect16& clip, void* state) {
    draw::filled_rectangle(destination,((srect16)destination.bounds()).crop(clip),color_t::black);
        // we use this to rotate points
    viewport<typename canvas_t::control_surface_type> vp(destination);
    vp.center({9,9});
    vp.rotation(0);
    vp.offset({0,0});
    // define a triangle
    spoint16 up_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    // create the path from the points
    spath16 up_path(sizeof(up_points)/sizeof(spoint16),up_points);
    // rotate 90 degrees clockwise and repeat
    vp.rotation(90);
    spoint16 right_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 right_path(sizeof(right_points)/sizeof(spoint16),right_points);
    // now 180
    vp.rotation(180);
    spoint16 down_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 down_path(sizeof(down_points)/sizeof(spoint16),down_points);
    // finally 270
    vp.rotation(270);
    spoint16 left_points[] = {
        vp.translate({4,0}),
        vp.translate({9,9}),
        vp.translate({0,9})
    };
    spath16 left_path(sizeof(left_points)/sizeof(spoint16),left_points);
    
    // for the middle between the triangles
    srect16 middle_rect(0,9,8,17);
    
    // for the buttons displayed below the 5way switch
    srect16 button_rect(0,0,17,7);

    // our origin
    spoint16 org = up_path.bounds().center_horizontal(srect16(spoint16::zero(),(ssize16)destination.dimensions())).top_left();
    /// draw the 5way switch
    // offset the path so it appears in the right place
    up_path.offset_inplace(org);
    // draw it
    draw::filled_polygon(destination,up_path,button_up.pressed()?color_t::blue:color_t::white);
    // repeat for the other triangles
    right_path.offset_inplace(org.offset(0,9));
    draw::filled_polygon(destination,right_path,button_right.pressed()?color_t::blue:color_t::white);
    down_path.offset_inplace(org.offset(-9,9));
    draw::filled_polygon(destination,down_path,button_down.pressed()?color_t::blue:color_t::white);
    left_path.offset_inplace(org.offset(-9,0));
    draw::filled_polygon(destination,left_path,button_left.pressed()?color_t::blue:color_t::white);
    // draw the middle
    middle_rect.offset_inplace(org);
    draw::filled_rectangle(destination,middle_rect,button_press.pressed()?color_t::blue:color_t::white);
    // draw the buttons
    button_rect.offset_inplace((destination.dimensions().width-((button_rect.width()+4)*3))/2,org.y+50);
    draw::filled_rounded_rectangle(destination,button_rect,.5,button_c.pressed()?color_t::blue:color_t::white);
    button_rect.offset_inplace(button_rect.width()+4,0);
    draw::filled_rounded_rectangle(destination,button_rect,.5,button_b.pressed()?color_t::blue:color_t::white);
    button_rect.offset_inplace(button_rect.width()+4,0);
    draw::filled_rounded_rectangle(destination,button_rect,.5,button_a.pressed()?color_t::blue:color_t::white);
}
static void buttons_on_pressed_changed(bool pressed, void* state) {
    buttons_canvas.invalidate();
}
static void main_screen_on_flush_callback(const rect16& bounds,const void* bmp,void* state) {
    // create a draw destination over the source (fast)
    const_bitmap<typename screen_t::pixel_type,typename::screen_t::palette_type> source(bounds.dimensions(),bmp,main_screen.palette());
    // draw the bitmap
    draw::bitmap(lcd,bounds,source,source.bounds());
    // let the main screen know we're done (DMA not supported with this driver)
    main_screen.flush_complete();
}
void main_screen_initialize() {

    // set the button callbacks
    // on_press_changed is lower level and immediate. we use this
    // to update the display.
    button_a.on_pressed_changed(buttons_on_pressed_changed);
    button_b.on_pressed_changed(buttons_on_pressed_changed);
    button_c.on_pressed_changed(buttons_on_pressed_changed);
    button_up.on_pressed_changed(buttons_on_pressed_changed);
    button_down.on_pressed_changed(buttons_on_pressed_changed);
    button_left.on_pressed_changed(buttons_on_pressed_changed);
    button_right.on_pressed_changed(buttons_on_pressed_changed);
    button_press.on_pressed_changed(buttons_on_pressed_changed);
    // set the flush callback for the main screen
    main_screen.on_flush_callback(main_screen_on_flush_callback);
    constexpr const size_t line_height = 35;
    main_screen.background_color(color_t::black);
    // for performance we don't want to update the controls at the 
    // same time as the screen. This little trick fixes that
    main_screen.update();
    main_screen.validate_all();
    srect16 b(main_screen.bounds().x1,0,main_screen.bounds().x2,line_height+2);
    b.center_vertical_inplace((srect16)main_screen.bounds());
    b.offset_inplace(0,-40);
    title_label.bounds(b);
    title_label.background_color(transparent);
    title_label.border_color(transparent);
    title_label.text_color(color32_t::white);
    // set the font to a truetype/opentype font
    title_label.text_open_font(&Telegrama);
    title_label.padding({0,0});
    title_label.text_justify(uix_justify::top_middle);
    title_label.text_line_height(line_height);
    title_label.text("Wio Terminal");
    main_screen.register_control(title_label);
    b=srect16(0,title_label.bounds().y2+5,99,main_screen.bounds().y2);
    b.center_horizontal_inplace(main_screen.bounds());
    buttons_canvas.bounds(b);
    buttons_canvas.on_paint_callback(buttons_canvas_on_paint,nullptr);
    main_screen.register_control(buttons_canvas);   
}