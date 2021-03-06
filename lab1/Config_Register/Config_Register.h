#ifndef CONFIG_REGISTER_CONFIG_REGISTER_H_
#define CONFIG_REGISTER_CONFIG_REGISTER_H_
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x400253FC))
extern void PortF_Init(void);
extern void Interrupt_GPIOF_Init(void);
//extern void PortFIntHandle(void);
//extern void Systick_Handle(void);
//extern void Systick_Init(void);
//extern void UART0IntHandle(void);
extern void Uart_Init(void);
//extern void Timer0Handle(void);
extern void Timer_Init(void);
//extern void ADCSS3Handle(void);
extern void ADC_Timer_Init(void);
extern void ADC_Init();
extern void PortA_Init(void);
//extern void PortAIntHandle();
extern void Interrupt_GPIOA_Init();
#endif /* CONFIG_REGISTER_CONFIG_REGISTER_H_ */
