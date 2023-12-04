/* 
 * File:   ecu_LCD.h
 * Author: Aya Ali
 *
 * Created on November 9, 2023, 6:48 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H
/*Section : Includes*/
#include "ecu_LCD_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*Section : Macro Declaration*/
#define LCD_CLEAR                   0x01
#define LCD_RETURN_HOME             0x02
#define LCD_ENTER_MODE              0x06
#define LCD_CURSOR_OFF_DISPLAY_ON   0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF  0x08
#define LCD_CURSOR_ON_BLINK_ON      0x0F
#define LCD_CURSOR_ON_BLINK_OFF     0x0E
#define LCD_DISPLAY_SHIFT_RIGHT     0x1C
#define LCD_DISPLAY_SHIFT_LEFT      0x18
#define LCD_8BIT_MODE_2_LINE        0x38
#define LCD_4BIT_MODE_2_LINE        0x28
#define LCD_CGRAM_START             0x40
#define LCD_DDRAM_START             0x80


#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4
/*Section : Data Type Declaration*/
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}lcd_4_bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8_bit_t;

/*Section : Macro Function Declaration*/


/*Section : Function Declaration*/
Std_ReturnType lcd_4_bit_initialize(const lcd_4_bit_t *lcd);
Std_ReturnType lcd_4_bit_send_command(const lcd_4_bit_t *lcd, uint_8 command);
Std_ReturnType lcd_4_bit_send_char_data(const lcd_4_bit_t *lcd, uint_8 data);
Std_ReturnType lcd_4_bit_send_data_position(const lcd_4_bit_t *lcd, uint_8 data, uint_8 row, uint_8 colum);
Std_ReturnType lcd_4_bit_send_string(const lcd_4_bit_t *lcd, uint_8 *str);
Std_ReturnType lcd_4_bit_send_string_position(const lcd_4_bit_t *lcd, uint_8 *str, uint_8 row, uint_8 colum);
Std_ReturnType lcd_4_bit_send_custom_char(const lcd_4_bit_t *lcd, const uint_8 chr[], uint_8 row, uint_8 colum, uint_8 mm_pos);

Std_ReturnType lcd_8_bit_initialize(const lcd_8_bit_t *lcd);
Std_ReturnType lcd_8_bit_send_command(const lcd_8_bit_t *lcd, uint_8 command);
Std_ReturnType lcd_8_bit_send_char_data(const lcd_8_bit_t *lcd, uint_8 data);
Std_ReturnType lcd_8_bit_send_data_position(const lcd_8_bit_t *lcd, uint_8 data, uint_8 row, uint_8 colum);
Std_ReturnType lcd_8_bit_send_string(const lcd_8_bit_t *lcd, uint_8 *str);
Std_ReturnType lcd_8_bit_send_string_position(const lcd_8_bit_t *lcd, uint_8 *str, uint_8 row, uint_8 colum);
Std_ReturnType lcd_8_bit_send_custom_char(const lcd_8_bit_t *lcd, const uint_8 chr[], uint_8 row, uint_8 colum ,uint_8 mm_pos);


Std_ReturnType convert_uint_8_string(uint_8 value, uint_8 *str);
Std_ReturnType convert_uint_16_string(uint_16 value, uint_8 *str);
Std_ReturnType convert_uint_32_string(uint_32 value, uint_8 *str);

#endif	/* ECU_LCD_H */

