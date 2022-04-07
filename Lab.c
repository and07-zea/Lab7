/*
 * File:   Lab.c
 * Author: Andrea Rodriguez Zea
 *
 * Created on April 6, 2022, 5:26 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF                   // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF                  // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON                   // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF                     // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF                    // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF                  // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF                   // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF                  // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON                     // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V               // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF                    // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>                             // Compilador usado
#include <stdint.h>

#define _tmr0 177                           // Cálculo de equivalencia para 5ms

void setup(void);

//INTERRUPCIONES
void __interrupt() isr (void)
{
    if (T0IF)
    {   PORTD++;                            // Cambiar a timer
        TMR0 = _tmr0;
        T0IF = 0;
     }
    if (RBIF)
    {
        if (RB0 == 0){                      // Incremento en puerto D
            PORTC++;
        }
        if (RB1 == 0){
            PORTC--;
        }  
        RBIF = 0;   
    } 
          
}

void main(void){
setup();
while(1) {}
}

void setup (void)                           //OSC CONFIG
{   OSCCONbits.SCS = 1;
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 1;
  
    PORTD = 0X00;
    PORTB = 0X03;
    PORTC = 0X00;     
    ANSEL = 0X00;
    ANSELH = 0X00;
    TRISC = 0X00;
    TRISB = 0X03;
    TRISD = 0X00;

    OPTION_REGbits.nRBPU = 0;               //ENABLE PULLUP PORTB
    IOCB = 0X03;
    
    WPUB = 0X03;

    OPTION_REGbits.T0CS = 0;                // CONFIGURAR TMR0
    OPTION_REGbits.PSA = 0; 
    OPTION_REGbits.PS2 = 0; 
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;
    TMR0 = _tmr0;
    
    INTCONbits.T0IF = 0;                    //INTCONbits.RBIF = 0;

    INTCONbits.T0IE = 1;                    //INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
}