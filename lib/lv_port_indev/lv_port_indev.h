/**
 * @file lv_port_indev.h
 *
 */

 /*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H


/*********************
 *      INCLUDES
 *********************/

#include "FT6236.h"
#include "lvgl.h"
#include <Arduino.h>
#include "debug.h"

/*********************
 *      DEFINES
 *********************/


#define FT6236_TOUCH //Capacitive screen driver
#define I2C_TOUCH_SCL 39
#define I2C_TOUCH_SDA 38
#define LCD_HEIGHT 240



/**********************
 *  STATIC VARIABLES
 **********************/





/**********************
 *      TYPEDEFS
 **********************/




/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_port_indev_init(void);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void touchpad_get_xy(lv_coord_t * x, lv_coord_t * y);






/**********************
 *      MACROS
 **********************/



#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/