/*
 * Task_def.h
 *
 *  Created on: May 18, 2022
 *      Author: nghia
 */

#ifndef TASK_DEF_H_
#define TASK_DEF_H_
TaskHandle_t xTaskHandle1;
TaskHandle_t xTaskHandle2;
TaskHandle_t xTaskHandle3;
TaskHandle_t xTaskHandle4;
TaskHandle_t xTaskHandle5;
TaskHandle_t xTaskHandle6;
QueueHandle_t xQueue1;
SemaphoreHandle_t xSemaphore1;
SemaphoreHandle_t xMutex;
SemaphoreHandle_t xSemaphore3;
SemaphoreHandle_t xSemaphore4;
TimerHandle_t xOneShotTimer;
extern uint8_t Start;
extern uint16_t ledTimer;
extern uint8_t Special;
extern uint8_t Game;
extern void vTask1(void *pvParameter);
extern void PortFIntHandler();
extern void Level1();
extern void vTask2(void *pvParameter);
extern void ADCSS3Handler();
extern void vTask3(void *pvParameter);
extern void vTask4(void *pvParameter);
extern void PortAIntHandler();
extern void prvOneShotTimerCallback(TimerHandle_t xTimer);
extern void vTask5(void *pvParameter);
extern void vTask6(void *pvParameter);
#endif /* TASK_DEF_H_ */
