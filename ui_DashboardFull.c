// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 9.1.0
// Project name: Project

#include "ui.h"

void ui_DashboardFull_screen_init(void)
{
    ui_DashboardFull = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_DashboardFull, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DashboardFull_VolumeArc = lv_arc_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_VolumeArc, 280);
    lv_obj_set_height(ui_DashboardFull_VolumeArc, 280);
    lv_obj_set_x(ui_DashboardFull_VolumeArc, -2);
    lv_obj_set_y(ui_DashboardFull_VolumeArc, 10);
    lv_obj_set_align(ui_DashboardFull_VolumeArc, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DashboardFull_VolumeArc, LV_OBJ_FLAG_CHECKABLE);     /// Flags
    lv_obj_remove_flag(ui_DashboardFull_VolumeArc, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_arc_set_value(ui_DashboardFull_VolumeArc, 0);


    ui_DashboardFull_StatusLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_StatusLabel, lv_pct(40));
    lv_obj_set_height(ui_DashboardFull_StatusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_StatusLabel, -2);
    lv_obj_set_y(ui_DashboardFull_StatusLabel, -50);
    lv_obj_set_align(ui_DashboardFull_StatusLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DashboardFull_StatusLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DashboardFull_StatusLabel, "Ready");
    lv_obj_set_style_text_color(ui_DashboardFull_StatusLabel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DashboardFull_StatusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DashboardFull_StatusLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DashboardFull_StatusLabel, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DashboardFull_VolumeLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_VolumeLabel, lv_pct(50));
    lv_obj_set_height(ui_DashboardFull_VolumeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_VolumeLabel, -2);
    lv_obj_set_y(ui_DashboardFull_VolumeLabel, 15);
    lv_obj_set_align(ui_DashboardFull_VolumeLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DashboardFull_VolumeLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DashboardFull_VolumeLabel, "600");
    lv_obj_set_style_text_align(ui_DashboardFull_VolumeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DashboardFull_VolumeLabel, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DashboardFull_UnitLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_UnitLabel, lv_pct(40));
    lv_obj_set_height(ui_DashboardFull_UnitLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_UnitLabel, -2);
    lv_obj_set_y(ui_DashboardFull_UnitLabel, 80);
    lv_obj_set_align(ui_DashboardFull_UnitLabel, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_DashboardFull_UnitLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_DashboardFull_UnitLabel, "mL");
    lv_obj_set_style_text_align(ui_DashboardFull_UnitLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DashboardFull_UnitLabel, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DashboardFull_ProgressLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_ProgressLabel, lv_pct(40));
    lv_obj_set_height(ui_DashboardFull_ProgressLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_ProgressLabel, -130);
    lv_obj_set_y(ui_DashboardFull_ProgressLabel, -140);
    lv_obj_set_align(ui_DashboardFull_ProgressLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DashboardFull_ProgressLabel, "Progress : 0 %");

    ui_DashboardFull_TakeTLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_TakeTLabel, lv_pct(32));
    lv_obj_set_height(ui_DashboardFull_TakeTLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_TakeTLabel, -150);
    lv_obj_set_y(ui_DashboardFull_TakeTLabel, -115);
    lv_obj_set_align(ui_DashboardFull_TakeTLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DashboardFull_TakeTLabel, "Take time : 0 s");

    ui_DashboardFull_TimeLabel = lv_label_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_TimeLabel, lv_pct(32));
    lv_obj_set_height(ui_DashboardFull_TimeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DashboardFull_TimeLabel, -150);
    lv_obj_set_y(ui_DashboardFull_TimeLabel, -90);
    lv_obj_set_align(ui_DashboardFull_TimeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DashboardFull_TimeLabel, "Time : 0 s");

    ui_DashboardFull_BackBtn = lv_button_create(ui_DashboardFull);
    lv_obj_set_width(ui_DashboardFull_BackBtn, 100);
    lv_obj_set_height(ui_DashboardFull_BackBtn, 30);
    lv_obj_set_x(ui_DashboardFull_BackBtn, 173);
    lv_obj_set_y(ui_DashboardFull_BackBtn, 133);
    lv_obj_set_align(ui_DashboardFull_BackBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DashboardFull_BackBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_DashboardFull_BackBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_DashboardFull_BackLabel = lv_label_create(ui_DashboardFull_BackBtn);
    lv_obj_set_width(ui_DashboardFull_BackLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DashboardFull_BackLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_DashboardFull_BackLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DashboardFull_BackLabel, "Back");

    lv_obj_add_event_cb(ui_DashboardFull_BackBtn, ui_event_DashboardFull_BackBtn, LV_EVENT_ALL, NULL);

}
