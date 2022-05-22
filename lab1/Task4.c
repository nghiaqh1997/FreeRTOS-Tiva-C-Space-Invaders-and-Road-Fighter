/*
 * Task4.c
 *
 *  Created on: May 19, 2022
 *      Author: nghia
 */
#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
uint8_t type = 0;
void PortAIntHandler(){
    uint32_t status = 0;
    status = GPIOIntStatus(GPIO_PORTA_BASE, true);
    GPIOIntClear(GPIO_PORTA_BASE, status);
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if((status&GPIO_INT_PIN_5)==GPIO_INT_PIN_5){
        if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5)){
            type = 1;
            xSemaphoreGiveFromISR(xSemaphore3,&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);        }
    }
    if((status&GPIO_INT_PIN_6)==GPIO_INT_PIN_6){
        if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6)){
            type = 0;
            xSemaphoreGiveFromISR(xSemaphore3,&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

void vTask4(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    xSemaphoreTake(xSemaphore3,0);
    int i;
    while(1){
        if(xSemaphoreTake(xSemaphore3,portMAX_DELAY)){
            if(Player_Missile.life == 0){
                if(type){
                    Player_Missile.image = Laser0;
                    Player_Missile.x = Player.x + 8;
                    Player_Missile.y = Player.y - 7;
                    Player_Missile.life = 1;
                }else{
                    if(Special){
                        for(i=0;i<15;i++){
                            Missile_Init();
                        }
                        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
                        Special = 0;
                        xTimerReset(xOneShotTimer,0);
                    }
                }
            }
            vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(1000));
        }
    }
}



