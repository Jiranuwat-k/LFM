// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 9.1.0
// Project name: Project

#include "ui.h"

void ui_History_screen_init(void)
{
    ui_History = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_History, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_History, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_History, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_left(ui_History, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_History, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_History, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_History, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_History_HisPanel = lv_obj_create(ui_History);
    lv_obj_set_width(ui_History_HisPanel, lv_pct(100));
    lv_obj_set_height(ui_History_HisPanel, lv_pct(100));
    lv_obj_set_x(ui_History_HisPanel, -124);
    lv_obj_set_y(ui_History_HisPanel, -30);
    lv_obj_set_align(ui_History_HisPanel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_History_HisPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_History_BackBtn = lv_button_create(ui_History_HisPanel);
    lv_obj_set_width(ui_History_BackBtn, 71);
    lv_obj_set_height(ui_History_BackBtn, 32);
    lv_obj_set_x(ui_History_BackBtn, -185);
    lv_obj_set_y(ui_History_BackBtn, -123);
    lv_obj_set_align(ui_History_BackBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_History_BackBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_History_BackBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_History_BackLabel = lv_label_create(ui_History_BackBtn);
    lv_obj_set_width(ui_History_BackLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_History_BackLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_History_BackLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_History_BackLabel, "Back");

    ui_History_Title = lv_label_create(ui_History_HisPanel);
    lv_obj_set_width(ui_History_Title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_History_Title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_History_Title, 181);
    lv_obj_set_y(ui_History_Title, -128);
    lv_obj_set_align(ui_History_Title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_History_Title, "History");
    lv_obj_set_style_text_font(ui_History_Title, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_History_HisTitle = lv_label_create(ui_History_HisPanel);
    lv_obj_set_width(ui_History_HisTitle, lv_pct(100));
    lv_obj_set_height(ui_History_HisTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_History_HisTitle, 0);
    lv_obj_set_y(ui_History_HisTitle, -80);
    lv_obj_set_align(ui_History_HisTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_History_HisTitle, "No.             Volume            Unit");

    ui_History_HisData = lv_label_create(ui_History_HisPanel);
    lv_obj_set_width(ui_History_HisData, lv_pct(100));
    lv_obj_set_height(ui_History_HisData, lv_pct(70));
    lv_obj_set_x(ui_History_HisData, 0);
    lv_obj_set_y(ui_History_HisData, 30);
    lv_obj_set_align(ui_History_HisData, LV_ALIGN_CENTER);
    lv_label_set_text(ui_History_HisData, "1                  600                   mL");

    lv_obj_add_event_cb(ui_History_BackBtn, ui_event_History_BackBtn, LV_EVENT_ALL, NULL);

}
