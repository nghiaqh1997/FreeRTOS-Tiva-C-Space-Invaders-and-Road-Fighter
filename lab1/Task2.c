/*
 * Task2.c
 *
 *  Created on: May 18, 2022
 *      Author: nghia
 */
#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
void ADCSS3Handler(){
    ADCIntClear(ADC0_BASE, 3);
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xSemaphore2,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
void vTask2(void *pvParameters){
    uint32_t lValueToSend;
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    xSemaphoreTake(xSemaphore2,0);
    while(1){
        if(xSemaphoreTake(xSemaphore2,portMAX_DELAY)){
            if(Player.life){
                ADCSequenceDataGet(ADC0_BASE, 3, &lValueToSend);
                xQueueSendToBack(xQueue1,&lValueToSend,0);
            }
        }else{
            taskYIELD();
        }
    }
}



