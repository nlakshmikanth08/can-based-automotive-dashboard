/*
 * File:   ecu2_main.c
 * Author: N LAKSHMIKANTH
 *
 * Created on 3 July, 2026, 8:25 AM
 */

#include <xc.h>
#include "digital_keypad.h"
#include "adc.h"
#include "uart.h"
#include "ecu2_sensor.h"
#include "msg_id.h"
#include "can.h"

#define _XTAL_FREQ 20000000

void main(void) {
    
    init_digital_keypad();
    init_adc();
    init_uart();
    init_can();
    
    
    unsigned char str[5];
     
    unsigned char indicator;
    while(1)
    {
        uint16_t rpm = get_rpm();
        indicator = process_indicator();
        
        str[0] = ((rpm/1000) % 10 +'0');
        str[1] = ((rpm/100) % 10 +'0');
        str[2] = ((rpm/10) % 10 + '0');
        str[3] = ((rpm % 10) + '0');
        str[4] = '\0';
        
        can_transmit(RPM_MSG_ID, str, 5);  
        for(int i = 500; i--;);
        
        
        can_transmit(INDICATOR_MSG_ID, &indicator, 1);
        for(int i = 1000; i--;);
         
    }
    return;
}