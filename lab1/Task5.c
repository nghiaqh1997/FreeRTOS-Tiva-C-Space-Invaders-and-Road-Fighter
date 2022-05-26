/*
 * Task5.c
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
unsigned int ran=0;
void vTask5(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    while(1){
        xSemaphoreTake(xMutex,portMAX_DELAY);
        if(Game == 0){
            GameOver();
            AutoFire();
            Player_Point();
        }else{
            Car_Create();
        }

    }
}


