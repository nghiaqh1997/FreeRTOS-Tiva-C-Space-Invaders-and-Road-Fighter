//QueueHandle_t xAQueue;
////QueueHandle_t xBQueue;
////QueueHandle_t xCQueue;
//void vTask1(void *Parameters){
//    portLONG lValueToSend;
//    while(1){
//        if(~GPIO_PORTF_DATA_R&0x01){
//            lValueToSend = 1;
//            xQueueSendToBack(xAQueue,&lValueToSend,0);
//            vTaskDelay(pdMS_TO_TICKS(1000));
//        }else if(~GPIO_PORTF_DATA_R&0x10){
//            lValueToSend = 2;
//            xQueueSendToBack(xAQueue,&lValueToSend,0);
//            vTaskDelay(pdMS_TO_TICKS(1000));
//        }else{
//            lValueToSend = 3;
//            xQueueSendToBack(xAQueue,&lValueToSend,0);
//            vTaskDelay(pdMS_TO_TICKS(1000));
//        }
//    }
//}
//void vTask2(void *pvParameters){
//    portLONG lReceiveValue;
//    portBASE_TYPE xStatus;
//    while(1){
//        xStatus = xQueueReceive(xAQueue, &lReceiveValue, pdMS_TO_TICKS(100));
//        if(xStatus == pdPASS){
//            if(lReceiveValue==1){
//                printf("%s","Switch 2 is pressed");
//                GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x00)+0x08;
//            }else if(lReceiveValue==2){
//                printf("%s","Switch 1 is pressed");
//                GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x00)+0x04;
//            }else if(lReceiveValue==3){
//                printf("%s","No Switch is pressed");
//                GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & 0x00)+0x02;
//            }
//        }
//    }
//}
//int main(){
//    vSetupHardware();
//    UART_Init();
//    xAQueue = xQueueCreate(5,sizeof(portLONG));
//    //xBQueue = xQueueCreate(5,sizeof(portLONG));
//    //xCQueue = xQueueCreate(5,sizeof(portLONG));
//    xTaskCreate(vTask1, "Task 1", 200, NULL, 1, NULL);
//    xTaskCreate(vTask2, "Task 2", 200, NULL, 2, NULL);
//    vTaskStartScheduler();
//    while(1){
//
//    }
//}
//
//
