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
//car_on_road player;
void vTask2(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    uint32_t ui32ADC0Value = 0;
    while(1){
        ADCIntClear(ADC0_BASE, 3);
        ADCProcessorTrigger(ADC0_BASE, 3);
        while(!ADCIntStatus(ADC0_BASE, 3, false));
        ADCSequenceDataGet(ADC0_BASE,3,&ui32ADC0Value);
        xQueueSendToBack(xQueue1,&ui32ADC0Value,0);
        vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(33));
    }
}
//void ADCSS3Handler(){
//    ADCIntClear(ADC0_BASE, 3);
//    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//    xSemaphoreGiveFromISR(xSemaphore2,&xHigherPriorityTaskWoken);
//    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//}
//void vTask2(void *pvParameters){
//    player.carname = player_car;
//    uint32_t lValueToSend;
//    portTickType xLastTaskWakeTime = xTaskGetTickCount();
//    xSemaphoreTake(xSemaphore2,0);
//    while(1){
//        if(xSemaphoreTake(xSemaphore2,portMAX_DELAY)){
//            if(Player.life){
//                ADCSequenceDataGet(ADC0_BASE, 3, &lValueToSend);
//                xQueueSendToBack(xQueue1,&lValueToSend,0);
//            }
//        }
//    }
//}




