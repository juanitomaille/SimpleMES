/********************************
*                               *
*        INCLUDES               *
*                               *
*******************************/


#include "DisplaySetup.h"
#include <lvgl.h>
#include "lv_port_indev.h" /* input Driver for lvgl */
#include <WiFi.h>
#include <PubSubClient.h> /* MQTT lib */

#include "logo_usiduc.c"

/********************************
*                               *
*        DEFINES                *
*                               *
*******************************/


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
  Serial.printf("Connecting to %s",ssid);
  WiFi.mode(WIFI_STA);  //Set the mode to WiFi station mode.  
  WiFi.begin(ssid, password); //Start Wifi connection.  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nSuccess\n");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reConnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID.  
    String clientId = "M5Stack-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect.  尝试重新连接
    if (client.connect(clientId.c_str())) {
      Serial.printf("\nSuccess\n");
      // Once connected, publish an announcement to the topic.  
      client.publish("M5Stack", "hello world");
      // ... and resubscribe.  
      client.subscribe("M5Stack");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}




/////////////////////////
//       DISPLAY       //
/////////////////////////



// Display flushing 
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   lcd.startWrite();
   lcd.setAddrWindow( area->x1, area->y1, w, h );
   //lcd.pushColors( ( uint16_t * )&color_p->full, w * h, true );
   lcd.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
   lcd.endWrite();

   lv_disp_flush_ready( disp );
}


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




/////////////////////////
//       SETUP         //
/////////////////////////




void setup(void)
{
    pinMode(LCD_CS, OUTPUT);
    pinMode(LCD_BLK, OUTPUT);

    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_BLK, HIGH);

    Serial.begin(9600);



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



    setupWifi(); // concrens wifi setup
    client.setServer(mqtt_server, 1883);  //Sets the MQTT server details.  
    client.setCallback(callback); //Sets the message callback function for MQTT

    //Serial.setTextColor(YELLOW);  //Set the font color to yellow. 
    //Serial.setTextSize(1);  //Set the font size to 2.  
    Serial.println("PME4.0 - Machine State -DEBUG"); //Print a string on the screen.  
    delay(1000);
    //Serial.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    //Serial.setTextColor(WHITE);  //Set the font color to yellow. 






    //Initialize the (dummy) input device driver in LGVL (lib/lv_port_indev_init)
    lv_port_indev_init();


    //**** Declare all graphics *****/

 //   lv_example_roller_3();

    construct_buttons();

    //lv_img_logo();

}


/////////////////////////
//       LOOP          //
/////////////////////////


void loop()
{
    //MQTT communication
    if (!client.connected()) {
        reConnect();
    }
    client.loop();  //MQTT : This function is called periodically to allow clients to process incoming messages and maintain connections to the server.

    unsigned long now = millis(); //Obtain the host startup duration.  
    if (now - lastMsg > 2000) {
        lastMsg = now;
        ++value;
        //snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value); //Format to the specified string and store it in MSG.  
        //msg = String(t).c_str();
        //M5.Lcd.print("Publish message: ");
        //M5.Lcd.println(String(t).c_str());
        client.publish("M5Stack/temp", String(t).c_str());  //Publishes a message to the specified topic.  
        Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
        int i = 0;
        while(Wire.available())    // slave may send less than requested
        {
            char c = Wire.read();    // receive a byte as character
            data[i] = c;
            i = i + 1 ; 
        }

    }

    Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
    int i = 0;
    while(Wire.available())    // slave may send less than requested
    {
        char c = Wire.read();    // receive a byte as character
        data[i] = c;
        i = i + 1 ; 
    }

    int vert = data[0] - '0'; // method to convert char in int
    int orange = data[1] - '0';
    int rouge = data[2] - '0';

    //M5.Lcd.setTextSize(2);  //Set the font size to 2. 
    int hauteur_txt = 110;
    
    if (vert == 1 && orange == 0 && rouge == 0 ){
        //textColor=BLACK;
        /*
        M5.Lcd.setTextColor(textColor,GREEN); //Set the foreground color of the text to textColor and the background color to BLACK. 
        M5.Lcd.fillScreen( GREEN ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(30,hauteur_txt);
        M5.Lcd.print("MACHINE EN PRODUCTION");
        */
    }
    else if (orange == 1 && vert == 0 && rouge == 0){
        //textColor=BLACK;
        /*
        M5.Lcd.setTextColor(textColor,YELLOW); //Set the foreground color of the text to textColor and the background color to BLACK. 
        M5.Lcd.fillScreen( YELLOW ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(60,hauteur_txt);
        M5.Lcd.print("MACHINE EN PAUSE");
        */
    }
    else if (rouge == 1 && vert == 0 && orange == 0){
        //textColor=RED;
        /*
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextColor(textColor,BLACK); //Set the foreground color of the text to textColor and the background color to BLACK. 
        M5.Lcd.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(110,hauteur_txt);
        M5.Lcd.print("ARRET");
        */
    }
    else if (vert == 1 && rouge == 1 && orange ==0 ){
        //textColor=BLACK;
        /*
        M5.Lcd.setTextColor(textColor,YELLOW); //Set the foreground color of the text to textColor and the background color to BLACK.
        M5.Lcd.fillScreen( YELLOW ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(60,hauteur_txt); 
        M5.Lcd.print("MACHINE EN PAUSE");
        */
    }
    else if (vert == 0 && rouge == 0 && orange == 0){
        //textColor=WHITE;      
        /*
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextColor(textColor,BLACK); //Set the foreground color of the text to textColor and the background color to BLACK. 
        M5.Lcd.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(60,hauteur_txt);
        M5.Lcd.print("NO SIGNAL");
        */
    }

    else {
        //textColor=WHITE;
        /*
        M5.Lcd.setTextSize(4);
        M5.Lcd.setTextColor(textColor,RED); //Set the foreground color of the text to textColor and the background color to RED. 
        M5.Lcd.fillScreen( RED ); //Make the screen full of black (equivalent to clear() to clear the screen). 
        M5.Lcd.setCursor(100,hauteur_txt);
        M5.Lcd.print("ERREUR");
        */
    }

    //M5.Lcd.fillScreen(BLACK);
    //M5.Lcd.setCursor(0,0);

    lv_timer_handler(); /* let the GUI do its work */
    //delay(200); /* only for debgging */
}
