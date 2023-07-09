#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
#include "TM4C123GH6PM.h"
#include "MyDefines.h"
 
void DelayMs(int ms);   // Software Delay Function
void Setup_GPIO(void);
 
int main(void)
{
    // Place your initialization/startup code here (e.g. Setup_GPIO() )
    Setup_GPIO();
    
    //Turn LEDS off 
    GPIOA->DATA = GPIOA->DATA &(~_BIT7); //G1
    GPIOA->DATA = GPIOA->DATA |_BIT2; //R1
    GPIOA->DATA = GPIOA->DATA &(~_BIT3); //Y1
    GPIOA->DATA = GPIOA->DATA &(~_BIT4); //G2
    GPIOA->DATA = GPIOA->DATA |_BIT5; //R2
    GPIOA->DATA = GPIOA->DATA &(~_BIT6);  //Y2 

 
    while (1) {
        // Place your application code here
        
        
        // Turn on green 1 //works
        GPIOA->DATA = GPIOA->DATA | _BIT7;
        
        // turn on red 2 
        GPIOA->DATA = GPIOA->DATA  & (~ _BIT5);
        DelayMs(10000);
        //green off 
        GPIOA->DATA = GPIOA->DATA &(~ _BIT7);
        
        
        
        
        // yellow on
        GPIOA->DATA = GPIOA->DATA | _BIT3; 
        DelayMs(3000);
        
        //yellow off
        GPIOA->DATA = GPIOA->DATA & (~_BIT3);
        DelayMs(500);
        
        //yellow on
        GPIOA->DATA = GPIOA->DATA | _BIT3; 
        DelayMs(500);
        
        //yellow off
        GPIOA->DATA =GPIOA->DATA & (~_BIT3);
        DelayMs(500);
        
        //yellow on
        GPIOA->DATA = GPIOA->DATA |  _BIT3;
        DelayMs(500);
        
        //yellow off
        GPIOA->DATA =GPIOA->DATA & (~_BIT3);
        //DelayMs(500);
        //yellow on
        //GPIOA->DATA = GPIOA->DATA | _BIT3;
        //DelayMs(500);
        //yellow on
       // GPIOA->DATA =GPIOA->DATA |_BIT3;
        
        //GPIOA->DATA = GPIOA->DATA &(~ _BIT3);
        
        
        
        //red on 
        GPIOA->DATA = GPIOA->DATA & (~_BIT2);
        DelayMs(1000);
        //here
        
        
        
        //DO NOT TOUCH WORKS
        GPIOA->DATA = GPIOA->DATA | _BIT5;
        GPIOA->DATA = GPIOA->DATA |_BIT4;

        DelayMs(10000);
        GPIOA->DATA = GPIOA->DATA &(~_BIT4);
        GPIOA->DATA = GPIOA->DATA |_BIT6;
        DelayMs(3000);
        
        GPIOA->DATA = GPIOA->DATA &(~_BIT6);
        DelayMs(500);
        GPIOA->DATA = GPIOA->DATA |_BIT6;
        DelayMs(500);
        GPIOA->DATA = GPIOA->DATA &(~_BIT6);
        DelayMs(500);
        GPIOA->DATA = GPIOA->DATA |_BIT6;
        DelayMs(500);
        
        GPIOA->DATA = GPIOA->DATA &(~_BIT6);
        GPIOA->DATA = GPIOA->DATA &(~_BIT5);
        DelayMs(1000);
        GPIOA->DATA = GPIOA->DATA |_BIT2;
    }
}
//------------------------------------------------------------------------------
void Setup_GPIO(void)
{
    // Configure GPIOs
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO |= (_PORTs);)
    SYSCTL->RCGCGPIO |= (_PORTA);
    // allow time for clock to stabilize (SYSCTL->PRGPIO & (_PORTs))
    while ((SYSCTL->PRGPIO & (_PORTA)) != (_PORTA)) {};
    // 2. Unlock GPIO only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIOx->LOCK = 0x4C4F434B; and GPIOx->CR = _PINs;)
  //  GPIOF->LOCK = 0x4C4F434B;   // Unlock for GPIOF
  //  GPIOF->CR |= _PIN0;         // Commit for PIN0
    // 3. Set Analog Mode Select bits for each Port (GPIOx->AMSEL = _PINs; 0=digital, 1=analog)
    // 4. Set Port Control Register for each Port (GPIOx->PCTL = PMCn << _PTCL_PINn, check the PCTL table)
    // 5. Set Alternate Function Select bits for each Port (GPIOx->AFSEL = _PINs; 0=regular I/O, 1=PCTL peripheral)
    // 6. Set Output pins for each Port (Direction of the Pins: GPIOx->DIR = _PINs; 0=input, 1=output)
    GPIOA->DIR = _PIN2 | _PIN3 | _PIN4 | _PIN7 | _PIN5 | _PIN6; 
    // 7. Set PUR bits (internal Pull-Up Resistor), PDR (Pull-Down Resistor), ODR (Open Drain) for each Port (0: disable, 1=enable)
 
    // 8. Set Digital ENable register on all port.pins (GPIOx->DEN = _PINs; 0=disable, 1=enable)
    GPIOA->DEN = _PIN2 | _PIN3 | _PIN4 | _PIN7 | _PIN5 | _PIN6; 

}
//------------------------------------------------------------------------------
// Delay ms milliseconds (4167:50MHz TM4C123G CPU, 1605:16MHz TM4C123G CPU Clock)
void DelayMs(int ms)
{
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4167; j++) {} // Do nothing for 1ms
}