#ifndef CONFIG_H
#define CONFIG_H
#include "ui.h"
/**************** Macro definition (Constane) ****************/
#define PILOT 13 // LOW - GREEN | HIGH - RED    (IN1)
#define PUMP  4  // LOW - ON    | HIGH - OFF    (IN2)
#define PSW   27
#define LSEN  33
/*Set to your screen resolution*/
#define TFT_HOR_RES   480
#define TFT_VER_RES   320

/* KeyPad */
#define KEY_I2CADDR   0x20
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS] = {3, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
/**************** Variable ****************/
uint32_t draw_buf[DRAW_BUF_SIZE / 4];
lv_obj_t * act_scr;
int act_tab;
float VolDataSet[6] = {0.6, 1.0, 1.25, 1.5, 1.95, 10.0}; 
float FlowRate; // (L/SEC) <FR>
float PrecentOffset; // <PO>
float Vols; // 0.6
float VolCustom = 0.6;
bool updateVol = false;
boolean LastWaterState = false;
boolean WaterState = false;  // true - No water | false - Water ready
boolean PumpStart = false;
boolean PauseState = false;
boolean StatusLabelUpdate = false;
boolean SetupStatus = false;
boolean KeyTimeout = false; // on-off Check TimeOut Keypad
int KeyTime = 1000;
int PauseCount = 0;
int RunCount = 0;
int WCSum = 0;
int WCCount = 0;
int WCVal = 0;
int WCDelay = 100;
int LoaddingDelay = 2000;
char KeyStr[10];
int Kindex = 0;
unsigned long LoaddingPageTime = 0;
unsigned long WCLastTime = 0;
unsigned long PumpLastTime = 0;
unsigned long PauseTime = 0;
unsigned long TimeUse = 0;
unsigned long SaveTimeUse = 0;
unsigned long KeypadLastTime = 0;
unsigned long last = 0;
#endif
