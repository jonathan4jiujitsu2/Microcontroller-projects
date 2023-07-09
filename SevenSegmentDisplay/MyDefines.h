#ifndef __MYDEFINES_H
#define __MYDEFINES_H



#define GPIOMSK(_gpio, _pins) (uint32_t*) ( (char*) (_gpio) + ((_pins) << 2 )) 
    
#define _PORTA                  0x0001
#define _PORTB                  0x0002
#define _PORTC                  0x0004
#define _PORTD                  0x0008
#define _PORTE                  0x0010
#define _PORTF                  0x0020

#define _PORTG                  0x0040
#define _PORTH                  0x0080
#define _PORTJ                  0x0100
#define _PORTK                  0x0200
#define _PORTL                  0x0400
#define _PORTM                  0x0800
#define _PORTN                  0x1000
#define _PORTP                  0x2000
#define _PORTQ                  0x4000


#define _PIN0                   0x01
#define _PIN1                   0x02
#define _PIN2                   0x04
#define _PIN3                   0x08
#define _PIN4                   0x10
#define _PIN5                   0x20
#define _PIN6                   0x40
#define _PIN7                   0x80

#define _BIT0                   (1 )
#define _BIT1                   (1 << 1)
#define _BIT2                   (1 << 2 )
#define _BIT3                   (1 << 3)
#define _BIT4                   (1 << 4)
#define _BIT5                   (1  << 5)
#define _BIT6                   (1 << 6)
#define _BIT7                   (1 << 7)
#define _BIT8                   (1 << 8 )
#define _BIT9                   (1U << 9 )
#define _BIT10                  (1U << 10 )
#define _BIT11                  (1U << 11 )
#define _BIT12                  (1U << 12 )
#define _BIT13                   (1U << 13)
#define _BIT14                   (1U << 14 )
#define _BIT15                   (1U << 15 )
#define _BIT16                   (1UL  << 16)
#define _BIT17                   (1UL << 17 )
#define _BIT18                   (1UL << 18 )
#define _BIT19                   (1UL << 19 )
#define _BIT20                   (1UL << 20)
#define _BIT21                   (1UL << 21 )
#define _BIT22                   (1UL << 22 )
#define _BIT23                   (1Ul << 23 )
#define _BIT24                   (1UL << 24 )
#define _BIT25                   (1UL << 25 )
#define _BIT26                   (1UL << 26 )
#define _BIT27                   (1UL << 27 )
#define _BIT28                   (1UL << 28 )
#define _BIT29                   (1UL << 29 )
#define _BIT30                   (1UL << 30 )
#define _BIT31                   (1UL << 31 )
#endif