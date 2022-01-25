/**
 * @file lv_port_indev.cpp
 *
 */

 /*set this value to "1" to enable content*/

#if 1


#include "lv_port_indev.h"



#define get_pos ft6236_pos

/* Driver Hardware FT6236 */
const int i2c_touch_addr = TOUCH_I2C_ADD;


lv_indev_t * indev_touchpad;
static lv_indev_data_t data;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find implementation of input device Touchpad supported by LittelvGL:
     *   
     *
     *  The `..._read()` is shaped according to hardware
     */

    static lv_indev_drv_t indev_drv;



    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
    
    /*Initialize  touchpad */
    touchpad_init();

}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/*Initialize touchpad*/
static void touchpad_init(void)
{
    /*Your code comes here*/
    //I2C init
    Wire.begin(I2C_TOUCH_SDA, I2C_TOUCH_SCL);
    byte error, address;

    Wire.beginTransmission(i2c_touch_addr);
    error = Wire.endTransmission();

    if (error == 0)
    {
        DPRINT("I2C device found at address 0x");
        DPRINT(i2c_touch_addr, HEX);
        DPRINTLN("  !");
    }
    else if (error == 4)
    {
        DPRINT("Unknown error at address 0x");
        DPRINTLN(i2c_touch_addr, HEX);
    }

}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    //DPRINTLN("touchpad_read() called");

    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;


    /*Save the pressed coordinates and the state*/
    if (touched())
    {

        last_x = getTouchPointY();
        last_y = LCD_HEIGHT - getTouchPointX();

        data->state = LV_INDEV_STATE_PR;

    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
/*
        DPRINT("Touch coord. | x:");
        DPRINT(data->point.x);
        DPRINT(", y : ");
        DPRINT(data->point.y);
        DPRINTLN();
*/
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif