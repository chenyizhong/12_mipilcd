#include "myLvAdapter.h"

void my_lv_adapter_init()
{
    esp_lv_adapter_config_t adapter_cfg = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    adapter_cfg.task_stack_size = 32 * 1024; // 增大栈至 32KB
    adapter_cfg.stack_in_psram = true;       // 将任务栈放入 PSRAM
    adapter_cfg.task_core_id = 1;            // 固定在核心 1 运行（视具体芯片而定，P4/S3 建议固定）
    adapter_cfg.task_priority = 5;           // 保持默认或根据系统负载适当调整
    errChkPrint(esp_lv_adapter_init(&adapter_cfg),"my_lv_adapter_init:esp_lv_adapter_init error\n");

    // 向 LVGL 适配器注册面板并启动任务。
    esp_lv_adapter_display_config_t disp_cfg =
        ESP_LV_ADAPTER_DISPLAY_MIPI_DEFAULT_CONFIG(
            lcddev.lcd_panel_handle,
            NULL,
            mipidev.pwidth,
            mipidev.pheight,
            ESP_LV_ADAPTER_ROTATE_0
        );

    // 默认宏通常是 DEFAULT_MIPI_DSI TRIPLE_PARTIAL，必须手动覆盖
    disp_cfg.tear_avoid_mode = ESP_LV_ADAPTER_TEAR_AVOID_MODE_DOUBLE_FULL;
    // 1. 设置全屏高度，获取全屏画布
    disp_cfg.profile.buffer_height = mipidev.pwidth; 
    // 2. 设置 PSRAM 与双缓冲要求
    disp_cfg.profile.use_psram = true;              // 绘制缓冲放入 PSRAM
    disp_cfg.profile.require_double_buffer = true;  // 全屏双缓冲
    errChkPrint(esp_lv_adapter_register_display(&disp_cfg),"my_lv_adapter_init:esp_lv_adapter_register_display error\n");

    errChkPrint(esp_lv_adapter_start(),"my_lv_adapter_init:esp_lv_adapter_start error\n");
    vTaskDelay(pdMS_TO_TICKS(100));
    return;
Error:
    return;
}