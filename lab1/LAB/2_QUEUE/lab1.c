//TaskHandle_t xTask1Handle;
//TaskHandle_t xTask2Handle;
//QueueHandle_t xQueue;
//void vTask1(void *pvParameters){
//    uint32_t lValueToSend;
//    bool xStatus;
//    lValueToSend = (portLONG)pvParameters;
//    while(1){
//        xStatus = xQueueSendToBack(xQueue,&lValueToSend,0);
//        if(xStatus != pdPASS){
//            UARTprintf("Gui khong duoc\n");
//        }
//    }
//}
//void vTask2(void *pvParameters){
//    uint32_t lReceivedValue;
//    bool xStatus;
//    while(1){
//        xStatus = xQueueReceive(xQueue,&lReceivedValue,portMAX_DELAY);
//        if(xStatus == pdPASS){
//            UARTprintf("Received = %d\n",lReceivedValue);
//        }else{
//            UARTprintf("FAIL");
//        }
//    }
//}
//int main(){
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    Uart_Init();
//    PortF_Init();
//    xQueue = xQueueCreate(5,sizeof(long));
//    xTaskCreate(vTask1,"Task 1",200,(void *)100,1,&xTask1Handle);
//    xTaskCreate(vTask1,"Task 1",200,(void *)200,1,&xTask2Handle);
//    xTaskCreate(vTask2,"Task 2",200,NULL,2,NULL);
//    //IntMasterEnable();
//    vTaskStartScheduler();
//
//    while(1){
//
//    }
//}
