#include "HMI_oled.h"

void set_Font_oled(const uint8_t *progmemFont)
{
    ssd1306_setFixedFont(progmemFont);
}

void init_oled(void){
    ssd1306_128x64_i2c_init();
    ssd1306_clearScreen();
}

void show_temp_and_hum_oled(int32_t temp , uint32_t humidity){

    char data_buffer_temp[10];
    char data_buffer_hum[10];
    snprintf(data_buffer_temp , sizeof(data_buffer_temp),"%ld",temp);
    snprintf(data_buffer_hum , sizeof(data_buffer_hum),"%ld%%",humidity);
    ssd1306_drawLine(0,ssd1306_displayHeight()/2, ssd1306_displayWidth(), ssd1306_displayHeight()/2);
    ssd1306_printFixed(35,0 , data_buffer_temp, STYLE_ITALIC);
    ssd1306_printFixed(35,35, data_buffer_hum, STYLE_NORMAL);
}