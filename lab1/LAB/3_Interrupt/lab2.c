//TaskHandle_t xTask1Handle;
//TaskHandle_t xTask2Handle;
//SemaphoreHandle_t xBinarySemaphore;
//void Timer0Handle(){
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
//    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//    xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
//    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
//}
//void vTask1(void *pvParameters){
//    while(1){
//        UARTprintf("Task 1 is running\n");
//        vTaskDelay(pdMS_TO_TICKS(500));
//    }
//}
//void vTask2(void *pvParameters){
//    xSemaphoreTake(xBinarySemaphore,0);
//    while(1){
//        if(xSemaphoreTake(xBinarySemaphore,portMAX_DELAY)){
//            UARTprintf("Handler Task");
//        }
//    }
//}
//int main(){
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    Uart_Init();
//    PortF_Init();
//    Timer_Init();
//    IntMasterEnable();
//    vSemaphoreCreateBinary(xBinarySemaphore);
//    xTaskCreate(vTask1,"Task 1",200,(void *)0,1,&xTask1Handle);
//    xTaskCreate(vTask2,"Task 2",200,(void *)0,3,&xTask2Handle);
//    vTaskStartScheduler();
//    while(1){
//
//    }
//}
