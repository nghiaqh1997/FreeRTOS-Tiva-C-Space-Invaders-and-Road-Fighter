/*
 * Task6.c
 *
 *  Created on: May 25, 2022
 *      Author: nghia
 */
#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
#include "FSM/FSM.h"
void vTask6(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    while(1){
        if(Game == 0){
            Missile_Move();
            Enemy_Move();
            Player_Missile_Move();
            xSemaphoreGive(xMutex);
            vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(33));
        }else{
            GameOver1();
            vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(33));
        }
    }
}



