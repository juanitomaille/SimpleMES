#define DEBUG  // uncomment this line for debug


/********************************
*                               *
*        INCLUDES               *
*                               *
*******************************/

#include "debug.h"


#include <WiFi.h>
#include <PubSubClient.h> /* MQTT lib */

#include "DisplaySetup.h"
#include "lvgl.h"
#include "lv_port_indev.h" /* input Driver for lvgl */


#include "logo_usiduc.c"

/********************************
*                               *
*        DEFINES                *
*                               *
*******************************/


#define LN  1


#define I2C_SCL 39
#define I2C_SDA 38

#define MSG_BUFFER_SIZE	(50)

/********************************
*                               *
*        VARIABLES              *
*                               *
*******************************/


// Configure the name and password of the connected wifi and your MQTT Serve host.
const char* ssid = "FACTORYBOX";
const char* password = "Jm9r5F3W";
const char* mqtt_server = "factorybox";

unsigned long lastMsg = 0;

char msg[MSG_BUFFER_SIZE];
int value = 0;
char data[3];
char code[3]; // Color of column : 000 = no color; 100 = green, 010 = orange, 001 = red


float t = 19; // just for test



//Change to your screen resolution
static const uint32_t screenWidth  = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];





/********************************
*                               *
*        Prototypes             *
*                               *
*******************************/


void setupWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reConnect();



/********************************
*                               *
*        declarations           *
*                               *
*******************************/









/////////////////////////
//   COMMUNICATIONS    //
/////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);


void setupWifi() {
  delay(10);
  DPRINT("setupWifi | ");
  DPRINT("Connecting to ");
  DPRINT(ssid);
  DPRINTLN("(SSID)");

  message_txt ("Connecting to ");
  message_txt (ssid, LN);



  WiFi.mode(WIFI_STA);  //Set the mode to WiFi station mode.  
  WiFi.begin(ssid, password); //Start Wifi connection.  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DPRINT(".");
    message_txt (".");
  }
  DPRINTLN("ok");
  DPRINTLN("Success");
  message_txt ("ok", LN);
  message_txt_green ("Succes");

}

void callback(char* topic, byte* payload, unsigned int length) {
  DPRINT("Message arrived [");
  DPRINT(topic);
  DPRINT("] ");
  for (int i = 0; i < length; i++) {
    DPRINT((char)payload[i]);
  }
  DPRINTLN();
}

void reConnect() {
  while (!client.connected()) {
    DPRINTLN("Attempting MQTT connection...");
    message_txt("Attempting MQTT connection...", LN);
    // Create a random client ID.  
    String clientId = "UPRISE-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect.  尝试重新连接
    if (client.connect(clientId.c_str())) {
      DPRINTLN("Success");
    message_txt_green ("Succes");

      // Once connected, publish an announcement to the topic.  
      client.publish("M5Stack", "hello world");
      // ... and resubscribe.  
      client.subscribe("M5Stack");
    } else {
      DPRINT("failed, rc=");
      DPRINT(client.state());
      DPRINTLN(" -> try again in 5 seconds");
        message_txt_red ("Failed, rc=");
        //message_txt((const char*) client.state());
        message_txt_red(" -> try again in 5 seconds", LN);

      delay(5000);
    }
  }
}




/////////////////////////
//       DISPLAY       //
/////////////////////////





static void mask_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    static int16_t mask_top_id = -1;
    static int16_t mask_bottom_id = -1;

    if (code == LV_EVENT_COVER_CHECK) {
        lv_event_set_cover_res(e, LV_COVER_RES_MASKED);

    } else if (code == LV_EVENT_DRAW_MAIN_BEGIN) {
        /* add mask */
        const lv_font_t * font = lv_obj_get_style_text_font(obj, LV_PART_MAIN);
        lv_coord_t line_space = lv_obj_get_style_text_line_space(obj, LV_PART_MAIN);
        lv_coord_t font_h = lv_font_get_line_height(font);

        lv_area_t roller_coords;
        lv_obj_get_coords(obj, &roller_coords);

        lv_area_t rect_area;
        rect_area.x1 = roller_coords.x1;
        rect_area.x2 = roller_coords.x2;
        rect_area.y1 = roller_coords.y1;
        rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;

        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *) lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
        mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);

        rect_area.y1 = rect_area.y2 + font_h + line_space - 1;
        rect_area.y2 = roller_coords.y2;

        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)  lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
        lv_draw_mask_fade_init(fade_mask_bottom, &rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
        mask_bottom_id = lv_draw_mask_add(fade_mask_bottom, NULL);

    } else if (code == LV_EVENT_DRAW_POST_END) {
        lv_draw_mask_fade_param_t * fade_mask_top = (lv_draw_mask_fade_param_t *)  lv_draw_mask_remove_id(mask_top_id);
        lv_draw_mask_fade_param_t * fade_mask_bottom = (lv_draw_mask_fade_param_t *)  lv_draw_mask_remove_id(mask_bottom_id);
        lv_draw_mask_free_param(fade_mask_top);
        lv_draw_mask_free_param(fade_mask_bottom);
        lv_mem_buf_release(fade_mask_top);
        lv_mem_buf_release(fade_mask_bottom);
        mask_top_id = -1;
        mask_bottom_id = -1;
    }
}

/**
 * Add a fade mask to roller.
 */
void lv_example_roller_3(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, lv_color_black());
    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_border_width(&style, 0);
    lv_style_set_pad_all(&style, 0);
    lv_obj_add_style(lv_scr_act(), &style, 0);

    lv_obj_t *roller1 = lv_roller_create(lv_scr_act());
    lv_obj_add_style(roller1, &style, 0);
    lv_obj_set_style_bg_opa(roller1, LV_OPA_TRANSP, LV_PART_SELECTED);

    #if LV_FONT_MONTSERRAT_22
        lv_obj_set_style_text_font(roller1, &lv_font_montserrat_22, LV_PART_SELECTED);
    #endif

    lv_roller_set_options(roller1,
                        "ARRET 1 - Changement d'outil\n"
                        "ARRET 2 - probleme robot\n"
                        "ARRET 3 - Probleme enbarreur\n"
                        "ARRET 4 - probleme bras\n"
                        "ARRET 5 - probleme xxxxx\n"
                        "ARRET 6 - probleme yyyyyyyyyyyyyyyy\n"
                        "ARRET 7 - probleme ssfh bhjj jjjkj\n"
                        "ARRET 8 - robot calé\n"
                        "ARRET 9 - probleme robot\n",
                        LV_ROLLER_MODE_NORMAL);

    lv_obj_center(roller1);
    lv_roller_set_visible_row_count(roller1, 3);
    lv_obj_add_event_cb(roller1, mask_event_cb, LV_EVENT_ALL, NULL);
}

// Logo of customer
void lv_img_logo(void)

{   

    lv_obj_t * logo = lv_img_create(lv_scr_act());
    lv_img_set_src(logo, &logo_usiduc);
    lv_obj_set_size(logo, 100, 27);
    lv_obj_align(logo, LV_ALIGN_TOP_LEFT, 10, 10);

    LV_IMG_DECLARE(logo_usiduc); 

}



// buttons 
void construct_buttons(void)
{
    int button_size = 100;
    int button_alt = 110;
    lv_obj_t * ButtonRed = lv_btn_create(lv_scr_act());
//    if(false) lv_btn_set_state(ButtonRed, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
//    lv_btn_set_layout(ButtonRed, LV_LAYOUT_OFF);
//    lv_obj_set_click(ButtonRed, false);
//    lv_obj_set_hidden(ButtonRed, false);
//    lv_obj_clear_state(ButtonRed, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonRed, button_size, button_size);  // force: 45
    lv_obj_align(ButtonRed, LV_ALIGN_TOP_LEFT, 45, button_alt); // force: 60
//    lv_obj_set_drag(ButtonRed, false);
    lv_obj_set_style_bg_color(ButtonRed, lv_color_hex(255 * 256 * 256 + 52 * 256 + 16), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonRed, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonRed, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonRed, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonRed, lv_color_hex(255 * 256 * 256 + 52 * 256 + 16), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ButtonRed, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonRed, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonRed, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonRed, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonRed, 0, LV_STATE_DEFAULT);

    lv_obj_t * ButtonOrange = lv_btn_create(lv_scr_act());
//    lv_btn_set_checkable(ButtonOrange, false);
//    if(false) lv_btn_set_state(ButtonOrange, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
//    lv_btn_set_layout(ButtonOrange, LV_LAYOUT_OFF);
//    lv_obj_set_click(ButtonOrange, false);
//   lv_obj_set_hidden(ButtonOrange, false);
//    lv_obj_clear_state(ButtonOrange, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonOrange, button_size, button_size);  // force: 127
    lv_obj_align(ButtonOrange, LV_ALIGN_TOP_LEFT, 180, button_alt); // force: 60
//    lv_obj_set_drag(ButtonOrange, false);
    lv_obj_set_style_bg_color(ButtonOrange, lv_color_hex(255 * 256 * 256 + 150 * 256 + 0), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ButtonOrange, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonOrange, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonOrange, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonOrange, lv_color_hex(255 * 256 * 256 + 150 * 256 + 0), LV_STATE_DEFAULT );
    lv_obj_set_style_shadow_opa(ButtonOrange, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonOrange, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonOrange, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonOrange, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonOrange, 0, LV_STATE_DEFAULT);

    lv_obj_t * ButtonGreen = lv_btn_create(lv_scr_act());
//    lv_btn_set_checkable(ButtonGreen, false);
//    if(false) lv_btn_set_state(ButtonGreen, false ? LV_STATE_CHECKED : LV_STATE_DEFAULT);
//    lv_btn_set_layout(ButtonGreen, LV_LAYOUT_OFF);
//    lv_obj_set_click(ButtonGreen, false);
//    lv_obj_set_hidden(ButtonGreen, false);
//    lv_obj_clear_state(ButtonGreen, LV_STATE_DISABLED);
    lv_obj_set_size(ButtonGreen, button_size, button_size);  // force: 206
    lv_obj_align(ButtonGreen, LV_ALIGN_TOP_LEFT, 320, button_alt); // force: 60
//    lv_obj_set_drag(ButtonGreen, false);
    lv_obj_set_style_bg_color(ButtonGreen, lv_color_hex(0 * 256 * 256 + 255 * 256 + 40), LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ButtonGreen, 255, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ButtonGreen, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ButtonGreen, LV_RADIUS_CIRCLE, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ButtonGreen, lv_color_hex(0 * 256 * 256 + 255 * 256 + 40), LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ButtonGreen, 180, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ButtonGreen, 50, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ButtonGreen, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ButtonGreen, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ButtonGreen, 0, LV_STATE_DEFAULT);

}


void Machine_stopped_message(void)
{
    
    lv_obj_clean(lv_scr_act());
    change_bg(LV_PALETTE_ORANGE);

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
    lv_label_set_text(main_label, "  ARRET\n"
                                    "MACHINE");


    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
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
}



/////////////////////////
//       SETUP         //
/////////////////////////




void setup(void)
{
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_BLK, OUTPUT);

    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_BLK, HIGH);

    DBEGIN(9600);


    /* LGVL init - graphic library */
    lv_init();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );

    /* LCD screen begin */
    lcd.init();
    lcd.setRotation(1);
    lcd.setBrightness(255);


    lcd.fillScreen(TFT_BLACK);


    //Initialize the display inside LGVL
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    //Change the following line to your display resolution in LGVL
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);


    message_welcome("UP-RISE SAS - PART of PME4.0");



    setupWifi(); // concrens wifi setup
    client.setServer(mqtt_server, 1883);  //Sets the MQTT server details.  
    client.setCallback(callback); //Sets the message callback function for MQTT

    //Serial.setTextColor(YELLOW);  //Set the font color to yellow. 
    //Serial.setTextSize(1);  //Set the font size to 2.  
    DPRINTLN("PME4.0 - Machine State -DEBUG"); //Print a string on the screen.  
    delay(1000);
    //Serial.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    //Serial.setTextColor(WHITE);  //Set the font color to yellow. 






    //Initialize the (dummy) input device driver in LGVL (lib/lv_port_indev_init)
    lv_port_indev_init();


    //**** Declare all graphics *****/

 //   lv_example_roller_3();

    //construct_buttons();

    //lv_img_logo();
    //Machine_stopped_message();
    //Machine_producing_message();
    //Machine_available_message();
    //Machine_error_message();
   // No_machine_message();


}


/////////////////////////
//       LOOP          //
/////////////////////////

int last_vert;
int last_orange;
int last_rouge;

int vert;
int orange; 
int rouge;


void loop()
{
    //MQTT communication
    if (!client.connected()) {
        reConnect();
    }
    client.loop();  //MQTT : This function is called periodically to allow clients to process incoming messages and maintain connections to the server.

    unsigned long now = millis(); //Obtain the host startup duration.  
    if (now - lastMsg > 2000) 
    {
        lastMsg = now;
        ++value;

        client.publish("M5Stack/temp", String(t).c_str());  //Publishes a message to the specified topic.  
        
        /*    
        Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
        int i = 0;
        while(Wire.available())    // slave may send less than requested
        {
            char c = Wire.read();    // receive a byte as character
            data[i] = c;
            i = i + 1 ;
            DPRINT("I2C Receive :");
            DPRINTLN(c); 
        }

        vert = data[0] - '0'; // method to convert char in int
        orange = data[1] - '0';
        rouge = data[2] - '0';
        */

    }
    else
    {
        vert = last_vert;  // we keep last value before delay
        rouge = last_rouge;
        orange = last_orange;
    }

    
    Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
    int i = 0;
    while(Wire.available())    // slave may send less than requested
    {
        char c = Wire.read();    // receive a byte as character
        data[i] = c;
        i = i + 1 ;
//        DPRINT("I2C Receive :");
//        DPRINTLN(c); 
    }

    vert = data[0] - '0'; // method to convert char in int
    orange = data[1] - '0';
    rouge = data[2] - '0';



    if (last_rouge != rouge | last_vert != vert | last_orange != orange )
    {




        DPRINT("SimpleMES | Etat machine :");
        DPRINT("Vert/orange/rouge -> ");
        DPRINT(vert);
        DPRINT(orange);
        DPRINTLN(rouge);


        if (vert == 1 && orange == 0 && rouge == 0 )
        {
            DPRINTLN("SimpleMES | Machine en production");
            Machine_producing_message();
        }
        else if (orange == 1 && vert == 0 && rouge == 0)
        {
            DPRINTLN("SimpleMES | Machine en arrêt");
            Machine_stopped_message();
            
        }
        else if (rouge == 1 && vert == 0 && orange == 0)
        {
            DPRINTLN("SimpleMES | Machine disponible");
            Machine_available_message();
        }
        else if (vert == 1 && rouge == 1 && orange ==0 )
        {
            DPRINTLN("SimpleMES | Machine en arrêt");
            Machine_stopped_message();
        }
        else if (vert == 0 && rouge == 0 && orange == 0)
        {
            DPRINTLN("SimpleMES | Pas de signal");
            No_machine_message(); // pas de signal
        }

        else 
        {
            DPRINTLN("SimpleMES | Erreur !");
            Machine_error_message();
        }
    }
    
    


    last_vert = vert;
    last_orange = orange;
    last_rouge = rouge;

    lv_timer_handler(); /* let the GUI do its work */
    //delay(200); /* only for debgging */
}
