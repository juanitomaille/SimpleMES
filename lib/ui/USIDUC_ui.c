#include "USIDUC_ui.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * HomeScreen;
lv_obj_t * fond;
lv_obj_t * Image4;
lv_obj_t * Label2;
lv_obj_t * ButtonRed;
lv_obj_t * ButtonOrange;
lv_obj_t * ButtonGreen;
lv_obj_t * ChoiceScreen;
lv_obj_t * fond2;
lv_obj_t * Label3;
lv_obj_t * ButtonRed2;
lv_obj_t * Image1;
lv_obj_t * stateChoice1;
lv_obj_t * raison1;
lv_obj_t * Button4;
lv_obj_t * raison1_copy;
lv_obj_t * StateScreen;
lv_obj_t * fond1;
lv_obj_t * Label1;
lv_obj_t * ButtonRed1;
lv_obj_t * Image12;
lv_obj_t * raison;
lv_obj_t * ButtonMachine;
lv_obj_t * MAchine;
lv_obj_t * raison_copy;
lv_obj_t * Robot;
lv_obj_t * ButtonRobot;

///////////////////// IMAGES ////////////////////
LV_IMG_DECLARE(img701552271);   // assets\logo-USIDUC.png

///////////////////// FUNCTIONS ////////////////////
#define BAR_PROPERTY_VALUE 0
#define BAR_PROPERTY_VALUE_WITH_ANIM 1

void SetBarProperty(lv_obj_t * target, int id, int val)
{
    if(id == BAR_PROPERTY_VALUE_WITH_ANIM) lv_bar_set_value(target, val, LV_ANIM_ON);
    if(id == BAR_PROPERTY_VALUE) lv_bar_set_value(target, val, LV_ANIM_OFF);
}

#define BASIC_PROPERTY_POSITION_X 0
#define BASIC_PROPERTY_POSITION_Y 1
#define BASIC_PROPERTY_WIDTH 2
#define BASIC_PROPERTY_HEIGHT 3
#define BASIC_PROPERTY_CLICKABLE 4
#define BASIC_PROPERTY_HIDDEN 5
#define BASIC_PROPERTY_DRAGABLE 6
#define BASIC_PROPERTY_DISABLED 7

void SetBasicProperty(lv_obj_t * target, int id, int val)
{
    if(id == BASIC_PROPERTY_POSITION_X) lv_obj_set_x(target, val);
    if(id == BASIC_PROPERTY_POSITION_Y) lv_obj_set_y(target, val);
    if(id == BASIC_PROPERTY_WIDTH) lv_obj_set_width(target, val);
    if(id == BASIC_PROPERTY_HEIGHT) lv_obj_set_height(target, val);
}

void SetBasicPropertyB(lv_obj_t * target, int id, bool val)
{
    if(id == BASIC_PROPERTY_CLICKABLE) lv_obj_set_click(target, val);
    if(id == BASIC_PROPERTY_HIDDEN) lv_obj_set_hidden(target, val);
    if(id == BASIC_PROPERTY_DRAGABLE) lv_obj_set_drag(target, val);
    if(id == BASIC_PROPERTY_DISABLED) {
        if(val) lv_obj_add_state(target, LV_STATE_DISABLED);
        else lv_obj_clear_state(target, LV_STATE_DISABLED);
    }
}

#define BUTTON_PROPERTY_TOGGLE 0
#define BUTTON_PROPERTY_CHECKED 1

void SetButtonProperty(lv_obj_t * target, int id, bool val)
{
    if(id == BUTTON_PROPERTY_TOGGLE) lv_btn_toggle(target);
    if(id == BUTTON_PROPERTY_CHECKED) lv_btn_set_state(target, val ? LV_BTN_STATE_CHECKED_RELEASED : LV_BTN_STATE_RELEASED);
}

#define DROPDOWN_PROPERTY_SELECTED 0

void SetDropdownProperty(lv_obj_t * target, int id, int val)
{
    if(id == DROPDOWN_PROPERTY_SELECTED) lv_dropdown_set_selected(target, val);
}

#define IMAGE_PROPERTY_IMAGE 0

void SetImageProperty(lv_obj_t * target, int id, uint8_t * val)
{
    if(id == IMAGE_PROPERTY_IMAGE) lv_img_set_src(target, val);
}

#define LABEL_PROPERTY_TEXT 0

void SetLabelProperty(lv_obj_t * target, int id, char * val)
{
    if(id == LABEL_PROPERTY_TEXT) lv_label_set_text(target, val);
}

#define ROLLER_PROPERTY_SELECTED 0
#define ROLLER_PROPERTY_SELECTED_WITH_ANIM 1

void SetRollerProperty(lv_obj_t * target, int id, int val)
{
    if(id == ROLLER_PROPERTY_SELECTED_WITH_ANIM) lv_roller_set_selected(target, val, LV_ANIM_ON);
    if(id == ROLLER_PROPERTY_SELECTED) lv_roller_set_selected(target, val, LV_ANIM_OFF);
}

#define SLIDER_PROPERTY_VALUE 0
#define SLIDER_PROPERTY_VALUE_WITH_ANIM 1

void SetSliderProperty(lv_obj_t * target, int id, int val)
{
    if(id == SLIDER_PROPERTY_VALUE_WITH_ANIM) lv_slider_set_value(target, val, LV_ANIM_ON);
    if(id == SLIDER_PROPERTY_VALUE) lv_slider_set_value(target, val, LV_ANIM_OFF);
}

void ChangeScreen(lv_obj_t * target, int fademode, int spd, int delay)
{
    lv_scr_load_anim(target, fademode, spd, delay, false);
}

void SetOpacity(lv_obj_t * target, int val)
{
    lv_obj_set_style_local_opa_scale(target, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, val);
}

void anim_callback_set_x(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_x(a->user_data, v);
}

void anim_callback_set_y(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_y(a->user_data, v);
}

void anim_callback_set_width(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_width(a->user_data, v);
}

void anim_callback_set_height(lv_anim_t * a, lv_anim_value_t v)
{
    lv_obj_set_height(a->user_data, v);
}

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS2 ////////////////////
static void fond_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void fond2_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void stateChoice1_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void Button4_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}
static void fond1_eventhandler(lv_obj_t * obj, lv_event_t event)
{
}

///////////////////// SCREENS ////////////////////
void BuildPages(void)
{
    HomeScreen = lv_obj_create(NULL, NULL);

    fond = lv_obj_create(HomeScreen, NULL);
    lv_obj_set_click(fond, true);
    lv_obj_set_hidden(fond, false);
    lv_obj_clear_state(fond, LV_STATE_DISABLED);
    lv_obj_set_size(fond, 320, 240);  // force: 0
    lv_obj_align(fond, HomeScreen, LV_ALIGN_CENTER, 0, 0); // force: 320
    lv_obj_set_drag(fond, true);
    lv_obj_set_event_cb(fond, fond_eventhandler);
    lv_obj_set_style_local_bg_color(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_bg_opa(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_bg_grad_color(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(52 * 256 * 256 + 52 * 256 + 52));
    lv_obj_set_style_local_bg_main_stop(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_stop(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_radius(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_dir(fond, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    Image4 = lv_img_create(HomeScreen, NULL);
    lv_img_set_src(Image4, &img701552271);
    lv_obj_set_click(Image4, false);
    lv_obj_set_hidden(Image4, false);
    lv_obj_set_size(Image4, 100, 27);
    lv_obj_align(Image4, HomeScreen, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_obj_set_drag(Image4, false);

    lv_obj_clear_state(Image4, LV_STATE_DISABLED);

    Label2 = lv_label_create(HomeScreen, NULL);
    lv_label_set_long_mode(Label2, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(Label2, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(Label2, "PROGRAMME PME 4.0");
    lv_obj_set_size(Label2, 160, 16);  // force: 72
    lv_obj_set_click(Label2, false);
    lv_obj_set_hidden(Label2, false);
    lv_obj_clear_state(Label2, LV_STATE_DISABLED);
    lv_obj_set_drag(Label2, false);

    lv_obj_align(Label2, HomeScreen, LV_ALIGN_CENTER, 72, 103); // force: 160

    ButtonRed = lv_btn_create(HomeScreen, NULL);
    lv_btn_set_checkable(ButtonRed, false);
    if(false) lv_btn_set_state(ButtonRed, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonRed, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonRed, false);
    lv_obj_set_hidden(ButtonRed, false);
    lv_obj_clear_state(ButtonRed, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonRed, 60, 60);  // force: 45
    lv_obj_align(ButtonRed, HomeScreen, LV_ALIGN_IN_TOP_LEFT, 45, 98); // force: 60
    lv_obj_set_drag(ButtonRed, false);
    lv_obj_set_style_local_bg_color(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_bg_opa(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_shadow_opa(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 180);
    lv_obj_set_style_local_shadow_width(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
    lv_obj_set_style_local_shadow_spread(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_shadow_ofs_x(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(ButtonRed, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    ButtonOrange = lv_btn_create(HomeScreen, NULL);
    lv_btn_set_checkable(ButtonOrange, false);
    if(false) lv_btn_set_state(ButtonOrange, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonOrange, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonOrange, false);
    lv_obj_set_hidden(ButtonOrange, false);
    lv_obj_clear_state(ButtonOrange, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonOrange, 60, 60);  // force: 127
    lv_obj_align(ButtonOrange, HomeScreen, LV_ALIGN_IN_TOP_LEFT, 127, 99); // force: 60
    lv_obj_set_drag(ButtonOrange, false);
    lv_obj_set_style_local_bg_color(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 150 * 256 + 0));
    lv_obj_set_style_local_bg_opa(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(255 * 256 * 256 + 150 * 256 + 0));
    lv_obj_set_style_local_shadow_opa(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 180);
    lv_obj_set_style_local_shadow_width(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
    lv_obj_set_style_local_shadow_spread(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_shadow_ofs_x(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(ButtonOrange, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    ButtonGreen = lv_btn_create(HomeScreen, NULL);
    lv_btn_set_checkable(ButtonGreen, false);
    if(false) lv_btn_set_state(ButtonGreen, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonGreen, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonGreen, false);
    lv_obj_set_hidden(ButtonGreen, false);
    lv_obj_clear_state(ButtonGreen, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonGreen, 60, 60);  // force: 206
    lv_obj_align(ButtonGreen, HomeScreen, LV_ALIGN_IN_TOP_LEFT, 206, 98); // force: 60
    lv_obj_set_drag(ButtonGreen, false);
    lv_obj_set_style_local_bg_color(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(0 * 256 * 256 + 255 * 256 + 40));
    lv_obj_set_style_local_bg_opa(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 255 * 256 + 40));
    lv_obj_set_style_local_shadow_opa(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 180);
    lv_obj_set_style_local_shadow_width(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
    lv_obj_set_style_local_shadow_spread(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_shadow_ofs_x(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(ButtonGreen, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    ChoiceScreen = lv_obj_create(NULL, NULL);

    fond2 = lv_obj_create(ChoiceScreen, NULL);
    lv_obj_set_click(fond2, true);
    lv_obj_set_hidden(fond2, false);
    lv_obj_clear_state(fond2, LV_STATE_DISABLED);
    lv_obj_set_size(fond2, 320, 240);  // force: 0
    lv_obj_align(fond2, ChoiceScreen, LV_ALIGN_CENTER, 0, 0); // force: 320
    lv_obj_set_drag(fond2, true);
    lv_obj_set_event_cb(fond2, fond2_eventhandler);
    lv_obj_set_style_local_bg_color(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_bg_opa(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_bg_grad_color(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(52 * 256 * 256 + 52 * 256 + 52));
    lv_obj_set_style_local_bg_main_stop(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_stop(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_radius(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_dir(fond2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    Label3 = lv_label_create(ChoiceScreen, NULL);
    lv_label_set_long_mode(Label3, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(Label3, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(Label3, "PROGRAMME PME 4.0");
    lv_obj_set_size(Label3, 160, 16);  // force: 72
    lv_obj_set_click(Label3, false);
    lv_obj_set_hidden(Label3, false);
    lv_obj_clear_state(Label3, LV_STATE_DISABLED);
    lv_obj_set_drag(Label3, false);

    lv_obj_align(Label3, ChoiceScreen, LV_ALIGN_CENTER, 72, 103); // force: 160

    ButtonRed2 = lv_btn_create(ChoiceScreen, NULL);
    lv_btn_set_checkable(ButtonRed2, false);
    if(false) lv_btn_set_state(ButtonRed2, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonRed2, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonRed2, false);
    lv_obj_set_hidden(ButtonRed2, false);
    lv_obj_clear_state(ButtonRed2, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonRed2, 60, 60);  // force: 247
    lv_obj_align(ButtonRed2, ChoiceScreen, LV_ALIGN_IN_TOP_LEFT, 247, 10); // force: 60
    lv_obj_set_drag(ButtonRed2, false);
    lv_obj_set_style_local_bg_color(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_bg_opa(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_shadow_opa(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 180);
    lv_obj_set_style_local_shadow_width(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
    lv_obj_set_style_local_shadow_spread(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_shadow_ofs_x(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(ButtonRed2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    Image1 = lv_img_create(ChoiceScreen, NULL);
    lv_img_set_src(Image1, &img701552271);
    lv_obj_set_click(Image1, false);
    lv_obj_set_hidden(Image1, false);
    lv_obj_set_size(Image1, 100, 27);
    lv_obj_align(Image1, ChoiceScreen, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_obj_set_drag(Image1, false);

    lv_obj_clear_state(Image1, LV_STATE_DISABLED);

    stateChoice1 = lv_dropdown_create(ChoiceScreen, NULL);
    lv_dropdown_set_dir(stateChoice1, LV_DROPDOWN_DIR_UP);
    lv_dropdown_set_options(stateChoice1,
                            "R1 - blocage Robot\nR2 - Graissage\nR3 - bla bla\nR4 - bla bla\nR5- bla bla\nR6 - bla bla\nR7 - bla bla\nR8 - bla bla\nR9 - bla bla");
    lv_dropdown_set_show_selected(stateChoice1, true);
    lv_dropdown_set_text(stateChoice1, "");
    lv_dropdown_set_max_height(stateChoice1, 250);
    lv_obj_set_click(stateChoice1, true);
    lv_obj_set_hidden(stateChoice1, false);
    lv_obj_clear_state(stateChoice1, LV_STATE_DISABLED);
    lv_obj_set_drag(stateChoice1, true);
    lv_obj_align(stateChoice1, ChoiceScreen, LV_ALIGN_IN_BOTTOM_LEFT, 106, -97);
    lv_obj_set_event_cb(stateChoice1, stateChoice1_eventhandler);
    lv_obj_set_style_local_shadow_color(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(255 * 256 * 256 + 16 * 256 + 40));
    lv_obj_set_style_local_shadow_opa(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_shadow_width(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, 100);
    lv_obj_set_style_local_shadow_spread(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_x(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(stateChoice1, LV_DROPDOWN_PART_MAIN, LV_STATE_DEFAULT, 0);

    raison1 = lv_label_create(ChoiceScreen, NULL);
    lv_label_set_long_mode(raison1, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(raison1, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(raison1, "RAISON");
    lv_obj_set_size(raison1, 81, 22);  // force: -106
    lv_obj_set_click(raison1, false);
    lv_obj_set_hidden(raison1, false);
    lv_obj_clear_state(raison1, LV_STATE_DISABLED);
    lv_obj_set_drag(raison1, false);
    lv_obj_set_style_local_text_color(raison1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(raison1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(raison1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_20);

    lv_obj_align(raison1, ChoiceScreen, LV_ALIGN_CENTER, -106, 0); // force: 81

    Button4 = lv_btn_create(ChoiceScreen, NULL);
    lv_btn_set_checkable(Button4, false);
    if(false) lv_btn_set_state(Button4, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(Button4, LV_LAYOUT_OFF);
    lv_obj_set_click(Button4, true);
    lv_obj_set_hidden(Button4, false);
    lv_obj_clear_state(Button4, LV_STATE_DISABLED);
    lv_obj_set_size(Button4, 150, 40);  // force: 2
    lv_obj_align(Button4, ChoiceScreen, LV_ALIGN_CENTER, 2, 59); // force: 150
    lv_obj_set_drag(Button4, false);
    lv_obj_set_event_cb(Button4, Button4_eventhandler);
    lv_obj_set_style_local_bg_color(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(0 * 256 * 256 + 255 * 256 + 40));
    lv_obj_set_style_local_bg_opa(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(0 * 256 * 256 + 255 * 256 + 40));
    lv_obj_set_style_local_shadow_opa(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_shadow_width(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 100);
    lv_obj_set_style_local_shadow_spread(Button4, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);

    raison1_copy = lv_label_create(ChoiceScreen, NULL);
    lv_label_set_long_mode(raison1_copy, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(raison1_copy, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(raison1_copy, "VALID");
    lv_obj_set_size(raison1_copy, 64, 22);  // force: 2
    lv_obj_set_click(raison1_copy, false);
    lv_obj_set_hidden(raison1_copy, false);
    lv_obj_clear_state(raison1_copy, LV_STATE_DISABLED);
    lv_obj_set_drag(raison1_copy, false);
    lv_obj_set_style_local_text_color(raison1_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(raison1_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(raison1_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_20);

    lv_obj_align(raison1_copy, ChoiceScreen, LV_ALIGN_CENTER, 2, 61); // force: 64

    StateScreen = lv_obj_create(NULL, NULL);

    fond1 = lv_obj_create(StateScreen, NULL);
    lv_obj_set_click(fond1, true);
    lv_obj_set_hidden(fond1, false);
    lv_obj_clear_state(fond1, LV_STATE_DISABLED);
    lv_obj_set_size(fond1, 320, 240);  // force: 0
    lv_obj_align(fond1, StateScreen, LV_ALIGN_CENTER, 0, 0); // force: 320
    lv_obj_set_drag(fond1, true);
    lv_obj_set_event_cb(fond1, fond1_eventhandler);
    lv_obj_set_style_local_bg_color(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0 * 256 * 256 + 0 * 256 + 0));
    lv_obj_set_style_local_bg_opa(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_bg_grad_color(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                         lv_color_hex(52 * 256 * 256 + 52 * 256 + 52));
    lv_obj_set_style_local_bg_main_stop(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_stop(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_radius(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_bg_grad_dir(fond1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    Label1 = lv_label_create(StateScreen, NULL);
    lv_label_set_long_mode(Label1, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(Label1, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(Label1, "PROGRAMME PME 4.0");
    lv_obj_set_size(Label1, 160, 16);  // force: 72
    lv_obj_set_click(Label1, false);
    lv_obj_set_hidden(Label1, false);
    lv_obj_clear_state(Label1, LV_STATE_DISABLED);
    lv_obj_set_drag(Label1, false);

    lv_obj_align(Label1, StateScreen, LV_ALIGN_CENTER, 72, 103); // force: 160

    ButtonRed1 = lv_btn_create(StateScreen, NULL);
    lv_btn_set_checkable(ButtonRed1, false);
    if(false) lv_btn_set_state(ButtonRed1, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonRed1, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonRed1, false);
    lv_obj_set_hidden(ButtonRed1, false);
    lv_obj_clear_state(ButtonRed1, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonRed1, 60, 60);  // force: 247
    lv_obj_align(ButtonRed1, StateScreen, LV_ALIGN_IN_TOP_LEFT, 247, 10); // force: 60
    lv_obj_set_drag(ButtonRed1, false);
    lv_obj_set_style_local_bg_color(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_bg_opa(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_color(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                        lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));
    lv_obj_set_style_local_shadow_opa(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 180);
    lv_obj_set_style_local_shadow_width(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 50);
    lv_obj_set_style_local_shadow_spread(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_obj_set_style_local_shadow_ofs_x(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_shadow_ofs_y(ButtonRed1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    Image12 = lv_img_create(StateScreen, NULL);
    lv_img_set_src(Image12, &img701552271);
    lv_obj_set_click(Image12, false);
    lv_obj_set_hidden(Image12, false);
    lv_obj_set_size(Image12, 100, 27);
    lv_obj_align(Image12, StateScreen, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_obj_set_drag(Image12, false);

    lv_obj_clear_state(Image12, LV_STATE_DISABLED);

    raison = lv_label_create(StateScreen, NULL);
    lv_label_set_long_mode(raison, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(raison, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(raison, "Equipement");
    lv_obj_set_size(raison, 128, 22);  // force: -5
    lv_obj_set_click(raison, false);
    lv_obj_set_hidden(raison, false);
    lv_obj_clear_state(raison, LV_STATE_DISABLED);
    lv_obj_set_drag(raison, false);
    lv_obj_set_style_local_text_color(raison, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(raison, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(raison, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_20);

    lv_obj_align(raison, StateScreen, LV_ALIGN_CENTER, -5, -35); // force: 128

    ButtonMachine = lv_btn_create(StateScreen, NULL);
    lv_btn_set_checkable(ButtonMachine, true);
    if(true) lv_btn_set_state(ButtonMachine, true ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonMachine, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonMachine, false);
    lv_obj_set_hidden(ButtonMachine, false);
    lv_obj_clear_state(ButtonMachine, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonMachine, 100, 50);  // force: -70
    lv_obj_align(ButtonMachine, StateScreen, LV_ALIGN_CENTER, -70, 40); // force: 100
    lv_obj_set_drag(ButtonMachine, false);
    lv_obj_set_style_local_bg_color(ButtonMachine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(0 * 256 * 256 + 204 * 256 + 255));
    lv_obj_set_style_local_bg_opa(ButtonMachine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonMachine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

    MAchine = lv_label_create(StateScreen, NULL);
    lv_label_set_long_mode(MAchine, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(MAchine, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(MAchine, "Machine");
    lv_obj_set_size(MAchine, 70, 18);  // force: -70
    lv_obj_set_click(MAchine, false);
    lv_obj_set_hidden(MAchine, false);
    lv_obj_clear_state(MAchine, LV_STATE_DISABLED);
    lv_obj_set_drag(MAchine, false);
    lv_obj_set_style_local_text_color(MAchine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(MAchine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(MAchine, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_16);

    lv_obj_align(MAchine, StateScreen, LV_ALIGN_CENTER, -70, 42); // force: 70

    raison_copy = lv_label_create(StateScreen, NULL);
    lv_label_set_long_mode(raison_copy, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(raison_copy, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(raison_copy, "Equipement");
    lv_obj_set_size(raison_copy, 128, 22);  // force: -5
    lv_obj_set_click(raison_copy, false);
    lv_obj_set_hidden(raison_copy, false);
    lv_obj_clear_state(raison_copy, LV_STATE_DISABLED);
    lv_obj_set_drag(raison_copy, false);
    lv_obj_set_style_local_text_color(raison_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(raison_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(raison_copy, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_20);

    lv_obj_align(raison_copy, StateScreen, LV_ALIGN_CENTER, -5, -35); // force: 128

    Robot = lv_label_create(StateScreen, NULL);
    lv_label_set_long_mode(Robot, LV_LABEL_LONG_EXPAND);
    lv_label_set_align(Robot, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(Robot, "Machine");
    lv_obj_set_size(Robot, 70, 18);  // force: -49
    lv_obj_set_click(Robot, false);
    lv_obj_set_hidden(Robot, false);
    lv_obj_clear_state(Robot, LV_STATE_DISABLED);
    lv_obj_set_drag(Robot, false);
    lv_obj_set_style_local_text_color(Robot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                      lv_color_hex(255 * 256 * 256 + 255 * 256 + 255));
    lv_obj_set_style_local_text_opa(Robot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_text_font(Robot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_font_montserrat_16);

    lv_obj_align(Robot, StateScreen, LV_ALIGN_CENTER, -49, 44); // force: 70

    ButtonRobot = lv_btn_create(StateScreen, NULL);
    lv_btn_set_checkable(ButtonRobot, true);
    if(true) lv_btn_set_state(ButtonRobot, true ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
    lv_btn_set_layout(ButtonRobot, LV_LAYOUT_OFF);
    lv_obj_set_click(ButtonRobot, false);
    lv_obj_set_hidden(ButtonRobot, false);
    lv_obj_clear_state(ButtonRobot, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonRobot, 100, 50);  // force: -70
    lv_obj_align(ButtonRobot, StateScreen, LV_ALIGN_CENTER, -70, 40); // force: 100
    lv_obj_set_drag(ButtonRobot, false);
    lv_obj_set_style_local_bg_color(ButtonRobot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
                                    lv_color_hex(0 * 256 * 256 + 204 * 256 + 255));
    lv_obj_set_style_local_bg_opa(ButtonRobot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_border_width(ButtonRobot, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, 0);

}

