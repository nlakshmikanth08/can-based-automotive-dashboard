/*
 * File:   ecu1_main.c
 * Author: N LAKSHMIKANTH 
 *
 * Created on 3 July, 2026, 8:38 AM
 */

#include <xc.h>
#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
//#include "uart.h"

#define _XTAL_FREQ 20000000

void main(void) {
    init_digital_keypad();
    init_adc();
    init_can();
    
    
    unsigned char str[3];
    unsigned char *arr[9] = {"GN", "G1", "G2", "G3", "G4", "G5", "GR", "GC"};  
    
    while(1)
    {
        uint16_t speed = get_speed();
        unsigned char gear = get_gear_pos();
        
            str[0] = ((speed/10)+'0');
            str[1] = ((speed%10)+'0');
            str[2] = '\0';
             
            can_transmit(SPEED_MSG_ID, str, 3);
            __delay_us(1000);
            
            can_transmit(GEAR_MSG_ID, arr[gear], 2);
            __delay_us(1000);
    }
    return;
}
