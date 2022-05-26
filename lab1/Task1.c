#include "include.h"
#include "Images.h"
#include "Task_def.h"
#include "Nokia5110/SPI.h"
#include "sprite.h"
uint8_t Game = 0;
void PortFIntHandler(){
    uint32_t status = 0;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    status = GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, status);
    if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4){
        if(~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){
            Game = 0;
            xSemaphoreGiveFromISR(xSemaphore1,&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
    if((status&GPIO_INT_PIN_0)==GPIO_INT_PIN_0){
        if(~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)){
            Game = 1;
            xSemaphoreGiveFromISR(xSemaphore1,&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}
void Level1a(){
    Nokia5110_ClearBuffer();
    Player_Init();
    Player_Draw();
    Enemy_Init();
    Enemy_Draw();
    Bunker_Init();
    Bunker_Draw();
    Missile_Init();
    Player_Missile_Init();
    Nokia5110_DisplayBuffer();
}
void Level1b(){
    Nokia5110_ClearBuffer();
    Player_Init();
    Player_Draw();
    Enemy_Init();
    Enemy_Draw();
    Bunker_Init();
    Bunker_Draw();
    Missile_Init();
    Player_Missile_Init();
    Car_Init();
    Nokia5110_DisplayBuffer();
}
uint8_t Start = 0;
void vTask1(void *pvParameters){
    portTickType xLastTaskWakeTime = xTaskGetTickCount();
    xSemaphoreTake(xSemaphore1,0);
    while(1){
        //player.car_xpos = 10;
        if(xSemaphoreTake(xSemaphore1,portMAX_DELAY)){
            if(Game == 0){
                xTimerStart(xOneShotTimer,0);
                Start = 1;
                Level1a();
            }
            else if(Game == 1){
                Start = 1;
                xTimerStop(xOneShotTimer,0);
                Level1b();
                GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
                xSemaphoreGive(xMutex);
            }
        }
    }
}


