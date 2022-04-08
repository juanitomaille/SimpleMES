
/**
 * @file status_messages.h
 *
 */

 /*set this value to "1" to enable content*/

#if 1


/********************************
*                               *
*        INCLUDES               *
*                               *
*******************************/

#include "lvgl.h"
#include "debug.h"



/********************************
*                               *
*        DEFINES                *
*                               *
*******************************/

/********************************
*                               *
*        VARIABLES              *
*                               *
*******************************/

int button_size = 100;

/********************************
*                               *
*      Global Prototypes        *
*                               *
*******************************/


//void construct_button(button_name, button_x_coord, button_y_coord, button_color);



void Machine_stopped_message(void);
void Machine_producing_message(void);
void Machine_available_message(void);
void No_machine_message(void);
void Machine_error_message(void);
void sending_error_message(String);

/********************************
*                               *
*      Static Prototypes        *
*                               *
*******************************/







/**********************
 *   GLOBAL FUNCTIONS
 **********************/






/*

// build a button
void construct_button(button_name, button_x_coord, button_y_coord, button_color)

{


    // color lv_color_hex(255 * 256 * 256 + 52 * 256 + 16)
    
    lv_obj_t * button_name = lv_btn_create(lv_scr_act());

    lv_obj_set_size(button_name, button_size, button_size);  
    lv_obj_align(button_name, LV_ALIGN_TOP_LEFT, button_x_coord, button_y_coord); 
    lv_obj_set_style_bg_color(button_name, button_color, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(button_name, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(button_name, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(button_name, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(button_name, button_color, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(button_name, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(button_name, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(button_name, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(button_name, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(button_name, 0, LV_STATE_DEFAULT);

}
*/



// most important Message : User should indicate why the machine is stopped
void Machine_stopped_message(void)
{
    
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_ORANGE);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_36);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_36);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, "  ARRET MACHINE");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, -100);

    // show a list of cause 


    //construct_button("P1_button", 45, 110, lv_color_hex(255 * 256 * 256 + 52 * 256 + 16));


    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE ORANGE ARRET ");
}

void Machine_producing_message(void)
{
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_GREEN);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_48);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_48);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, "PRODUCTION");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE VERT PROD");
}

void Machine_available_message(void)
{
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_RED);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_48);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_48);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, "DISPONIBLE");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE ROUGE ");
}

void No_machine_message(void)
{
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_DEEP_PURPLE);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_48);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_48);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, "NO SIGNAL");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE VIOLET NO SIGNAL ");
}

void Machine_error_message(void)
{
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_DEEP_ORANGE);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_48);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_48);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, "ERREUR");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE ERREUR ");
}

void sending_error_message(String error_message)
{
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_DEEP_ORANGE);

    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());
    lv_style_set_text_font(&style_shadow, &lv_font_montserrat_48);

    static lv_style_t txt_style;
    lv_style_init(&txt_style);
    lv_style_set_text_font(&txt_style, &lv_font_montserrat_48);


    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t * shadow_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t * main_label = lv_label_create(lv_scr_act());
    lv_obj_add_style(main_label, &txt_style, 0);
    lv_label_set_text(main_label, error_message.c_str());


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    DPRINTLN("AFFICHAGE MESSAGE ERREUR d'envoi ");
}


/**********************
 *   STATIC FUNCTIONS
 **********************/



#endif /*Disable/Enable content*/