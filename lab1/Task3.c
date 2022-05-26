#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
#include "FSM/FSM.h"
uint16_t ledTimer = 0;
void vTask3(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    uint32_t lReceivedValue;
    bool xStatus;
    while(1){
        if(ledTimer>0){
            ledTimer = ledTimer - 33;
        }
        xStatus = xQueueReceive(xQueue1,&lReceivedValue,0);
        if(xStatus == pdPASS){
            if(Game == 1){
                lReceivedValue = 4096-lReceivedValue;
                lReceivedValue = lReceivedValue/157;
                Player1.y = 15+lReceivedValue;
            }else{
                Player.x = lReceivedValue/62;
            }
        }
        StateMachineUpdate();
        vTaskDelayUntil(&xLastTaskWakeTime, pdMS_TO_TICKS(33));
    }
}



