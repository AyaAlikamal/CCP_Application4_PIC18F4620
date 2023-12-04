#include "hal_gpio.h"

volatile uint_8 *tris_registers[]= {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint_8 *lat_registers[]= {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint_8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};


/**
 * 
 * @param pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * pin_config){
 Std_ReturnType ret = E_OK;
 if(pin_config == NULL || pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
 switch(pin_config->direction){
       case Output:
           CLEAR_BIT(*tris_registers[pin_config->port],pin_config->pin);
           break;
       case Input:
           SET_BIT(*tris_registers[pin_config->port],pin_config->pin);
           break;
       default: 
           ret = E_NOT_OK;
 }
 } 
      return ret;   
 }
#endif 
/**
 * 
 * @param pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * pin_config, direction_t * direction_status){
    Std_ReturnType ret = E_OK;
    if(pin_config == NULL || direction_status == NULL ||pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
 *direction_status = READ_BIT(*tris_registers[pin_config->port], pin_config->pin);
 }
    return ret;   
}
#endif
/**
 * 
 * @param pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config, logic_t  logic){
    Std_ReturnType ret = E_OK;
      if(pin_config == NULL || logic == NULL || pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{ 
          
    switch(logic){
       case LOW:
           CLEAR_BIT(*lat_registers[pin_config->port], pin_config->pin);
           break;
       case HIGH:
           SET_BIT(*lat_registers[pin_config->port],pin_config->pin);
           break;
       default: 
           ret = E_NOT_OK;
           break;
   } 
 }
    return ret;  
 
}
#endif


/**
 * 
 * @param pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config, logic_t * logic){
    Std_ReturnType ret = E_OK;
      if(pin_config == NULL || logic == NULL || pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
 *logic = READ_BIT(*port_registers[pin_config->port], pin_config->pin);
 }
    return ret;
}
#endif

/**
 * 
 * @param pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config){
    Std_ReturnType ret = E_OK;
      if(pin_config == NULL || pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
  TOGGLE_BIT(*lat_registers[pin_config->port],pin_config->pin);
 }
    return ret;
}
#endif
/**
 * 
 * @param pin_config
 * @return 
 */

#if GPIO_PORT_PIN_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t * pin_config){
 Std_ReturnType ret = E_OK;
 if(pin_config == NULL || pin_config->pin > PORT_PIN_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
     ret = gpio_pin_direction_intialize(pin_config);
     ret = gpio_pin_write_logic(pin_config, pin_config->logic);
 }
  return ret;  
}
#endif

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(Port_Index port, uint_8 direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
    *tris_registers[port] = direction;
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(Port_Index port, uint_8 *direction_status){
    Std_ReturnType ret = E_OK;
        if((direction_status == NULL) && (port > PORT_MAX_NUMBER-1)){
     ret = E_NOT_OK;
 }
 else{
 *direction_status = *tris_registers[port];
 }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(Port_Index port, uint_8 logic){
    Std_ReturnType ret = E_OK;
      if((logic== NULL) && (port > PORT_MAX_NUMBER-1)){
     ret = E_NOT_OK;
 }
 else{
  *lat_registers[port] = logic;
 }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(Port_Index port, uint_8 *logic){
    Std_ReturnType ret = E_OK;
       if((logic== NULL) && (port > PORT_MAX_NUMBER-1)){
     ret = E_NOT_OK;
 }
 else{
 *logic = *lat_registers[port];
 }  
    return ret;
}
#endif
/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGRATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(Port_Index port){
    Std_ReturnType ret = E_OK;
      if(port > PORT_MAX_NUMBER-1){
     ret = E_NOT_OK;
 }
 else{
  *lat_registers[port]^= PORTC_MASK;
 }  
    return ret;
}
#endif