
#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_rpm()
{
    uint32_t rpm = read_adc(CHANNEL4);
    rpm = (rpm * 6000)/1023;
    return rpm;
}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    unsigned char key = read_digital_keypad(STATE_CHANGE);  
    static char flag = 3; 
    
    if(key == SWITCH1)
    {
        flag = 0;
    }
    else if(key == SWITCH2)
    {
        flag = 1;
    }
    else if(key == SWITCH3)
    {
        flag = 2;
    }
    else if(key == SWITCH4)
    {
        flag = 3;
    }
    
    return flag;
}
