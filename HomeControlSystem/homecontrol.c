
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
#include "TM4C123GH6PM.h"
#include "MyDefines.h"
 
void Doorbell(void);
void RoomLightingControl(void);
void StairwallLightingControl(void);
 
void DelayMs(int ms);   // Software Delay Function
void Setup_GPIO(void);
 
int main()
{
    Setup_GPIO();
 
    // Turn off LED2 here
    GPIOA->DATA = GPIOA->DATA | _BIT4;
 
    while (1) {
        Doorbell();
        RoomLightingControl();
        StairwallLightingControl();
 
        DelayMs(20);
    }
}
//------------------------------------------------------------------------------
void Doorbell()
{   
    // was zero 
    if ((GPIOE->DATA & (_BIT1)) == 0)    
    {
        GPIOA->DATA = GPIOA->DATA & ~(_BIT2);
        }
        // else 
        else
        {
            GPIOA->DATA = GPIOA->DATA  | _BIT2;
        }
}
//------------------------------------------------------------------------------
void RoomLightingControl()
{
   
    bool                curSW2;
    static bool         preSW2 = false;
    //Step 1: read current strates for SW3 an dSW4
   curSW2 = GPIOE->DATA & _BIT2;
    //Step 2: check edge on SW3 , SW4 
    if ((preSW2 == false ) && (curSW2 == true))
    {
        GPIOA->DATA = GPIOA->DATA ^_BIT3;
    }
    //Step 3: Update preState from currState 
    preSW2 = curSW2; 
}
//------------------------------------------------------------------------------
void StairwallLightingControl()
{
    // Place your application code here
    bool                curSW3;
    static bool         preSW3 = true ;
    bool                curSW4;
    static bool         preSW4 = true; 
    //Step 1: read current strates for SW3 an dSW4
   curSW3 = GPIOB->DATA & (_BIT2);
   curSW4 = GPIOB->DATA & (_BIT3);
    //Step 2: check edge on SW3 , SW4 
    if ((preSW3 == true) && (curSW3 == false))
    {
        GPIOA->DATA = GPIOA->DATA ^ _BIT4; 
    }  
    if ((preSW4 == true) && (curSW4 == false))
    {
        GPIOA->DATA = GPIOA->DATA ^ _BIT4; 
    }
    //Step 3: Update preState from currState 
    preSW3 = curSW3;
    preSW4 = curSW4;
}
//------------------------------------------------------------------------------
void Setup_GPIO()
{    

    // Configure GPIOs
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO |= (_PORTs);)
    SYSCTL->RCGCGPIO |= (_PORTE | _PORTB | _PORTA);
    // allow time for clock to stabilize (SYSCTL->PRGPIO & (_PORTs))
    while ((SYSCTL->PRGPIO & (_PORTE | _PORTB | _PORTA)) != (_PORTE | _PORTB | _PORTA)) {};
    // 2. Unlock GPIO GPIOA->DATA = GPIOA->DATA &(~ _BIT3); only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIOx->LOCK = 0x4C4F434B; and GPIOx->CR = _PINs;)
    //GPIOF->LOCK = 0x4C4F434B;   // Unlock for GPIOF
    //GPIOF->CR |= _PIN0;         // Commit for PIN0
    // 3. Set Analog Mode Select bits for each Port (GPIOx->AMSEL = _PINs; 0=digital, 1=analog)
    // 4. Set Port Control Register for each Port (GPIOx->PCTL = PMCn << _PTCL_PINn, check the PCTL table)
    // 5. Set Alternate Function Select bits for each Port (GPIOx->AFSEL = _PINs; 0=regular I/O, 1=PCTL peripheral)
    // 6. Set Output pins for each Port (Direction of the Pins: GPIOx->DIR = _PINs; 0=input, 1=output)
    GPIOA->DIR = _PIN2 | _PIN3 | _PIN4;
    // 7. Set PUR bits (internal Pull-Up Resistor), PDR (Pull-Down Resistor), ODR (Open Drain) for each Port (0: disable, 1=enable)
    GPIOB->PUR = _PIN2 | _PIN3;
    GPIOE->PDR = _PIN1 | _PIN2;
    // 8. Set Digital ENable register on all port.pins (GPIOx->DEN = _PINs; 0=disable, 1=enable)
    GPIOE->DEN = _PIN1 | _PIN2;
    GPIOB->DEN = _PIN2 | _PIN3;
    GPIOA->DEN = _PIN2 | _PIN3 | _PIN4;
}
//------------------------------------------------------------------------------
// Delay ms milliseconds (4167:50MHz TM4C123G CPU, 1605:16MHz TM4C123G CPU Clock)
void DelayMs(int ms)
{
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4167; j++) {} // Do nothing for 1ms
}