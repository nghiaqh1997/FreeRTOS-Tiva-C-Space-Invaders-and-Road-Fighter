//TaskHandle_t xTask1Handle;
//TaskHandle_t xTask2Handle;
//SemaphoreHandle_t xBinarySemaphore;
//void PortFIntHandle(){
//    uint32_t status = 0;
//    status = GPIOIntStatus(GPIO_PORTF_BASE, true);
//    GPIOIntClear(GPIO_PORTF_BASE, status);
//    if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4){
//        if(~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_3);
//        }
//    }
//    BaseType_t xSW1Yield;
//    xSW1Yield = xTaskResumeFromISR(xTask2Handle);
//    portYIELD_FROM_ISR(xSW1Yield);
//}
//void Interrupt_GPIO_Init(){
//    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
//    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
//    GPIOIntRegister(GPIO_PORTF_BASE, PortFIntHandle);
//    IntEnable(INT_GPIOF);
//    //IntMasterEnable();
//    //IntPrioritySet(INT_GPIOF, 0xE0);
//}
//
//void vTask1(void *pvParameters)
//{
//    for(;;) {
//        UARTprintf("%s", "Task1 is Running.\n\r");
//        vTaskDelay(pdMS_TO_TICKS(500));
//    }
//}
///* Deferred interrupt processing Task */
//void vTask2(void *pvParameters)
//{
//    for(;;) {
//        vTaskSuspend(NULL);                /* Wait for SW1 interrupt */
//        UARTprintf("You Pressed SW1 Button switch\n\r");
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_2);
//    }
//}
//int main(){
//    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
//    Uart_Init();
//    PortF_Init();
//    Interrupt_GPIO_Init();
//    vSemaphoreCreateBinary(xBinarySemaphore);
//    xTaskCreate(vTask1,"Task 1",200,(void *)0,1,&xTask1Handle);
//    xTaskCreate(vTask2,"Task 2",200,(void *)0,3,&xTask2Handle);
//    vTaskStartScheduler();
//    while(1){
//
//    }
//}

