//TaskHandle_t xTask1Handle;
//TaskHandle_t xTask2Handle;
//QueueHandle_t xQueue;
//TimerHandle_t xAutoReloadTimer;
//TimerHandle_t xOneShotTimer;
//typedef enum {
//    zero,
//    one
//} DataSource;
//typedef struct {
//    uint8_t ucValue;
//    DataSource eDataSource;
//} Data_t;
//Data_t xStructsToSend[2] =
//{
// {100,zero},
// {200,one}
//};
//void vTask1(void *pvParameters){
//    bool xStatus;
//    while(1){
//        xStatus = xQueueSendToBack(xQueue,pvParameters,0);//pdPASS
//        if(xStatus!=pdPASS){
//            UARTprintf("Khong gui duoc");
//        }
//    }
//}
//void vTask2(void *pvParameters){
//    bool xStatus;
//    Data_t xReceived;
//    while(1){
//        xStatus = xQueueReceive(xQueue,&xReceived,portMAX_DELAY);//pdPASS
//        if((xStatus==pdPASS)&&(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==0)){
//            if(xReceived.eDataSource == zero){
//                UARTprintf("From Sender 1 = %d",xReceived.ucValue);
//                xTimerReset(xAutoReloadTimer,portMAX_DELAY);//pdPASS and pdFAIL
//                xTimerReset(xOneShotTimer,portMAX_DELAY);
//            }else{
//                UARTprintf("From Sender 2 = %d",xReceived.ucValue);
//            }
//        }
//    }
//}
//void prvAutoReloadTimerCallback(TimerHandle_t xTimer){
//    TickType_t xTimeNow;
//    xTimeNow = xTaskGetTickCount();
//    static uint32_t ulExecutionCount = 0;
//    ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
//    ulExecutionCount++;
//    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)==0){
//        ulExecutionCount = 0;
//    }
//    vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );
//    UARTprintf("%d\n",xTimeNow);
//    UARTprintf("%d\n",ulExecutionCount);
//    xTimerChangePeriod(xTimer,pdMS_TO_TICKS(500),0);//pdPASS and pdFAIL
//    if( ulExecutionCount == 3 ){
//        xTimerStop( xTimer, 0 );
//    }
//    //xTimerReset(xAutoReloadTimer,portMAX_DELAY);
//}
//void prvOneShotTimerCallback(TimerHandle_t xTimer){
//    TickType_t xTimeNow;
//    xTimeNow = xTaskGetTickCount();
//    UARTprintf("Hello %d",xTimeNow);
//}
//int main(){
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    Uart_Init();
//    PortF_Init();
//    xQueue = xQueueCreate(5,sizeof(Data_t));//return NULL = failed
//    xTaskCreate(vTask1,"Task 1",200,&xStructsToSend[0],1,&xTask1Handle);//pdPASS vs pdFAIL
//    xTaskCreate(vTask1,"Task 1",200,&xStructsToSend[1],1,&xTask2Handle);
//    xTaskCreate(vTask2,"Task 2",200,NULL,2,NULL);
//    xAutoReloadTimer = xTimerCreate("Auto Reload", pdMS_TO_TICKS(1000), pdTRUE, 0, prvAutoReloadTimerCallback);//NULL = failed
//    xOneShotTimer = xTimerCreate("Auto Reload", pdMS_TO_TICKS(3333), pdFALSE, 0, prvOneShotTimerCallback);
//    xTimerStart(xAutoReloadTimer,0);//pdPASS and pdFALSE
//    xTimerStart(xOneShotTimer,0);
//    //IntMasterEnable();
//    //UARTprintf("%d",xPortGetFreeHeapSize());
//    vTaskStartScheduler();
//}
