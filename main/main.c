/**
 ******************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2025-01-01
 * @brief       LCD实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 ESP32-P4 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "lcd.h"
#include <stdio.h>
#include "myLvAdapter.h"
#include "myUI.h"

/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    // esp_err_t ret;
    
    // ret = nvs_flash_init();     /* 初始化NVS */
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    // {
    //     ESP_ERROR_CHECK(nvs_flash_erase());
    //     ESP_ERROR_CHECK(nvs_flash_init());
    // }

    led_init();                 /* LED初始化 */
    lcd_init();                 /* LCD屏初始化 */
    my_lv_adapter_init();     /* LVGL适配器初始化 */

    // 加载我们的极简界面
    my_simple_ui();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
