#include <Wire.h>

#define TOUCH_I2C_ADD 0x38 // i2c address of touchscreen 
#define FT6236_REG_NUMTOUCHES 0x02 // Number of touch points
#define TOUCH_REG_XL 0x04 
#define TOUCH_REG_XH 0x03
#define TOUCH_REG_YL 0x06
#define TOUCH_REG_YH 0x05

int readTouchReg(int reg);

int getTouchPointX();

int getTouchPointY();

int ft6236_pos(int pos[2]);

uint8_t touched();

uint8_t calibrate();