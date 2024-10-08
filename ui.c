// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 9.1.0
// Project name: Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Loadding
void ui_Loadding_screen_init(void);
lv_obj_t * ui_Loadding;
lv_obj_t * ui_Loadding_Title;
lv_obj_t * ui_Loadding_LoadContainer;
lv_obj_t * ui_Loadding_LoadText;
lv_obj_t * ui_Loadding_LoadPercent;
lv_obj_t * ui_Loadding_LoadBar;


// SCREEN: ui_Main
void ui_Main_screen_init(void);
lv_obj_t * ui_Main;
lv_obj_t * ui_Main_MainTabView;
lv_obj_t * ui_Main_Dashboard;
lv_obj_t * ui_Main_DashPanel;
void ui_event_Main_ZoomBtn(lv_event_t * e);
lv_obj_t * ui_Main_ZoomBtn;
lv_obj_t * ui_Main_Label9;
void ui_event_Main_HistoryBtn(lv_event_t * e);
lv_obj_t * ui_Main_HistoryBtn;
lv_obj_t * ui_Main_Label13;
lv_obj_t * ui_Main_VolumeArc;
lv_obj_t * ui_Main_StatusLabel;
lv_obj_t * ui_Main_VolumeLabel;
lv_obj_t * ui_Main_UnitLabel;
lv_obj_t * ui_Main_ProgressLabel;
lv_obj_t * ui_Main_TakeTLabel;
lv_obj_t * ui_Main_TimeLabel;
lv_obj_t * ui_Main_DetailLabel;
lv_obj_t * ui_Main_Setting;
lv_obj_t * ui_Main_SettingPanel;
lv_obj_t * ui_Main_RightContainer;
lv_obj_t * ui_Main_VolContainer;
lv_obj_t * ui_Main_SVLabel;
lv_obj_t * ui_Main_SVSpinbox;
lv_obj_t * ui_Main_SVUnit;
lv_obj_t * ui_Main_FlowContainer;
lv_obj_t * ui_Main_SFLabel;
lv_obj_t * ui_Main_SFSpinbox;
lv_obj_t * ui_Main_SFUnit;
lv_obj_t * ui_Main_AlarmContainer;
lv_obj_t * ui_Main_WALabel;
void ui_event_Main_WASwitch(lv_event_t * e);
lv_obj_t * ui_Main_WASwitch;
lv_obj_t * ui_Main_LeftContainer;
lv_obj_t * ui_Main_Container2;
lv_obj_t * ui_Main_Label8;
void ui_event_Main_Slider1(lv_event_t * e);
lv_obj_t * ui_Main_Slider1;
lv_obj_t * ui_Main_SystemContainer;
void ui_event_Main_ResetBtn(lv_event_t * e);
lv_obj_t * ui_Main_ResetBtn;
lv_obj_t * ui_Main_ResetLabel;
void ui_event_Main_RebootBtn(lv_event_t * e);
lv_obj_t * ui_Main_RebootBtn;
lv_obj_t * ui_Main_RebootLabel;
lv_obj_t * ui_Main_Info;
lv_obj_t * ui_Main_InfoPanel;
lv_obj_t * ui_Main_InfoText;


// SCREEN: ui_DashboardFull
void ui_DashboardFull_screen_init(void);
lv_obj_t * ui_DashboardFull;
lv_obj_t * ui_DashboardFull_VolumeArc;
lv_obj_t * ui_DashboardFull_StatusLabel;
lv_obj_t * ui_DashboardFull_VolumeLabel;
lv_obj_t * ui_DashboardFull_UnitLabel;
lv_obj_t * ui_DashboardFull_ProgressLabel;
lv_obj_t * ui_DashboardFull_TakeTLabel;
lv_obj_t * ui_DashboardFull_TimeLabel;
void ui_event_DashboardFull_BackBtn(lv_event_t * e);
lv_obj_t * ui_DashboardFull_BackBtn;
lv_obj_t * ui_DashboardFull_BackLabel;


// SCREEN: ui_History
void ui_History_screen_init(void);
lv_obj_t * ui_History;
lv_obj_t * ui_History_HisPanel;
void ui_event_History_BackBtn(lv_event_t * e);
lv_obj_t * ui_History_BackBtn;
lv_obj_t * ui_History_BackLabel;
lv_obj_t * ui_History_Title;
lv_obj_t * ui_History_HisTitle;
lv_obj_t * ui_History_HisData;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Main_ZoomBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        _ui_screen_change(&ui_DashboardFull, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_DashboardFull_screen_init);
        _ui_screen_delete(&ui_Main);
    }
}
void ui_event_Main_HistoryBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        _ui_screen_change(&ui_History, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_History_screen_init);
        _ui_screen_delete(&ui_Main);
    }
}
void ui_event_Main_WASwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        WAEvent(e);
    }
}
void ui_event_Main_Slider1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        SetOffset(e);
    }
}
void ui_event_Main_ResetBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        ResetSystem(e);
    }
}
void ui_event_Main_RebootBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        RebootSystem(e);
    }
}
void ui_event_DashboardFull_BackBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        _ui_screen_change(&ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Main_screen_init);
        _ui_screen_delete(&ui_DashboardFull);
    }
}
void ui_event_History_BackBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        _ui_screen_change(&ui_Main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Main_screen_init);
        _ui_screen_delete(&ui_History);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_display_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Loadding_screen_init();
    ui_Main_screen_init();
    ui_DashboardFull_screen_init();
    ui_History_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Loadding);
}
