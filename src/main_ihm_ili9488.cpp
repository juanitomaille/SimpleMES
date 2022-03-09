#define DEBUG  // uncomment this line for debug


/********************************
*                               *
*        INCLUDES               *
*                               *
*******************************/

#include "debug.h"


#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>


#include "lvgl.h"
#include "lv_port_indev.h" /* input Driver for lvgl */

/* UI */
#include "DisplaySetup.h"
#include "status_messages.h"



/********************************
*                               *
*        DEFINES                *
*                               *
*******************************/


#define LN  1


#define I2C_SCL 39
#define I2C_SDA 38

#define MSG_BUFFER_SIZE	(50)


#define CUSTOMER "USIDUC"

/********************************
*                               *
*        VARIABLES              *
*                               *
*******************************/


// Configure the name and password of the connected wifi and your MQTT Serve host.
const char* ssid = "FACTORYBOX";
const char* password = "Jm9r5F3W";

unsigned long lastMsg = 0;

char msg[MSG_BUFFER_SIZE];
int value = 0;
char data[3];
char code[3]; // Color of column : 000 = no color; 100 = green, 010 = orange, 001 = red


//Change to your screen resolution
static const uint32_t screenWidth  = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];


// customer + machine

const char* customer = "USIDUC";
String machine = "QUASER";


const char* state; // statut machine



/********************************
*                               *
*        Prototypes             *
*                               *
*******************************/


void setupWifi();
void SendDatabase(String client, String machine, String status) ;



/********************************
*                               *
*        declarations           *
*                               *
*******************************/









/////////////////////////
//   COMMUNICATIONS    //
/////////////////////////

WiFiClient espClient;
//PubSubClient client(espClient);


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
  message_txt_green ("Success");

}


void SendDatabase(String client, String machine, String status) {
        // start connexion to influDB
        HTTPClient http;
        http.begin("http://factorybox.local:8086/write?db=" + client);
        http.addHeader("Content-Type", "--data-binary");

        String postData = machine + " state=\"" + status + "\"";
        int httpResponseCode = http.POST(postData);
        
        if (httpResponseCode != 204) {
            DPRINT("Error code: ");
            DPRINTLN(httpResponseCode);
        }

        http.end(); //end of sending influDB DATA 
}




/////////////////////////
//       DISPLAY       //
/////////////////////////

/*

static void stopped_button_handler(lv_obj_t * obj, lv_event_t event)
{
        if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Toggled\n");
    }
}

void lv_error_btn_1(void)
{
    lv_obj_t * label;


    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(btn2, stopped_button_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 40);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "1");
}
*/


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

    DPRINTLN("PME4.0 - Machine State -DEBUG"); //Print a string on the screen.  
    delay(1000);


    //Initialize the (dummy) input device driver in LGVL (lib/lv_port_indev_init)
    lv_port_indev_init();



}


/////////////////////////
//       LOOP          //
/////////////////////////

int last_vert = 0;
int last_orange = 0;
int last_rouge = 0;

int vert;
int orange; 
int rouge;


void loop()
{

    Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
    int i = 0;
    while(Wire.available())    // slave may send less than requested
    {
        char c = Wire.read();    // receive a byte as character
        data[i] = c;
        i = i + 1 ;
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
            state = "prod";
            
        }
        else if (orange == 1 && vert == 0 && rouge == 0)
        {
            DPRINTLN("SimpleMES | Machine en arrêt");
            Machine_stopped_message();
            state = "arret";   
        }
        else if (rouge == 1 && vert == 0 && orange == 0)
        {
            DPRINTLN("SimpleMES | Machine disponible");
            Machine_available_message();
            state = "dispo";
        }
        else if (vert == 1 && rouge == 1 && orange ==0 )
        {
            DPRINTLN("SimpleMES | Machine en arrêt");
            Machine_stopped_message();

            state = "arret";
        }
        else if (vert == 0 && rouge == 0 && orange == 0)
        {
            DPRINTLN("SimpleMES | Pas de signal");
            No_machine_message(); // pas de signal
            state = "nosignal";
        }
        else 
        {
            DPRINTLN("SimpleMES | Erreur !");
            Machine_error_message();
            state = "erreur";
        }

         // start connexion to influDB
        HTTPClient http;
        http.begin("http://factorybox:8086/api/v2/write?org=USIDUC&bucket=SimpleMES&precision=ns");
        http.addHeader("Authorization", "IiVS3QdWC7tmewfrE4NUdfL8vpIRcOmJgeJI2D-YF9l7KO78e6fPR9kvo1gWOFvSBs5IK-hL117j5O2zIyjP9w==");
        http.addHeader("Accept:", "application/json");
        http.addHeader("Content-Type", "--data-binary");

        String postData = machine + " state=\"" + state + "\"";
        int httpResponseCode = http.POST(postData);
        
        if (httpResponseCode != 204) {
            DPRINT("Error code: ");
            DPRINTLN(httpResponseCode);
        }

        http.end(); //end of sending influDB DATA 
        
    }

    last_vert = vert;
    last_orange = orange;
    last_rouge = rouge;

    lv_timer_handler(); /* let the GUI do its work */
}
