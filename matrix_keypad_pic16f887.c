/*
 * File:   newmain.c
 * Author: Zaw Myat
 *
 * Created on April 16, 2020, 7:57 PM
 */


#define _XTAL_FREQ 4000000


// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

char findKey(unsigned short a, unsigned short b)
{
   if(b == 0)
   {
        if(a == 3)
            return 'F'; 
        else if(a == 2)
            return '1'; 
        else if(a == 1)
            return '4';
        else if(a == 0)
            return '7'; 
    }
   else if(b == 1)
    {
        if(a == 3)
            return '0'; 
        else if(a == 2) 
            return '2';
        else if(a == 1)
            return '5';
        else if(a == 0)
            return '8'; 
    }
   else if(b == 2)
    {
        if(a == 3) 
            return 'E';
        else if(a == 2)
            return '3';
        else if(a == 1) 
            return '6'; 
        else if(a == 0) 
            return '9';
    }
   else if(b == 3)
    {
        if(a == 3) 
            return 'd';
        else if(a == 2) 
            return 'C'; 
        else if(a == 1) 
            return 'b';
        else if(a == 0) 
            return 'A';
    }
}

char readKey()
{
   for(unsigned int i=0; i<4; i++)
   {
       if(i == 0)
         PORTB = 1;     // 0000 0001
       
       else if(i == 1)
         PORTB = 2;     // 0000 0010
       
       else if(i == 2)
         PORTB = 4;     // 0000 0100
       
       else if(i == 3)
         PORTB = 8;     // 0000 1000
       

       if(RB4)
          return findKey(i,0);  
       if(RB5)
          return findKey(i,1);
       if(RB6)  
          return findKey(i,2);
       if(RB7) 
          return findKey(i,3);
       __delay_ms(5);
   }
}
unsigned int segment(char a)
{
   switch(a)
      {
      case '0': return 0x3F; break;     
      case '1': return 0x06; break;    
      case '2': return 0x5B; break;  
      case '3': return 0x4F; break;    
      case '4': return 0x66; break;   
      case '5': return 0x6D; break;    
      case '6': return 0x7D; break;     
      case '7': return 0x07; break;
      case '8': return 0x7F; break;     
      case '9': return 0x6F; break;     
      case 'A': return 0x77; break;     
      case 'b': return 0x7C; break; 
      case 'C': return 0x39; break;    
      case 'd': return 0x5E; break;      
      case 'E': return 0x79; break;      
      case 'F': return 0x71; break;      
    }
}
void main()
{
    ANSEL = 0x00; ANSELH = 0x00;
    TRISC = 0x00; PORTC = 0x00;
    TRISB = 0xF0;     // 11110000
    unsigned char r;
   
    
  while(1)
  {
    r = readKey();
    PORTC = segment(r);
    
    _delay_ms(50);
  }
}