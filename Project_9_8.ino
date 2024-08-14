#include <esp_task_wdt.h>
#include <ButtonDebounce.h>
#include <lvgl.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <String.h>
#include "Config.h"
#include "ui.h"
#include <Preferences.h>

/*** initial instance ***/
TFT_eSPI tft = TFT_eSPI(TFT_HOR_RES, TFT_VER_RES);
Keypad_I2C keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEY_I2CADDR, PCF8574 );
ButtonDebounce button(PSW, 100); // Wait 100 mS
Preferences preferences;
esp_task_wdt_config_t wdtconfig = {
  .timeout_ms = 3000,
  .trigger_panic = true,
};
void setup() {
  Serial.begin(115200);
  Wire.begin();
  keypad.begin(makeKeymap(keys));
  preferences.begin("app", false);
  pinMode(PUMP,  OUTPUT);
  digitalWrite(PUMP, HIGH);
  pinMode(PILOT, OUTPUT);
  pinMode(LSEN, INPUT);

  lv_init();
  lv_tick_set_cb(millis);
#if LV_USE_LOG != 0
  lv_log_register_print_cb( my_print );
#endif
  tft.begin();          /* TFT init */
  tft.setRotation( 3 ); /* Landscape orientation, flipped */
  uint16_t calData[5] = { 431, 3274, 499, 3044, 1 };
  tft.setTouch(calData);
  lv_display_t * disp;
  disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));

  /*Initialize the (dummy) input device driver*/
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
  lv_indev_set_read_cb(indev, my_touchpad_read);
  ui_init();

  button.setCallback(PSWEvent);
  Serial.println("Configuring WDT...");
  esp_task_wdt_init(&wdtconfig); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
  LoadConf();   // Load Cofigulation Data
  float t = GetTime(FlowRate, Vols);
  TimeUse = t + (t * PrecentOffset / 100);
  SaveTimeUse = TimeUse;
  LoaddingPageTime = millis();
  last = millis();
}

void loop() {
  // resetting WDT every 2s
  if (millis() - last >= 2000) {
    esp_task_wdt_reset();
    last = millis();
  }
  lv_task_handler();
  act_scr = lv_scr_act();
  act_tab = lv_tabview_get_tab_active(ui_Main_MainTabView);

  if (!SetupStatus && millis() - LoaddingPageTime >= LoaddingDelay) {
    lv_bar_set_value(ui_Loadding_LoadBar, 100, LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Loadding_LoadPercent, "%d %%", (int)lv_bar_get_value(ui_Loadding_LoadBar));
    _ui_screen_change(&ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 200, &ui_Main_screen_init);
    _ui_screen_delete(&ui_Loadding);
    digitalWrite(PILOT, LOW);
    SetupStatus = true;
  }

  /* Run After Setup Condition */
  if (SetupStatus) {
    KeyProcess();
    if (updateVol) {
      float t = GetTime(FlowRate, Vols);
      TimeUse = t + (t * PrecentOffset / 100);
      SaveTimeUse = TimeUse;
      UpdateRing(0);
      SaveConf();
      updateVol = false;
    }
    /*** Level Check ***/
    if (millis() - WCLastTime >= WCDelay) {
      WCSum += analogRead(LSEN);
      WCCount++;
      if (WCCount == 10) {
        WCVal = WCSum / 10;
        WCCount = 0;
        WCSum = 0;
      }
      WaterState = bool(WCVal);
      // ReConfig WaterState if WAStatus off
      if (!WAStatus) {
        WaterState = false;
      }
      if (ESPRestart) {
        ESPRestart = false;
        ESP.restart();
      }
      if (ResetConf) {
        preferences.clear();
        LoadConf();
        updateVol = true;
      }

      if (WaterState != LastWaterState || StatusLabelUpdate) {
        digitalWrite(PILOT, WaterState);
        if (WaterState) {
          lv_obj_set_style_text_color(ui_Main_StatusLabel, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_label_set_text(ui_Main_StatusLabel, "Water is not ready");
          lv_obj_set_style_text_color(ui_DashboardFull_StatusLabel, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_label_set_text(ui_DashboardFull_StatusLabel, "Water is not ready");
        } else {
          lv_obj_set_style_text_color(ui_Main_StatusLabel, lv_color_hex(0x00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_label_set_text(ui_Main_StatusLabel, "Ready");
          lv_obj_set_style_text_color(ui_DashboardFull_StatusLabel, lv_color_hex(0x00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
          lv_label_set_text(ui_DashboardFull_StatusLabel, "Ready");
        }
        StatusLabelUpdate = false;
      }
      LastWaterState = WaterState;
      WCLastTime = millis();
    }
    // กรณีน้ำหมดระหว่างที่เครื่องทำงานให้หยุดและเริ่มต้นใหม่
    if (PumpStart && WaterState) {
      digitalWrite(PUMP, HIGH);
      PauseTime = 0;
      UpdateRing(0);
      TimeUse = SaveTimeUse;
      PumpStart = false;
      PauseState = false;
    }
    button.update();
  }
  if (PumpStart) {
    UpdateRing(1); // running update
  }
  /*** Timer-Counter ***/
  if (PumpStart && millis() - PumpLastTime >= TimeUse) {
    digitalWrite(PUMP, HIGH);
    float t = millis() - PumpLastTime + PauseTime;
    float v = GetVolume(FlowRate, t) * 1000;
    PauseTime = 0;
    TimeUse = SaveTimeUse;
    PumpStart = false;
    RunCount++;
    UpdateRing(0); // set 0 reset ring
  }
}
void PSWEvent(const int state) {
  if (!state) {
    // Start Condition
    if (!PauseState && !PumpStart && !WaterState) {
      digitalWrite(PUMP, LOW);
      PumpStart = true;
      PumpLastTime = millis();
      lv_obj_set_style_text_color(ui_Main_StatusLabel, lv_color_hex(0x0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_label_set_text(ui_Main_StatusLabel, "Running");
    } else if (!PauseState && PumpStart) {
      // PauseState
      digitalWrite(PUMP, HIGH);
      PauseTime += millis() - PumpLastTime;
      TimeUse = TimeUse - (millis() - PumpLastTime);
      PumpStart = false;
      PauseState = true;
      PauseCount++;
      lv_obj_set_style_text_color(ui_Main_StatusLabel, lv_color_hex(0x0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_label_set_text(ui_Main_StatusLabel, "Pause");
    } else if (PauseState && !PumpStart && !WaterState) {
      // UnPauseState
      digitalWrite(PUMP, LOW);
      PumpStart = true;
      PauseState = false;
      PumpLastTime = millis();
      lv_obj_set_style_text_color(ui_Main_StatusLabel, lv_color_hex(0x0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_label_set_text(ui_Main_StatusLabel, "Running");
    }
  }
}

void KeyProcess() {
  char key = keypad.getKey();
  if (key) {
    KeyStr[Kindex] = key;
    Kindex++;
    KeyTimeout = true;
    KeypadLastTime = millis();
  }
  if(KeyTimeout && (millis() - KeypadLastTime >= KeyTime)){
    Kindex = 0;
    KeyTimeout = false;
  }
  if (Kindex == 2) {
    if (act_tab == 0) {
      switch (KeyStr[0]) {
        case 'D':
          switch (KeyStr[1]) {
            case '0':
              Vols = VolCustom;
            case '1':
              Vols = VolDataSet[0];
              updateVol = true;
              break;
            case '2':
              Vols = VolDataSet[1];
              updateVol = true;
              break;
            case '3':
              Vols = VolDataSet[2];
              updateVol = true;
              break;
            case '4':
              Vols = VolDataSet[3];
              updateVol = true;
              break;
            case '5':
              Vols = VolDataSet[4];
              updateVol = true;
              break;
            case '6':
              Vols = VolDataSet[5];
              updateVol = true;
              break;
          }
          break;
        case '*':
          if (KeyStr[1] == 'C') {
            PauseTime = 0;
            TimeUse = SaveTimeUse;
            PumpStart = false;
            PauseState = false;
            UpdateRing(0);
          }
          break;
      }
    }
    Kindex = 0;
  }
}
float GetTime(float FlowRate, float Volume) {
  // Flowrate base L/sec
  float time = Volume / FlowRate;
  return time * 1000; // millissec
}

float GetVolume(float FlowRate, int Time) {
  return FlowRate * Time / 1000.0;
}
void LoadConf() {
  FlowRate = preferences.getFloat("FR", 0.083); // L/SEC
  WAStatus = preferences.getBool("WAS", true); // true
  PrecentOffset = preferences.getInt("PO", 0); // 0
  Vols = preferences.getFloat("Vol", 0.6); // L
}
void SaveConf() {
  preferences.putFloat("FR", FlowRate); // L/SEC
  preferences.putBool("WAS", WAStatus); // true
  preferences.putInt("PO", PrecentOffset); // 0
  preferences.putFloat("Vol", Vols); // L
}
void UpdateRing(int Mode) {
  char Volbuf[6];
  bool UseUnit = false; // false -> mL / true -> L
  if (Vols < 1) {
    UseUnit = false;
    sprintf(Volbuf, "%.1lf", Vols * 1000);
  } else {
    UseUnit = true;
    sprintf(Volbuf, "%.2lf", Vols);
  }
  switch (Mode) {
    case 0:
      StatusLabelUpdate = true;
      char bufTt[20];
      sprintf(bufTt, "Take time : %.1f s", SaveTimeUse / 1000.0);
      lv_label_set_text(ui_Main_TakeTLabel, bufTt);
      lv_label_set_text(ui_DashboardFull_TakeTLabel, bufTt);
      lv_arc_set_value(ui_Main_VolumeArc, 0);
      lv_label_set_text(ui_Main_VolumeLabel, Volbuf);
      lv_label_set_text(ui_Main_ProgressLabel, "Progress : 0 %%");
      lv_arc_set_value(ui_DashboardFull_VolumeArc, 0);
      lv_label_set_text(ui_DashboardFull_VolumeLabel, Volbuf);
      lv_label_set_text(ui_DashboardFull_ProgressLabel, "Progress : 0 %%");
      lv_label_set_text(ui_Main_UnitLabel, (UseUnit) ? "L" : "mL");
      lv_label_set_text(ui_DashboardFull_UnitLabel, (UseUnit) ? "L" : "mL");
      break;
    case 1:
      char VolNbuf[6];
      char bufPg[20];
      unsigned long TimeNow = millis() - PumpLastTime + PauseTime;
      float PercentTime = (TimeNow / (float)SaveTimeUse) * 100;
      float VolNow = GetVolume(FlowRate, TimeNow);
      if(VolNow < 1){
        UseUnit = false;
        sprintf(VolNbuf, "%.1lf", VolNow * 1000);
      }else {
        UseUnit = true;
        sprintf(VolNbuf, "%.2lf", VolNow);
      }
      sprintf(bufPg, "Progress : %.0lf %%", PercentTime);
      lv_arc_set_value(ui_Main_VolumeArc, int(PercentTime));
      lv_label_set_text(ui_Main_VolumeLabel, VolNbuf);
      lv_label_set_text(ui_Main_ProgressLabel, bufPg);
      lv_arc_set_value(ui_DashboardFull_VolumeArc, int(PercentTime));
      lv_label_set_text(ui_DashboardFull_VolumeLabel, VolNbuf);
      lv_label_set_text(ui_DashboardFull_ProgressLabel, bufPg);
      lv_label_set_text(ui_Main_UnitLabel, (UseUnit) ? "L" : "mL");
      lv_label_set_text(ui_DashboardFull_UnitLabel, (UseUnit) ? "L" : "mL");
      break;
  }
}
#if LV_USE_LOG != 0
void my_print( lv_log_level_t level, const char * buf )
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{
  /*Copy `px map` to the `area`*/

  /*For example ("my_..." functions needs to be implemented by you)
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    my_set_window(area->x1, area->y1, w, h);
    my_draw_bitmaps(px_map, w * h);
  */

  /*Call it to tell LVGL you are ready*/
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
{
  uint16_t touchX = 0, touchY = 0;
  bool touched = tft.getTouch( &touchX, &touchY, 600 );
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;
    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}
