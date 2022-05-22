/*
 * Task3.c
 *
 *  Created on: May 19, 2022
 *      Author: nghia
 */
#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
#include "FSM/FSM.h"
uint16_t ledTimer = 0;
void vTask3(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    portLONG lReceiveValue;
    portBASE_TYPE xStatus;
    while(1){
        if(ledTimer>0){
            ledTimer = ledTimer - 33;
        }
        xStatus = xQueueReceive(xQueue1, &lReceiveValue, 0);
        if(xStatus){
            Player.x = lReceiveValue/62;
        }
        StateMachineUpdate();
        vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(33));
    }
}


