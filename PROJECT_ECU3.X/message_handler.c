#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
#include "uart.h"
 

volatile unsigned char led_state = LED_OFF, status = e_ind_off;
unsigned char *ind_arr[4] = {"<--", "-->", "<->","OFF"};
unsigned char ind;

void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    data[len] = '/0';
    clcd_print(data, LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{     
    //Implement the gear function
    data[len] = '\0';
    clcd_print(data, LINE2(4));
    clcd_print("  ", LINE2(6));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    clcd_print(data, LINE2(8));
} 

void handle_indicator_data(uint8_t *data, uint8_t len) 
{  
    ind = data[0];
    clcd_print(ind_arr[ind], LINE2(13));
}

void indicator_blink()
{   
    static char flag = 0;
    if(ind == 3)
    {
        RIGHT_IND_OFF();
        LEFT_IND_OFF();
    }
    else if(ind == 0)
    {
        if(flag == 0)
        {
          flag = 1;
          LEFT_IND_ON();
          RIGHT_IND_OFF();  
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF(); 
        }
    }
    else if(ind == 1)
    {
        if(flag == 0)
        {
            flag = 1;
           RIGHT_IND_ON();
           LEFT_IND_OFF();  
        }
        else
        {
            flag = 0;
           RIGHT_IND_OFF();
            LEFT_IND_OFF(); 
        }
    }
    else if(ind == 2)
    {
        if(flag == 0)
        {
            flag = 1;
            LEFT_IND_ON();
            RIGHT_IND_ON();
        }
        else
        {
            flag = 0;
            LEFT_IND_OFF();
            RIGHT_IND_OFF(); 
        }
    }
}

void process_canbus_data() 
{   
    //process the CAN bus data
    uint16_t msg_id;
    uint8_t data[8];
    uint8_t len;
    
    can_receive(&msg_id, data, &len);
    
   if(len != 0)
   {    
        if(msg_id == SPEED_MSG_ID)
        {
            handle_speed_data(data, len);
        }

        if(msg_id == GEAR_MSG_ID)
        {
            handle_gear_data(data, len);
        }

        if(msg_id == RPM_MSG_ID)
        {
            handle_rpm_data(data, len);
        }

        if(msg_id == INDICATOR_MSG_ID)
        {
            
            handle_indicator_data(data, len);
        }
        
        len = 0;
   }
}
