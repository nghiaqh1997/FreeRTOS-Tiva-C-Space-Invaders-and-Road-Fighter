#include "../include.h"
#include "SPI.h"
void static Delay(unsigned long ulCount){
    do{
        ulCount--;
    }while(ulCount);
}

uint32_t NokiaX=0; // position along the horizonal axis 0 to 11
uint32_t NokiaY=0; // position along the vertical axis 0 to 5
enum typeOfWrite{
    COMMAND=0,                              // the transmission is an LCD command
    DATA                                  // the transmission is data
};
uint8_t Screen[504];
void static lcdwrite(enum typeOfWrite type, char message){
    if(type == COMMAND){
        while(SSIBusy(SSI2_BASE)){};
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
        SSIDataPut(SSI2_BASE, (uint32_t)message);
        while(SSIBusy(SSI2_BASE)){};
    } else{
        while(SSIBusy(SSI2_BASE)){};
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2);
        SSIDataPut(SSI2_BASE, (uint32_t)message);
        while(SSIBusy(SSI2_BASE)){};
    }
}
void SPI_Init(){
    uint32_t initialData = 0;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlDelay(3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    SysCtlDelay(3);
    SSIDisable(SSI2_BASE);
    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);
    GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    SSIClockSourceSet(SSI2_BASE, SSI_CLOCK_SYSTEM);
    SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 3125000, 8);
    SSIEnable(SSI2_BASE);
    while(SSIDataGetNonBlocking(SSI2_BASE, &initialData));
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
    Delay(136357);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);
    Delay(454525);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);
    lcdwrite(COMMAND, 0x21);              // chip active; horizontal addressing mode (V = 0); use extended instruction set (H = 1)
    // set LCD Vop (contrast), which may require some tweaking:
    lcdwrite(COMMAND, 0x48);          // try 0xB1 (for 3.3V red SparkFun), 0xB8 (for 3.3V blue SparkFun), 0xBF if your display is too dark, or 0x80 to 0xFF if experimenting
    lcdwrite(COMMAND, 0x04);              // set temp coefficient
    lcdwrite(COMMAND, 0x14);              // LCD bias mode 1:48: try 0x13 or 0x14

    lcdwrite(COMMAND, 0x20);              // we must send 0x20 before modifying the display control mode
    lcdwrite(COMMAND, 0x0C);              // set display control to normal mode: 0x0D for inverse
}
void Nokia5110_SetCursor(unsigned char newX, unsigned char newY){
    if((newX > 11) || (newY > 5)){        // bad input
        return;                             // do nothing
    }
    // multiply newX by 7 because each character is 7 columns wide
    lcdwrite(COMMAND, 0x80|(newX*7));     // setting bit 7 updates X-position
    lcdwrite(COMMAND, 0x40|newY);         // setting bit 6 updates Y-position
    NokiaX=newX; // position along the horizonal axis 0 to 11
    NokiaY=newY; // position along the vertical axis 0 to 5
}
void Nokia5110_OutChar(unsigned char data){
    int i;
    if(data == '\r') return;
    if(data == '\n'){
        NokiaX=0; // position along the horizonal axis 0 to 11
        NokiaY++; // position along the vertical axis 0 to 5
        if(NokiaY == 6) NokiaY = 0;
        Nokia5110_SetCursor(NokiaX,NokiaY);
    }else{
        lcdwrite(DATA, 0x00);                 // blank vertical line padding
        for(i=0; i<5; i=i+1){
            lcdwrite(DATA, ASCII[data - 0x20][i]);
        }
        lcdwrite(DATA, 0x00);                 // blank vertical line padding
        NokiaX++;
        if(NokiaX >= 12){
            NokiaX=0;
            NokiaY++; // position along the vertical axis 0 to 5
            if(NokiaY >= 6) NokiaY = 0;
            Nokia5110_SetCursor(NokiaX,NokiaY);
        }
    }
}
void Nokia5110_OutString(char *ptr){
    while(*ptr){
        Nokia5110_OutChar((unsigned char)*ptr);
        ptr = ptr + 1;
    }
}
void Nokia5110_OutFix(unsigned short n){
    if(n >999){
        Nokia5110_OutString("*.**");
    } else{
        Nokia5110_OutChar(n/100+'0'); /* ones digit */
        Nokia5110_OutChar('.');
        n = n%100;
        Nokia5110_OutChar(n/10+'0'); /* tenths digit */
        Nokia5110_OutChar(n%10+'0'); /* hundredth digit */
    }
}
void Nokia5110_OutUDec(unsigned short n){
    if(n < 10){
        Nokia5110_OutString("    ");
        Nokia5110_OutChar(n+'0'); /* n is between 0 and 9 */
    } else if(n<100){
        Nokia5110_OutString("   ");
        Nokia5110_OutChar(n/10+'0'); /* tens digit */
        Nokia5110_OutChar(n%10+'0'); /* ones digit */
    } else if(n<1000){
        Nokia5110_OutString("  ");
        Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
        n = n%100;
        Nokia5110_OutChar(n/10+'0'); /* tens digit */
        Nokia5110_OutChar(n%10+'0'); /* ones digit */
    }
    else if(n<10000){
        Nokia5110_OutChar(' ');
        Nokia5110_OutChar(n/1000+'0'); /* thousands digit */
        n = n%1000;
        Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
        n = n%100;
        Nokia5110_OutChar(n/10+'0'); /* tens digit */
        Nokia5110_OutChar(n%10+'0'); /* ones digit */
    }
    else {
        Nokia5110_OutChar(n/10000+'0'); /* ten-thousands digit */
        n = n%10000;
        Nokia5110_OutChar(n/1000+'0'); /* thousands digit */
        n = n%1000;
        Nokia5110_OutChar(n/100+'0'); /* hundreds digit */
        n = n%100;
        Nokia5110_OutChar(n/10+'0'); /* tens digit */
        Nokia5110_OutChar(n%10+'0'); /* ones digit */
    }
}
void Nokia5110_Clear(void){
    int i;
    for(i=0; i<(504); i=i+1){
        lcdwrite(DATA, 0x00);
    }
    Nokia5110_SetCursor(0, 0);
}
void Nokia5110_DrawFullImage(const uint8_t *ptr){
    int i;
    Nokia5110_SetCursor(0, 0);
    for(i=0; i<(504); i=i+1){
        lcdwrite(DATA, ptr[i]);
    }
}

void Nokia5110_ClearBuffer(void){int i;
for(i=0; i<SCREENW*SCREENH/8; i=i+1){
    Screen[i] = 0;              // clear buffer
}
}
void Nokia5110_DisplayBuffer(void){
    Nokia5110_DrawFullImage(Screen);
}
void Nokia5110_PrintBMP(unsigned char xpos, unsigned char ypos, const unsigned char *ptr, unsigned char threshold){
    long width = ptr[18], height = ptr[22], i, j;
    unsigned short screenx, screeny;
    unsigned char mask;
    // check for clipping
    if((height <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
            ((width%2) != 0) ||           // must be even number of columns
            ((xpos + width) > SCREENW) || // right side cut off
            (ypos < (height - 1)) ||      // top cut off
            (ypos > SCREENH))           { // bottom cut off
        return;
    }
    if(threshold > 14){
        threshold = 14;             // only full 'on' turns pixel on
    }
    // bitmaps are encoded backwards, so start at the bottom left corner of the image
    screeny = ypos/8;
    screenx = xpos + SCREENW*screeny;
    mask = ypos%8;                // row 0 to 7
    mask = 0x01<<mask;            // now stores a mask 0x01 to 0x80
    j = ptr[10];                  // byte 10 contains the offset where image data can be found
    for(i=1; i<=(width*height/2); i=i+1){
        // the left pixel is in the upper 4 bits
        if(((ptr[j]>>4)&0xF) > threshold){
            Screen[screenx] |= mask;
        } else{
            Screen[screenx] &= ~mask;
        }
        screenx = screenx + 1;
        // the right pixel is in the lower 4 bits
        if((ptr[j]&0xF) > threshold){
            Screen[screenx] |= mask;
        } else{
            Screen[screenx] &= ~mask;
        }
        screenx = screenx + 1;
        j = j + 1;
        if((i%(width/2)) == 0){     // at the end of a row
            if(mask > 0x01){
                mask = mask>>1;
            } else{
                mask = 0x80;
                screeny = screeny - 1;
            }
            screenx = xpos + SCREENW*screeny;
            // bitmaps are 32-bit word aligned
            switch((width/2)%4){      // skip any padding
            case 0: j = j + 0; break;
            case 1: j = j + 3; break;
            case 2: j = j + 2; break;
            case 3: j = j + 1; break;
            }
        }
    }
}

