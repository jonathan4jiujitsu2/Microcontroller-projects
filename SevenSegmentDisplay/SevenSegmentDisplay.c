#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
#include "TM4C123GH6PM.h"
#include "MyDefines.h"
 
void DelayMs(int ms);   // Software Delay Function
void SegDisplay(uint8_t d);
void Setup_GPIO(void);
// You nave to finish the following array for Seven Segment Display
char SevenSeg[] = { 0x3F,   // 0
                    0x06,   // 1
                    0x5B,       // You have to finish this array for 7-seg display
                    0x4F, //3
                    0x66,   // 4
                    0x6D,   // 5
                    0x7D,   //6
                    0x07, //7
                    0x7F,   // 8
                    0x6F,   // 9
                    0x77,    //10
                    0x7C, //11
                    0x39,   // 12
                    0x5E,   // 13
                    0x79,       // 14You have to finish this array for 7-seg display
                    0x71, //15
                  };

int main()
{
    char    ch = 0;
    int     i  = 0;
    bool    preSW1 , currSW1, pause; 
    int     count = 0; 
    preSW1 = true; 
    pause = true ;
    // Place your initialization/startup code here (e.g. Setup_GPIO() )
    Setup_GPIO();
    SegDisplay(0); 
    while (1) {
        // Place your application code here
        //for (i = 0; i < sizeof(SevenSeg); i++) {
        //    SegDisplay(ch & 0x0F);
        //    ch++;
        //    DelayMs(1000);
       //1. Read Current State
        currSW1 = GPIOF->DATA & (_BIT4);
         //2. Detect the Falling Edge   
         if (( preSW1 == true && currSW1 == false )) 
            {
                // inverting pause value
                //pause =! pause; 
                pause =! pause; 
            }
         //3. update preSW1 from curr SW1 
         preSW1 = currSW1;
         if ( pause != true) {
             count+=1;
             if (count > 50) {
                 count = 0;
                 i+=1;
             
        }
    }
     SegDisplay(i);
     DelayMs(10); 
}
    }
    
//------------------------3.2 stuff 

//int main()
//{
//    bool    currSW1, preSW2, currSW2; 
//    int     count; 
//    preSW2 = true; 
//    count = 0;
//    // Place your initialization/startup code here (e.g. Setup_GPIO() )
//    Setup_GPIO();
//    SegDisplay(0); 
//    while (1) {
//        
//  
//        currSW1 = GPIOF->DATA & (_BIT4);
//        currSW2 = GPIOF->DATA & (_BIT0);
//    
//        if (currSW1 == false) /*&& (currSW2 == true)) */ {
//            count = 0;
//        } else if ((preSW2 == true) && (currSW2 == false)) /*&& (currSW1 == true)) */ {
//            count +=1; }
//        
//           
//     preSW2 = currSW2;
//     SegDisplay(count);
//     DelayMs(20); 
//}
//    }
// 
//------------------------------------------------------------------------------
// GPIO Addressing Mask
volatile uint32_t *PA42 = (uint32_t *)GPIOA + (_PIN2 | _PIN3 | _PIN4);
volatile uint32_t *PC74 = (uint32_t *)GPIOC + (_PIN4 | _PIN5 | _PIN6 | _PIN7);
volatile uint32_t *PD7  = (uint32_t *)GPIOD + (_PIN7);
 
void SegDisplay(uint8_t d)
{
    char    seg;
 
    seg = SevenSeg[d &0x0F];
    *PA42 = seg << 2;
    *PC74 = seg << 1;
    *PD7  = seg;
}
//------------------------------------------------------------------------------
void Setup_GPIO(void)
{
    // Configure GPIOs
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO |= (_PORTs);)
    SYSCTL->RCGCGPIO |= (_PORTA | _PORTC | _PORTD | _PORTF);
    // allow time for clock to stabilize (SYSCTL->PRGPIO & (_PORTs))
    while((SYSCTL->PRGPIO & (_PORTA | _PORTC | _PORTD | _PORTF)) != (_PORTA | _PORTC | _PORTD | _PORTF)) {};
    // 2. Unlock GPIO only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIOx->LOCK = 0x4C4F434B; and GPIOx->CR = _PINs;)
    GPIOD->LOCK = 0x4C4F434B;
    GPIOD->CR |= _PIN7;
     GPIOF->LOCK = 0x4C4F434B;
     GPIOF->CR |= _PIN0 ;
    // 3. Set Analog Mode Select bits for each Port (GPIOx->AMSEL = _PINs; 0=digital, 1=analog)
    // 4. Set Port Control Register for each Port (GPIOx->PCTL = PMCn << _PTCL_PINn, check the PCTL table)
    // 5. Set Alternate Function Select bits for each Port (GPIOx->AFSEL = _PINs; 0=regular I/O, 1=PCTL peripheral)
    // 6. Set Output pins for each Port (Direction of the Pins: GPIOx->DIR = _PINs; 0=input, 1=output)
    GPIOA->DIR = _PIN2 | _PIN3 | _PIN4;
    GPIOC->DIR = _PIN4 | _PIN5 | _PIN6 | _PIN7;
    GPIOD->DIR = _PIN7;
    
    // 7. Set PUR bits (internal Pull-Up Resistor), PDR (Pull-Down Resistor), ODR (Open Drain) for each Port (0: disable, 1=enable)
    GPIOF->PUR = _PIN0 | _PIN4;
    // 8. Set Digital ENable register on all port.pins (GPIOx->DEN = _PINs; 0=disable, 1=enable)
    GPIOA->DEN = _PIN2 | _PIN3 | _PIN4; 
    GPIOC->DEN = _PIN4 | _PIN5 | _PIN6 | _PIN7; 
    GPIOD->DEN = _PIN7; 
    GPIOF->DEN = _PIN0 | _PIN4; 
    
}
//------------------------------------------------------------------------------
// Delay ms milliseconds (16MHz CPU Clock)
void DelayMs(int ms)
{
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4167; j++) {} // Do nothing for 1ms
}