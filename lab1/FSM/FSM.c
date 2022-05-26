#include "../include.h"
#include "../Images.h"
#include "../Task_def.h"
#include "../Nokia5110/SPI.h"
#include "../sprite.h"
#include "FSM.h"
typedef enum {S0=0,S1,S2,S3,S4} State;
static State State_1 = S0;

void StateMachineUpdate(){
    switch(State_1){
    case S0:
        if(Start){
            State_1 = S1;
        }
        break;
    case S1:
        if((Player.life == 0)||(Player1.life == 0)){
            ledTimer = 990;
            State_1 = S2;
        }else if(Player.point == 15){
            State_1 = S3;
        }
        break;
    case S2:
        if(ledTimer==0){
            State_1 = S4;
        }
        break;
    case S3:
    case S4:
        State_1 = S0;
        break;
    }
    switch(State_1){
    case S0:
        Start = 0;
        break;
    case S1:
    case S2:
        if(Game == 0){
            Draw();
        }else if(Game == 1){
            RoadMove();
        }
        break;
    case S4:
        xTimerStop(xOneShotTimer,0);
        Special = 0;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
        Nokia5110_OutString("*----------* GAME OVER   TRY AGAIN  *----------**----------**----------*");
        break;
    case S3:
        xTimerStop(xOneShotTimer,0);
        Special = 0;
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
        Nokia5110_OutString("*----------*   WINNER      WINNER      CHICKEN     DINNER   *----------*");
        break;
    }
}
