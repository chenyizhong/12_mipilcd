#include "myUI.h"

// 最简单的 UI 界面：只显示一个标签
void my_simple_ui(void)
{
    // 【重要】使用 esp_lvgl_adapter 必须加锁！
    if (esp_lv_adapter_lock(portMAX_DELAY) == ESP_OK) {

        // 1. 创建一个 Label（标签）
        lv_obj_t *label = lv_label_create(lv_scr_act());

        // 2. 设置文字
        lv_label_set_text(label, "Hello LVGL!\nI'm Running!");

        // 3. 让文字居中
        lv_obj_center(label);

        // 可选：设置字体大小
        lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);

        // 解锁
        esp_lv_adapter_unlock();
    }
}

// 主入口（你可以直接把这段放到 app_main 最后）
void simple_ui_demo(void)
{
    // 等待 esp_lvgl_adapter 启动完成
    vTaskDelay(pdMS_TO_TICKS(200));
    // 加载我们的极简界面
    my_simple_ui();
}