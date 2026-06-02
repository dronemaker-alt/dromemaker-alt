#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "display_init.h"

static const char *TAG = "esp32_p4_handheld";

void app_main(void)
{
    /* Preserve existing diagnostic behavior */
    printf("Cali prototype systems ver.0001\n");
    printf("ESP32-P4 serial online\n");

    ESP_LOGI(TAG, "Starting handheld prototype firmware");
    ESP_LOGI(TAG, "Display controller: %s", DISPLAY_DRIVER_NAME);
    ESP_LOGI(TAG, "Resolution: %dx%d", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ESP_LOGI(TAG, "Backlight GPIO: %d", PIN_LCD_BL);
    
    ESP_LOGI(TAG, "lcd init start");
    display_init();
    ESP_LOGI(TAG, "lcd init complete");

    while (true) {
        ESP_LOGI(TAG, "heartbeat");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
