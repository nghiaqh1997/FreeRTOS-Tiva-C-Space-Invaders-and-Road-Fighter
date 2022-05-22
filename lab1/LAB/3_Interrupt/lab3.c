//#include <stdbool.h>
//#include <stdint.h>
//#include "stdlib.h"
//#include <stdbool.h>
//#include "inc/hw_types.h"//macro
//#include "inc/hw_uart.h"
//#include "inc/hw_memmap.h"//base address of the memories and peripherals.
//#include "inc/hw_gpio.h"//Defines and Macros for GPIO hardware.
//#include "inc/hw_ints.h"//Macros that define the interrupt assignment
//#include "inc/hw_pwm.h"
//#include "driverlib/debug.h"
//#include "driverlib/sysctl.h"//SYSCTL register
//#include "driverlib/rom.h"//ROM library
//#include "driverlib/rom_map.h"//ROM map
//#include "driverlib/pin_map.h"//ort/Pin Mapping Definitions
//#include "driverlib/gpio.h"//Defines and Macros for GPIO API
//#include "driverlib/interrupt.h"//Interrupt library
//#include "driverlib/timer.h"//Prototypes for the timer module
//#include "driverlib/uart.h"//Defines and Macros for the UART
//#include "utils/uartstdio.h"//UARTSTDIO
//#include "driverlib/systick.h"//Systick
//#include "driverlib/udma.h"
//#include "driverlib/pwm.h"
//#include "driverlib/ssi.h"
//#include <string.h>
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
//#include "semphr.h"
//#include "Config_Register/Config_Register.h"
//#include "FSM/FSM.h"
//#include "timers.h"
////#include "inc/tm4c123gh6pm.h"
///*-----------------------------------------------------------*/
//void vApplicationMallocFailedHook( void )
//{
//    /* This function will only be called if an API call to create a task, queue
//    or semaphore fails because there is too little heap RAM remaining. */
//    for( ;; );
//}
///*-----------------------------------------------------------*/
//
//void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
//{
//    /* This function will only be called if a task overflows its stack.  Note
//    that stack overflow checking does slow down the context switch
//    implementation. */
//    for( ;; );
//}
///*-----------------------------------------------------------*/
//volatile unsigned int Idle = 0;
//void vApplicationIdleHook( void )
//{
//    /* This example does not use the idle hook to perform any processing. */
//    Idle++;
//}
///*-----------------------------------------------------------*/
//
//void vApplicationTickHook( void )
//{
//    /* This example does not use the tick hook to perform any processing. */
//}
///*-----------------------------------------------------------*/
//TaskHandle_t xTask1Handle;
//TaskHandle_t xTask2Handle;
//QueueHandle_t xQueue;
//QueueHandle_t xQueue2;
//SemaphoreHandle_t xSemaphore;
//uint8_t State;
//char string[10];
//int i = 0;
//void vTask1(void *pvParameters){
//    TickType_t xLastTimeWaken = xTaskGetTickCount();
//    char led[3][10] = {
//                       "ledon",
//                       "ledoff",
//                       "ledtoggle"
//    };
//    while(1){
//        if(xSemaphoreTake(xSemaphore,portMAX_DELAY)==pdPASS){
//            if(memcmp(led[0],string,5)==0){
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//                UARTprintf("LEDRED sang\n");
//            }else if(memcmp(led[1],string,6)==0){
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
//                UARTprintf("LEDRED tat\n");
//            }
//            else if((memcmp(led[2],string,9)==0)&&(State!=2)){
//                UARTprintf("LEDRED nhap nhay");
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
//                vTaskDelayUntil(&xLastTimeWaken, pdMS_TO_TICKS(1000));
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//                vTaskDelayUntil(&xLastTimeWaken, pdMS_TO_TICKS(1000));
//                xSemaphoreGive(xSemaphore);
//            }
//            //UARTprintf("%s",string);
//        }
//    }
//}
//void vTask2(void *pvParameters){
//    unsigned char ucReceivedValue;
//    portBASE_TYPE xStatus;
//    while(1){
//        if(i==10){
//            i = 0;
//        }
//        xStatus = xQueueReceive(xQueue,&ucReceivedValue,portMAX_DELAY);
//        if(xStatus == pdPASS){
//            string[i] = ucReceivedValue;
//            i = i + 1;
//
//        }
//    }
//}
//
//void UART0IntHandler(){
//    UBaseType_t xStatus;
//    xStatus = UARTIntStatus(UART0_BASE, true);
//    UARTIntClear(UART0_BASE, xStatus);
//    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//    unsigned char received_character;
//    while(UARTCharsAvail(UART0_BASE)){
//        received_character = UARTCharGet(UART0_BASE);
//        UARTCharPutNonBlocking(UART0_BASE, received_character); //echo character
//        if(received_character == 13){
//            i = 0;
//            UARTprintf("\n\r");
//            xSemaphoreGiveFromISR(xSemaphore,&xHigherPriorityTaskWoken);
//            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//        }else{
//            xQueueSendFromISR(xQueue,&received_character,&xHigherPriorityTaskWoken);
//        }
//        if(received_character == 'r'){
//            State = 2;
//        }else if(received_character == 'l'){
//            State = 0;
//        }
//    }
//}
//int main(){
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    Uart_Init();
//    PortF_Init();
//    xTaskCreate(vTask1,"Task 1",1000,(void *)0,2,&xTask1Handle);
//    xTaskCreate(vTask2,"Task 2",1000,(void *)0,1,&xTask2Handle);
//    xQueue = xQueueCreate(8,sizeof(char));
//    xSemaphore = xSemaphoreCreateBinary();
//    IntMasterEnable();
//    //UARTprintf("%d",xPortGetFreeHeapSize());
//    vTaskStartScheduler();
//    while(1){
//
//    }
//}
