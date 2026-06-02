#include "display_init.h"
#include <string.h>
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "display_init";
static spi_device_handle_t st_dev = NULL;

// ============================================================================
// SPI Helpers
// ============================================================================

static esp_err_t lcd_send_cmd(uint8_t cmd)
{
    gpio_set_level(PIN_LCD_DC, 0);  // DC=0 for command
    spi_transaction_t t = {0};
    t.length = 8;
    t.tx_buffer = &cmd;
    t.flags = SPI_TRANS_USE_TXDATA;
    return spi_device_transmit(st_dev, &t);
}

static esp_err_t lcd_send_data(const uint8_t *data, int len)
{
    if (len == 0) return ESP_OK;
    gpio_set_level(PIN_LCD_DC, 1);  // DC=1 for data
    spi_transaction_t t = {0};
    t.length = len * 8;
    t.tx_buffer = data;
    return spi_device_transmit(st_dev, &t);
}

// ============================================================================
// Display Controller Init Sequences
// ============================================================================

#if defined(DISPLAY_CONTROLLER_ST7789)
// ST7789 initialization sequence for 240x320 display
static void st7789_init_sequence(void)
{
    uint8_t data[16];

    ESP_LOGI(TAG, "  ST7789 SWRESET");
    lcd_send_cmd(0x01); // SWRESET
    vTaskDelay(pdMS_TO_TICKS(150));

    ESP_LOGI(TAG, "  ST7789 SLPOUT");
    lcd_send_cmd(0x11); // SLPOUT (exit sleep mode)
    vTaskDelay(pdMS_TO_TICKS(120));

    ESP_LOGI(TAG, "  ST7789 COLMOD (pixel format)");
    lcd_send_cmd(0x3A); // COLMOD
    data[0] = 0x55;     // 16-bit/pixel (5-6-5 RGB)
    lcd_send_data(data, 1);

    ESP_LOGI(TAG, "  ST7789 MADCTL (memory access control)");
    lcd_send_cmd(0x36); // MADCTL
    data[0] = 0x00;     // Top-left origin, normal column/row order
    lcd_send_data(data, 1);

    ESP_LOGI(TAG, "  ST7789 NORON");
    lcd_send_cmd(0x13); // NORON (normal display on)
    vTaskDelay(pdMS_TO_TICKS(10));

    ESP_LOGI(TAG, "  ST7789 DISPON");
    lcd_send_cmd(0x29); // DISPON (display on)
    vTaskDelay(pdMS_TO_TICKS(20));
}

#elif defined(DISPLAY_CONTROLLER_ILI9341)
// ILI9341 initialization sequence for 240x320 display
static void ili9341_init_sequence(void)
{
    uint8_t data[16];

    ESP_LOGI(TAG, "  ILI9341 SWRESET");
    lcd_send_cmd(0x01); // SWRESET
    vTaskDelay(pdMS_TO_TICKS(200));

    ESP_LOGI(TAG, "  ILI9341 PIXFMT");
    lcd_send_cmd(0x3A); // COLMOD (pixel format)
    data[0] = 0x55;     // 16-bit/pixel (5-6-5 RGB)
    lcd_send_data(data, 1);

    ESP_LOGI(TAG, "  ILI9341 MADCTL");
    lcd_send_cmd(0x36); // MADCTL (memory access control)
    data[0] = 0x48;     // BGR mode, row/column swap for 240x320
    lcd_send_data(data, 1);

    ESP_LOGI(TAG, "  ILI9341 GAMMASET");
    lcd_send_cmd(0x26); // GAMMASET (gamma curve selection)
    data[0] = 0x01;
    lcd_send_data(data, 1);

    ESP_LOGI(TAG, "  ILI9341 SLPOUT");
    lcd_send_cmd(0x11); // SLPOUT (exit sleep)
    vTaskDelay(pdMS_TO_TICKS(120));

    ESP_LOGI(TAG, "  ILI9341 DISPON");
    lcd_send_cmd(0x29); // DISPON (display on)
    vTaskDelay(pdMS_TO_TICKS(20));
}

#else
// Fallback generic sequence (similar to ST7789)
static void generic_init_sequence(void)
{
    uint8_t data[16];
    ESP_LOGW(TAG, "  Generic init sequence (no specific controller selected)");
    
    lcd_send_cmd(0x01); // SWRESET
    vTaskDelay(pdMS_TO_TICKS(150));

    lcd_send_cmd(0x11); // SLPOUT
    vTaskDelay(pdMS_TO_TICKS(120));

    lcd_send_cmd(0x3A); // COLMOD
    data[0] = 0x55;
    lcd_send_data(data, 1);

    lcd_send_cmd(0x29); // DISPON
    vTaskDelay(pdMS_TO_TICKS(20));
}
#endif

// ============================================================================
// Main Display Init
// ============================================================================

void display_init(void)
{
    esp_err_t ret;

    ESP_LOGI(TAG, "display init: driver=%s resolution=%dx%d", 
             DISPLAY_DRIVER_NAME, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    ESP_LOGI(TAG, "display init: pins BL=%d RST=%d DC=%d", 
             PIN_LCD_BL, PIN_LCD_RST, PIN_LCD_DC);

    // Configure and enable backlight GPIO
    ESP_LOGI(TAG, "display init: backlight gpio setup");
    gpio_config_t bl_conf = {
        .pin_bit_mask = 1ULL << PIN_LCD_BL,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&bl_conf);
    gpio_set_level(PIN_LCD_BL, 1);
    ESP_LOGI(TAG, "display init: backlight forced ON on GPIO %d", PIN_LCD_BL);

    // Configure DC and RST control pins
    ESP_LOGI(TAG, "display init: control pins setup");
    gpio_set_direction(PIN_LCD_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_LCD_RST, GPIO_MODE_OUTPUT);

    // Reset sequence
    ESP_LOGI(TAG, "display init: reset sequence start");
    gpio_set_level(PIN_LCD_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(PIN_LCD_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(120));
    ESP_LOGI(TAG, "display init: reset sequence complete");

    // Initialize SPI bus
    ESP_LOGI(TAG, "display init: spi bus setup MOSI=%d SCLK=%d", PIN_LCD_MOSI, PIN_LCD_SCLK);
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_LCD_MISO,
        .mosi_io_num = PIN_LCD_MOSI,
        .sclk_io_num = PIN_LCD_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096,
    };
    ret = spi_bus_initialize(LCD_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "display init: spi_bus_initialize failed: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "display init: spi bus initialized");

    // Add SPI device
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = DISPLAY_SPI_FREQ_HZ,
        .mode = 0,
        .spics_io_num = PIN_LCD_CS,
        .queue_size = 1,
        .flags = SPI_DEVICE_HALFDUPLEX,
    };
    ret = spi_bus_add_device(LCD_SPI_HOST, &devcfg, &st_dev);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "display init: spi_bus_add_device failed: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "display init: spi device added");

    // Run controller-specific init sequence
    ESP_LOGI(TAG, "display init: running controller sequence");
#if defined(DISPLAY_CONTROLLER_ST7789)
    st7789_init_sequence();
#elif defined(DISPLAY_CONTROLLER_ILI9341)
    ili9341_init_sequence();
#else
    generic_init_sequence();
#endif
    ESP_LOGI(TAG, "display init: controller sequence complete");
}
