#ifndef _HMI_OLED_H
#define _HMI_OLED_H
#include "ssd1306.h"
#include <stdio.h>
void show_temp_and_hum_oled(int32_t temp , uint32_t humidity);


void set_Font_oled(const uint8_t * progmemFont);
//void ssd1306_setFixedFont(const uint8_t * progmemFont);

void init_oled(void);
#endif