#include "../include.h"
#include "../Task_def.h"

void PortF_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    //PD7
    //HWREG (GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    //HWREG (GPIO_PORTD_BASE + GPIO_O_CR) | = 0x81;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
//void PortFIntHandle(){
//    uint32_t status = 0;
//    status = GPIOIntStatus(GPIO_PORTF_BASE, true);
//    GPIOIntClear(GPIO_PORTF_BASE, status);
//    if((status&GPIO_INT_PIN_4)==GPIO_INT_PIN_4){
//        if(~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4)){
//
//        }
//    }
//    if((status&GPIO_INT_PIN_0)==GPIO_INT_PIN_0){
//        if(~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)){
//
//        }
//    }
//}
void Interrupt_GPIOF_Init(){
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_INT_PIN_0);
    GPIOIntRegister(GPIO_PORTF_BASE, PortFIntHandler);
    IntEnable(INT_GPIOF);
    //IntMasterEnable();
    //IntPrioritySet(INT_GPIOF, 0xE0);

}
//void Systick_Handle(){
//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
//}
//void Systick_Init(){
//    SysTickPeriodSet(SysCtlClockGet()/3);
//    SysTickEnable();
//    SysTickIntEnable();
//    //SysTickIntRegister(Systick_Handle);
//    //IntMasterEnable();
//}
//void UART0IntHandle(void)
//{
//    unsigned long ulStatus;
//    unsigned char received_character;
//    ulStatus = UARTIntStatus(UART0_BASE, true); //get interrupt status
//    UARTIntClear(UART0_BASE, ulStatus); //clear the asserted interrupts
//    while(UARTCharsAvail(UART0_BASE)) //loop while there are characters in the receive FIFO
//    {
//        received_character = UARTCharGet(UART0_BASE);
//        UARTCharPutNonBlocking(UART0_BASE, received_character); //echo character
//        if (received_character == 13) UARTCharPutNonBlocking(UART0_BASE, 10); //if CR received,issue LF as well
//    }
//}
void Uart_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
    UARTFIFOEnable(UART0_BASE); //enable FIFOs

    //IntMasterEnable(); //enable processor interrupts
    //IntEnable(INT_UART0); //enable the UART interrupt
    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //enable Receiver interrupts
    //UARTIntRegister(UART0_BASE, UART0IntHandle);
    UARTprintf("\033[2J\033[HEnter Text: "); // erase screen, put cursor at home position (0,0),prompt
    //IntPrioritySet(INT_UART0, 0x00);
}
//void Timer0Handle(){
//    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//    UARTprintf("Hello");
//}
void Timer_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet()/2-1);

    //TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1Handler);
    //TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    //IntEnable(INT_TIMER1A);
    TimerEnable(TIMER1_BASE, TIMER_A);
    //IntMasterEnable();
}
uint32_t Value;
//void ADCSS3Handle(){
//    ADCIntClear(ADC0_BASE, 3);
//    ADCSequenceDataGet(ADC0_BASE, 3, &Value);
//    UARTprintf("%d\n",Value);
//
//}
void ADC_Timer_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlDelay(3);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlDelay(3);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/30-1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(3);
    ADCHardwareOversampleConfigure(ADC0_BASE, 16);
    ADCSequenceDisable(ADC0_BASE, 3);
    TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_TIMER, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);

    ADCIntEnable(ADC0_BASE, 3);
    IntEnable(INT_ADC0SS3);
    TimerEnable(TIMER0_BASE, TIMER_A);
    ADCIntRegister(ADC0_BASE, 3, ADCSS3Handler);
    //IntPrioritySet(INT_ADC0SS3, 5<<5);
    //IntMasterEnable();
}
void ADC_Init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlDelay(3);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(3);
    ADCHardwareOversampleConfigure(ADC0_BASE, 16);
    ADCSequenceDisable(ADC0_BASE, 3);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);

}
void PortA_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlDelay(3);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
}
//void PortAIntHandle(){
//    uint32_t status = 0;
//    status = GPIOIntStatus(GPIO_PORTA_BASE, true);
//    GPIOIntClear(GPIO_PORTA_BASE, status);
//    if((status&GPIO_INT_PIN_5)==GPIO_INT_PIN_5){
//        if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5)){
//            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
//        }
//    }
//    if((status&GPIO_INT_PIN_6)==GPIO_INT_PIN_6){
//        if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6)){
//            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
//        }
//    }
//}
void Interrupt_GPIOA_Init(){
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_5|GPIO_PIN_6, GPIO_RISING_EDGE);
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_5|GPIO_INT_PIN_6);
    GPIOIntRegister(GPIO_PORTA_BASE, PortAIntHandler);
    IntEnable(INT_GPIOA);
    //IntMasterEnable();
    //IntPrioritySet(INT_GPIOA, 5<<5);

}
