/* 
 * File:   ecu_LCD.c
 * Author: Aya Ali
 *
 * Created on November 9, 2023, 6:48 PM
 */
#include "ecu_LCD.h"
static Std_ReturnType send_4bit_data(const lcd_8_bit_t *lcd, uint_8 command);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4_bit_t *lcd, uint_8 row, uint_8 coulmn);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4_bit_t *lcd);

static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8_bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8_bit_t *lcd, uint_8 row, uint_8 coulmn);
/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4_bit_initialize(const lcd_4_bit_t *lcd){
 Std_ReturnType ret = E_OK;
 uint_8 l_data_counter =ZERO_INIT ;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
     ret = gpio_pin_intialize(&(lcd->lcd_rs));
     ret = gpio_pin_intialize(&(lcd->lcd_en));
     for(l_data_counter = 0; l_data_counter <4; l_data_counter++){
     ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_counter]));
     }
     __delay_ms(20);
     ret = lcd_4_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     __delay_ms(5);
     ret = lcd_4_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     __delay_us(150);
     ret = lcd_4_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     ret = lcd_4_bit_send_command(lcd,LCD_CLEAR );
     ret = lcd_4_bit_send_command(lcd,LCD_RETURN_HOME);
     ret = lcd_4_bit_send_command(lcd,LCD_ENTER_MODE); 
     ret = lcd_4_bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON); 
     ret = lcd_4_bit_send_command(lcd,LCD_4BIT_MODE_2_LINE );
     ret = lcd_4_bit_send_command(lcd,0x80);
 }

 return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4_bit_send_command(const lcd_4_bit_t *lcd, uint_8 command){
Std_ReturnType ret = E_OK;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
   ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW);
   ret = send_4bit_data(&(lcd),command<< 4);
   ret = lcd_4bit_send_enable_signal(&lcd);
   ret = send_4bit_data(&(lcd),command);
   ret = lcd_4bit_send_enable_signal(&lcd);
 }

 return ret;


}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4_bit_send_char_data(const lcd_4_bit_t *lcd, uint_8 data){
Std_ReturnType ret = E_OK;

 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
   ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH);
   ret = send_4bit_data(&(lcd),data<< 4);
   ret = lcd_4bit_send_enable_signal(&lcd);
   ret = send_4bit_data(&(lcd),data);
   ret = lcd_4bit_send_enable_signal(&lcd);
 }

 return ret;


}
/**
 * 
 * @param lcd
 * @param data
 * @param row
 * @param colum
 * @return 
 */
Std_ReturnType lcd_4_bit_send_data_position(const lcd_4_bit_t *lcd, uint_8 data, uint_8 row, uint_8 colum){
Std_ReturnType ret = E_OK;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
     
     ret = lcd_4bit_set_cursor(&lcd,row, colum);
     ret = lcd_4_bit_send_char_data(&lcd, data);
}

 return ret;

}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4_bit_send_string(const lcd_4_bit_t *lcd, uint_8 *str){
Std_ReturnType ret = E_OK;
    if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
    while(*str){
     ret = lcd_4_bit_send_char_data(&lcd, *str++);
    }
 
 }

 return ret;
}
/**
 * @param lcd
 * @param str
 * @param row
 * @param colum
 * @return 
 */
Std_ReturnType lcd_4_bit_send_string_position(const lcd_4_bit_t *lcd, uint_8 *str, uint_8 row, uint_8 colum){
Std_ReturnType ret = E_OK;
    if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
    ret = lcd_4bit_set_cursor(&lcd,row, colum);
    while(*str){
     ret = lcd_4_bit_send_char_data(&lcd, *str++);
    }
 
 }

 return ret;


}
/**
 * @param lcd
 * @param chr
 * @param row
 * @param colum
 * @param mm_pos
 * @return 
 */
Std_ReturnType lcd_4_bit_send_custom_char(const lcd_4_bit_t *lcd, const uint_8 chr[], uint_8 row, uint_8 colum, uint_8 mm_pos){
Std_ReturnType ret = E_OK;
uint_8 lcd_Counter = ZERO_INIT;
    if(lcd == NULL){
     ret = E_NOT_OK;
 }
    else{
    ret = lcd_4_bit_send_command(lcd,(LCD_CGRAM_START+ (mm_pos*8)));  
    for(lcd_Counter =0; lcd_Counter <=7 ; lcd_Counter++){
        ret = lcd_4_bit_send_char_data(lcd,chr[lcd_Counter]);
    }
    ret = lcd_4_bit_send_string_position(lcd, row, colum, mm_pos);
    }

return ret;

}

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8_bit_initialize(const lcd_8_bit_t *lcd){
Std_ReturnType ret = E_OK;
 uint_8 l_data_counter =ZERO_INIT ;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
     ret = gpio_pin_intialize(&(lcd->lcd_rs));
     ret = gpio_pin_intialize(&(lcd->lcd_en));
     for(l_data_counter = 0; l_data_counter < 8 ; l_data_counter++){
     ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_counter]));
     }  
     __delay_ms(20);
     ret = lcd_8_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     __delay_ms(5);
     ret = lcd_8_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     __delay_us(150);
     ret = lcd_8_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
     
     ret = lcd_8_bit_send_command(lcd,LCD_CLEAR );
     ret = lcd_8_bit_send_command(lcd,LCD_RETURN_HOME);
     ret = lcd_8_bit_send_command(lcd,LCD_ENTER_MODE); 
     ret = lcd_8_bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON); 
     ret = lcd_8_bit_send_command(lcd,LCD_8BIT_MODE_2_LINE );
      ret = lcd_8_bit_send_command(lcd,0x80);
 }

 return ret;


}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8_bit_send_command(const lcd_8_bit_t *lcd, uint_8 command){
Std_ReturnType ret = E_OK;
 uint_8 l_command_counter =ZERO_INIT ;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
   ret = gpio_pin_write_logic(&(lcd->lcd_rs), LOW);
   for(l_command_counter = 0 ; l_command_counter < 8; l_command_counter++){
   ret = gpio_pin_write_logic(&(lcd->lcd_data[l_command_counter]) , (command << l_command_counter)& 0x01); 
   }
   ret = lcd_8bit_send_enable_signal(&lcd);
   
 }
 return ret;

}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8_bit_send_char_data(const lcd_8_bit_t *lcd, uint_8 data){
Std_ReturnType ret = E_OK;
 uint_8 l_data_counter =ZERO_INIT ;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
   ret = gpio_pin_write_logic(&(lcd->lcd_rs), HIGH);
   for(l_data_counter = 0 ; l_data_counter < 8; l_data_counter++){
   ret = gpio_pin_write_logic(&(lcd->lcd_data[l_data_counter]) , (data << l_data_counter)&0x01); 
   }
   ret = lcd_8bit_send_enable_signal(lcd);
   
 }
 return ret;


}
/**
 * 
 * @param lcd
 * @param data
 * @param row
 * @param colum
 * @return 
 */

Std_ReturnType lcd_8_bit_send_data_position(const lcd_8_bit_t *lcd, uint_8 data, uint_8 row, uint_8 colum){
Std_ReturnType ret = E_OK;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
     ret = lcd_8bit_set_cursor(lcd,row,  colum);
     ret = lcd_8_bit_send_char_data(lcd, data);
}

 return ret;


}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8_bit_send_string(const lcd_8_bit_t *lcd, uint_8 *str){
Std_ReturnType ret = E_OK;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
     while(*str){
    ret = lcd_8_bit_send_char_data(lcd, *str++);
     }
 }
return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param colum
 * @return 
 */
Std_ReturnType lcd_8_bit_send_string_position(const lcd_8_bit_t *lcd, uint_8 *str, uint_8 row, uint_8 colum){
Std_ReturnType ret = E_OK;
 if(lcd == NULL){
     ret = E_NOT_OK;
 }
 else{
      ret = lcd_8bit_set_cursor(lcd, row,  colum);
     while(*str){
    ret = lcd_8_bit_send_char_data(lcd, *str++);
     }
 }
return ret;
}
/**
 * @param lcd
 * @param chr
 * @param row
 * @param colum
 * @param mm_pos
 * @return 
 */
Std_ReturnType lcd_8_bit_send_custom_char(const lcd_8_bit_t *lcd, const uint_8 chr[], uint_8 row, uint_8 colum ,uint_8 mm_pos){
Std_ReturnType ret = E_OK;
uint_8 lcd_Counter = ZERO_INIT;
    if(lcd == NULL){
     ret = E_NOT_OK;
 }
    else{
    ret = lcd_8_bit_send_command(lcd,(LCD_CGRAM_START+ (mm_pos*8)));  
    for(lcd_Counter =0; lcd_Counter <=7 ; lcd_Counter++){
        ret = lcd_8_bit_send_char_data(lcd,chr[lcd_Counter]);
    }
    ret = lcd_8_bit_send_string_position(lcd, row, colum, mm_pos);
    }

return ret;
}
/**
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_uint_8_string(uint_8 value, uint_8 *str){
Std_ReturnType ret = E_OK;
    if(str == NULL){
     ret = E_NOT_OK;
 }
    else{
        memset(str, "/0", 4);
        sprintf((char *)str, "%i", value);
    }
return ret;

}
/**
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_uint_16_string(uint_16 value, uint_8 *str){
Std_ReturnType ret = E_OK;
uint_8 Data_Counter = 0;
uint_8 Temp_string[6] = {0};
    if(str == NULL){
     ret = E_NOT_OK;
 }
    else{
     memset(str, "/0", 6);
     str[5] = '\0' ;
     sprintf((char *)Temp_string, "%i", value);
     while (Temp_string[Data_Counter] != '\0'){
        str[Data_Counter] = Temp_string[Data_Counter];
        Data_Counter++;
     }
    }
return ret;
}
/**
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_uint_32_string(uint_32 value, uint_8 *str){
Std_ReturnType ret = E_OK;
    if(str == NULL){
     ret = E_NOT_OK;
 }
    else{
     memset(str, "/0", 11);
     sprintf((char *)str, "%i", value);
     
    }
return ret;
}


/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
static Std_ReturnType send_4bit_data(const lcd_8_bit_t *lcd, uint_8 command){
Std_ReturnType ret = E_OK;

 ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (command << 0)& 0x01); 
 ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (command << 1)& 0x01); 
 ret = gpio_pin_write_logic(&(lcd->lcd_data[2]),  (command << 2)& 0x01); 
 ret = gpio_pin_write_logic(&(lcd->lcd_data[3]),  (command << 3)& 0x01); 
 
 return ret;
}
/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4_bit_t *lcd){
Std_ReturnType ret = E_OK; 
 ret = gpio_pin_write_logic(&(lcd->lcd_en) ,HIGH);
__delay_ms(50); 
 ret = gpio_pin_write_logic(&(lcd->lcd_en) ,LOW);

 return ret;
}
/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8_bit_t *lcd){
Std_ReturnType ret = E_OK;
 
 ret = gpio_pin_write_logic(&(lcd->lcd_en) ,HIGH);
__delay_ms(50); 
 ret = gpio_pin_write_logic(&(lcd->lcd_en) ,LOW);
 return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return 
 */
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8_bit_t *lcd, uint_8 row, uint_8 coulmn){
 Std_ReturnType ret = E_OK;
 coulmn--;
 switch (row){
     case ROW1: ret = lcd_8_bit_send_char_data(lcd, (0x80 + coulmn)); break;
     case ROW2: ret = lcd_8_bit_send_char_data(lcd, (0xC0 + coulmn)); break;
     case ROW3: ret = lcd_8_bit_send_char_data(lcd, (0x94 + coulmn)); break;
     case ROW4: ret = lcd_8_bit_send_char_data(lcd, (0xD4 + coulmn)); break;
     default: ;
 }
 return ret;
}
/**
 * @param lcd
 * @param row
 * @param coulmn
 * @return 
 */
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4_bit_t *lcd, uint_8 row, uint_8 coulmn){
 Std_ReturnType ret = E_OK;
 coulmn--;
 switch (row){
     case ROW1: ret = lcd_4_bit_send_char_data(lcd, (0x80 + coulmn)); break;
     case ROW2: ret = lcd_4_bit_send_char_data(lcd, (0xC0 + coulmn)); break;
     case ROW3: ret = lcd_4_bit_send_char_data(lcd, (0x94 + coulmn)); break;
     case ROW4: ret = lcd_4_bit_send_char_data(lcd, (0xD4 + coulmn)); break;
     default: ;
 }
 return ret;
}