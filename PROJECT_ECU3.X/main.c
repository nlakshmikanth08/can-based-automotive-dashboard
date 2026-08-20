/*
 * File:   main.c
 * Author: N LAKSHMIKANTH
 *
 * Created on 9 July, 2026, 8:10 AM
 */


#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "uart.h"

static void init_leds() {
    TRISB = 0x08;
    PORTB = 0x00;
}

static void init_config(void) {
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
}

void main(void) {
    // Initialize peripherals
    init_config();
    unsigned long int delay = 0;

    while (1) {
         clcd_print("SPD", LINE1(0));
         clcd_print("GR", LINE1(4));
         clcd_print("RPM", LINE1(8));
         clcd_print("IND", LINE1(13));
        process_canbus_data();  
        
        if(delay++ == 1000)
        {
            delay = 0;
           indicator_blink(); 
        }
         
        
    }
    
    return;
}
